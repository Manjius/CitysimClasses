// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CityActor.h"
#include "ForceRotation.generated.h"

/**
 * 
 */
UCLASS()
class CITYSIM_API AForceRotation : public ACityActor
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
		float Yaw;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
		float Roll;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
		float Pitch;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
		bool Isoptional;

	// Sets default values for this actor's properties
	AForceRotation();
	
	virtual FRotator NewDirection() override;
	
	
};
