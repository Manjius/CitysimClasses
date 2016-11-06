// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CityActor.h"
#include "AbstractCar.generated.h"

UCLASS()
class CITYSIM_API AAbstractCar : public ACityActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAbstractCar();

	int32 Speed;
	float rotspeed;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void TurnRight();

	void TurnLeft();

	void Accelerate();

	void Decelerate();

	
	
};
