// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SocketClient.h"
#include "AbstractCar.h"
#include "MLcar.generated.h"


/**
 * 
 */
UCLASS()
class CITYSIM_API AMLcar : public AAbstractCar
{
	GENERATED_BODY()
	

public:

	AMLcar();
	bool Turn;
	bool DispX;
	bool DispY;
	bool Stop;
	bool Crashed;
	int32 savespeed;
	FVector NextLocation;
	FRotator NextRotation;
	int RotYawCounter;
	SocketClient *socket;



	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

	virtual bool IsDrivable() override;

	bool IsItClear();

	virtual void NotifyActorBeginOverlap(AActor * OtherActor);
	
	
};
