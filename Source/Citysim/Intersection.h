// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/TriggerSphere.h"
#include "Intersection.generated.h"

/**
 * 
 */
UCLASS()
class CITYSIM_API AIntersection : public ATriggerSphere
{
	GENERATED_BODY()
	
	public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "roads")
		bool North;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "roads")
		bool West;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "roads")
		bool East;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "roads")
		bool South;

	AIntersection();

	bool IsDrivable(FName direction);

	
};


