// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CityActor.h"
#include "Building.generated.h"

/**
 * 
 */
UCLASS()
class CITYSIM_API ABuilding : public ACityActor
{
	GENERATED_BODY()
	
public:

		virtual bool IsDrivable() override;

		virtual bool IsWalkable() override;
	
};
