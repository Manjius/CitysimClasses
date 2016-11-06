// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CityActor.h"
#include "Mover.generated.h"

/**
 * 
 */
UCLASS()
class CITYSIM_API AMover : public ACityActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
		bool gettoX;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
		bool gettoY;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotation")
		bool gettoZ;

	// Sets default values for this actor's properties
	AMover();

	virtual bool DisplacementX() override;
	virtual bool DisplacementY() override;
	virtual bool DisplacementZ() override;

};
