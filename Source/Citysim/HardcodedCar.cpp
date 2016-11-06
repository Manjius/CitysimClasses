// Fill out your copyright notice in the Description page of Project Settings.

#include "Citysim.h"
#include "HardcodedCar.h"
#include "CityActor.h"
#include "CitysimGameMode.h"

// Sets default values
//IMPORTANT: RED ARROW INDICATES NORTH
AHardcodedCar::AHardcodedCar()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Speed = 3;
	Turn = false;
	DispX = false;
	DispY = false;
	Stop = false;
	savespeed = Speed;

	NextLocation = GetActorLocation();
	NextRotation = GetActorRotation();
	RotYawCounter = 0;

}

void AHardcodedCar::BeginPlay()
{
	Super::BeginPlay();

}

bool AHardcodedCar::IsDrivable()
{
	return false;
}

// Called every frame
void AHardcodedCar::Tick(float DeltaTime)
{
	/*ACitysimGameMode* const gm = GetWorld()->GetAuthGameMode<ACitysimGameMode>();

	gm->ResetScore();
	gm->Addpoints(3);*/
		
	Super::Tick(DeltaTime);

	if (Turn && !Stop) {

		if (RotYawCounter < fabs(1)) {
			Turn = false;
			RotYawCounter = 0;
		}
		else if (NextRotation.Yaw > 0) {
			TurnRight();
			RotYawCounter--;
		}
		else if (NextRotation.Yaw < 0) {
			TurnLeft();
			RotYawCounter++;
		}
	}

	if (DispX && !Stop) {
		if (fabs(NextLocation.X) > Speed) {
			if (NextLocation.X > 0) {
				SetActorLocation(FVector(GetActorLocation().X + Speed, GetActorLocation().Y, GetActorLocation().Z), false);
				NextLocation.X = NextLocation.X - Speed;
			}
			if (NextLocation.X < 0) {
				SetActorLocation(FVector(GetActorLocation().X - Speed, GetActorLocation().Y, GetActorLocation().Z), false);
				NextLocation.X = NextLocation.X + Speed;
			}
		}
		else
			DispX = false;
	}
	if (DispY && !Stop) {
//		UE_LOG(LogTemp, Warning, TEXT("enterY"));
		if (fabs(NextLocation.Y) > Speed) {
//			UE_LOG(LogTemp, Warning, TEXT("morethanspeed"));
			if (NextLocation.Y > 0) {
				SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y + Speed, GetActorLocation().Z), false);
				NextLocation.Y = NextLocation.Y - Speed;
			}
			if (NextLocation.Y < 0) {
				SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y - Speed, GetActorLocation().Z), false);
				NextLocation.Y = NextLocation.Y + Speed;
			}
		}
		else
			DispY = false;
	}

	if (Stop == true) {
		if (Speed > 0)
			Decelerate();
		else
			Speed = 0;
		Stop = !IsItClear();
	}
	else {
		if (Speed < savespeed)
			Accelerate();
		else
			Speed = savespeed;
	}

}
//checks for obstacles
bool AHardcodedCar::IsItClear() {

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


void AHardcodedCar::NotifyActorBeginOverlap(class AActor* OtherActor)
{
	if (OtherActor != this) {
		Super::NotifyActorBeginOverlap(OtherActor);
		FVector OtherActorLocation = OtherActor->GetActorLocation();
		FRotator ActorRotation = GetActorRotation();
		FRotator Rotationchange = GetActorRotation();

		ACityActor* Other = Cast<ACityActor>(OtherActor);

		if (Other != NULL) {
			FVector aux = OtherActorLocation - GetActorLocation();
			//trigonometry to know if its infront.
			float trigcalc = aux.Y*cos(ActorRotation.Yaw*3.14 / 180) - aux.X*sin(ActorRotation.Yaw*3.14 / 180);
			if (trigcalc < 0)
			{
				if (Other->IsDrivable() == false) {
					Stop = true;
				}
				Rotationchange = Other->NewDirection();
				if (Rotationchange.Yaw != 0) {
					NextRotation = Rotationchange;
					RotYawCounter = NextRotation.Yaw / rotspeed;
					Turn = true;
				}
				if (Other->DisplacementX()==true) {
					NextLocation.X = aux.X;
					DispX = true;
				}
				if (Other->DisplacementY() == true) {
					NextLocation.Y = aux.Y;
					DispY = true;
				}
			}
		}
	}
}