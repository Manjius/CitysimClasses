// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CityActor.h"
#include "Spawner.generated.h"

UCLASS()
class CITYSIM_API ASpawner : public ACityActor
{
	GENERATED_BODY()
	
public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behaviour")
	float Frequency;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behaviour")
	int32 MaxActors;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behaviour")
	TSubclassOf<class AActor> MyItemBlueprint;

	float Counter;
	int32 ActorCounter;
	// Sets default values for this actor's properties
	ASpawner();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
};
