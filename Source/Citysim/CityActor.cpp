// Fill out your copyright notice in the Description page of Project Settings.

#include "Citysim.h"
#include "CityActor.h"


// Sets default values
ACityActor::ACityActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACityActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACityActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

bool ACityActor::IsDrivable() {
	return true;
}

bool ACityActor::IsWalkable() {
	return true;
}

FRotator ACityActor::NewDirection() {
	FRotator result = GetActorRotation();
	result.Yaw = 0;
	result.Roll = 0;
	result.Pitch = 0;
	return result;
}

bool ACityActor::DisplacementX() {
	return false;
}

bool ACityActor::DisplacementY() {
	return false;
}

bool ACityActor::DisplacementZ() {
	return false;
}

