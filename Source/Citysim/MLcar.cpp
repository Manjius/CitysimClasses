// Fill out your copyright notice in the Description page of Project Settings.

#include "Citysim.h"
#include "MLcar.h"


// Sets default values
AMLcar::AMLcar()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Speed = 3;
	Turn = false;
	DispX = false;
	DispY = false;
	Stop = false;
	//crashed to send the signal
	Crashed = false;
	savespeed = Speed;
	//send image every X ticks
	imagedelay = 0;
	NextLocation = GetActorLocation();
	NextRotation = GetActorRotation();
	RotYawCounter = 0;
	socket = new SocketClient();
	IncMan = new IncidentManager();
	socket->Start();


}

void AMLcar::BeginPlay()
{
	Super::BeginPlay();

}

bool AMLcar::IsDrivable()
{
	return false;
}

// Called every frame
void AMLcar::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);
	int action = 0;
	

	//	socket->Send();
	if (imagedelay < 5) {
		imagedelay++;
	}
	else {
		imagedelay = 0;
		char* aux;
		aux = IncMan->GetIncident();
		//IncMan->GenerateData();
		//aux = IncMan->GetData();
		//socket->Start();
		char* recv = socket->Continue(aux);
		//socket->End();
		free(aux);
		char* input = "a..";
		//UE_LOG(LogTemp, Warning, TEXT("crashed: %c"),recv);
		//test to control car
		if (memcmp(recv,input,1)==0) {
			action = 1;
		}
		input = "d..";
		if (memcmp(recv,input, 1)==0) {
			action = 2;
		}
		input = "w..";
		if (memcmp(recv,input, 1)==0) {
			action = 3;
		}
		input = "s..";
		if (memcmp(recv,input, 1)==0) {
			action = 4;
		}
	}


	switch (action) {
	case 0:
		break;
	case 1:
		TurnLeft();
		TurnLeft();
		break;
	case 2:
		TurnRight();
		TurnRight();
		break;
	case 3:
		Accelerate();
		break;
	case 4:
		Decelerate();
		break;
	default:
		// Code
		break;
	}
	

	Crashed = !IsItClear();
	if (!Crashed) {
		IncMan->Noaccident();
	}
	//UE_LOG(LogTemp, Warning, TEXT("crashed: %d"),Crashed);

}
//checks for obstacles

bool AMLcar::IsItClear() {

	TArray<AActor*> Overlapers;
	bool result = true;
	bool tf = false;
	FRotator ActorRotation = GetActorRotation();

	//check if they let him pass
	GetOverlappingActors(Overlapers);
	for (int32 b = 0; b < Overlapers.Num(); b++)
	{
		FVector OtherActorLocation = Overlapers[b]->GetActorLocation();
		class ACityActor* OtherActor = Cast<ACityActor>(Overlapers[b]);
		if (OtherActor != NULL) {
			FVector aux = OtherActorLocation - GetActorLocation();
			//trigonometry to know if its infront.
			float trigcalc = aux.Y*cos(ActorRotation.Yaw*3.14 / 180) - aux.X*sin(ActorRotation.Yaw*3.14 / 180);
			if (trigcalc < 0)
			{
				if (OtherActor->IsDrivable() == false) {
					result = false;
				}
			}
		}


	}
	return result;
}


void AMLcar::NotifyActorBeginOverlap(class AActor* OtherActor)
{


	if (OtherActor != this) {
		Super::NotifyActorBeginOverlap(OtherActor);
		FVector OtherActorLocation = OtherActor->GetActorLocation();
		FRotator ActorRotation = GetActorRotation();
		FRotator Rotationchange = GetActorRotation();

		ACityActor* Other = Cast<ACityActor>(OtherActor);


		//aux = IncMan->GetInfraction(this, Other);
		//FString Fs = FString(ANSI_TO_TCHAR(aux));

		//UE_LOG(LogTemp, Warning, TEXT("crashed: %s"),*Fs);



		if (Other != NULL) {
			FVector aux = OtherActorLocation - GetActorLocation();
			//trigonometry to know if its infront.
			float trigcalc = aux.Y*cos(ActorRotation.Yaw*3.14 / 180) - aux.X*sin(ActorRotation.Yaw*3.14 / 180);
			if (trigcalc < 0)
			{
				if (Other->IsDrivable() == false) {
					Crashed = true;
					char* aux;
					IncMan->GetInfraction(this,Other);
					aux = IncMan->GetIncident();
					//aux = IncMan->GetData();
					//socket->Send(aux);
					free(aux);
					imagedelay = 0;
					//to not go through objects
					if (Speed>0)
						Speed = 0;
				}/*
				Rotationchange = Other->NewDirection();
				if (Rotationchange.Yaw != 0) {
					NextRotation = Rotationchange;
					RotYawCounter = NextRotation.Yaw / rotspeed;
					Turn = true;
				}
				if (Other->DisplacementX() == true) {
					NextLocation.X = aux.X;
					DispX = true;
				}
				if (Other->DisplacementY() == true) {
					NextLocation.Y = aux.Y;
					DispY = true;
				}*/
			}
		}
	}
}