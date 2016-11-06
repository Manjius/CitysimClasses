// Fill out your copyright notice in the Description page of Project Settings.

#include "Citysim.h"
#include "AbstractCar.h"


// Sets default values
AAbstractCar::AAbstractCar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Speed = 0;
	rotspeed = 0.5;

}

// Called when the game starts or when spawned
void AAbstractCar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAbstractCar::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );


	FVector ActorLocation = GetActorLocation();
	FRotator ActorRotation = GetActorRotation();

	ActorLocation.X += Speed*sin(ActorRotation.Yaw*3.14 / 180);
	ActorLocation.Y += Speed*-cos(ActorRotation.Yaw*3.14 / 180);

	SetActorLocation(ActorLocation, false);

}

void AAbstractCar::TurnRight()
{
	FRotator ActorRotation = GetActorRotation();
	ActorRotation.Yaw += rotspeed;
	SetActorRelativeRotation(ActorRotation);
}

void AAbstractCar::TurnLeft()
{
	FRotator ActorRotation = GetActorRotation();
	ActorRotation.Yaw -= rotspeed;
	SetActorRelativeRotation(ActorRotation);
}

void AAbstractCar::Accelerate()
{
	Speed++;
}

void AAbstractCar::Decelerate()
{
	Speed--;
}
