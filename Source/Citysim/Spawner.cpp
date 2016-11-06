// Fill out your copyright notice in the Description page of Project Settings.

#include "Citysim.h"
#include "Spawner.h"


// Sets default values
ASpawner::ASpawner()
{
	Frequency = 10;
	MaxActors = 5;
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Counter = 0;
	ActorCounter = 0;

}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawner::Tick( float DeltaTime )
{
	Super::Tick(DeltaTime);
	Counter = Counter + 0.1;
	if (Counter > Frequency) {
		if (MyItemBlueprint && ActorCounter<MaxActors) {
			UWorld* const World = GetWorld();
			if (World) {
				FActorSpawnParameters SpawnParams;
				AActor* Object = World->SpawnActor<AActor>(MyItemBlueprint, GetActorLocation(), GetActorRotation(), SpawnParams);
				ActorCounter++;
			}
		}
		Counter = 0;
	}
}

