// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "CitysimGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CITYSIM_API ACitysimGameMode : public AGameMode
{
	GENERATED_BODY()

	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GeneralVars")	
	int32 Score;

	ACitysimGameMode();

	virtual void BeginPlay() override;

	void Addpoints(int32 points);

	void ResetScore();

};
