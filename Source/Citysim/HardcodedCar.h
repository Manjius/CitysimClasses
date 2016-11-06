// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbstractCar.h"
#include "HardcodedCar.generated.h"

/**
 * 
 */
UCLASS()
class CITYSIM_API AHardcodedCar : public AAbstractCar
{
	GENERATED_BODY()
	
public:

	// Sets default values for this actor's properties
	AHardcodedCar();
	
	bool Turn;
	bool DispX;
	bool DispY;
	bool Stop;
	int32 savespeed;
	FVector NextLocation;
	FRotator NextRotation;
	int RotYawCounter;




	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

	virtual bool IsDrivable() override;

	bool IsItClear();

	virtual void NotifyActorBeginOverlap(AActor * OtherActor);
	
};
