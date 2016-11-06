// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "CityActor.generated.h"

UCLASS()
class CITYSIM_API ACityActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACityActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual bool IsDrivable();

	virtual bool IsWalkable();

	virtual FRotator NewDirection();

	virtual bool DisplacementX();

	virtual bool DisplacementY();

	virtual bool DisplacementZ();

	
	
};
