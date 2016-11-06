// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CityActor.h"
#include "TrafficLight.generated.h"

UCLASS()
class CITYSIM_API ATrafficLight : public ACityActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lights")
		bool Red;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lights")
		bool Green;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lights")
		bool Yellow;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lights")
		int32 Timer;

	int32 Counter;

	// Sets default values for this actor's properties
	ATrafficLight();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual bool IsDrivable() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
