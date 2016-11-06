// Fill out your copyright notice in the Description page of Project Settings.

#include "Citysim.h"
#include "CitysimGameMode.h"

ACitysimGameMode::ACitysimGameMode()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;
	Score = 0;

}

void ACitysimGameMode::BeginPlay()
{
	Super::BeginPlay();

}

void ACitysimGameMode::Addpoints(int32 points) {
	Score = Score + points;
	UE_LOG(LogTemp, Warning, TEXT("Score: %ld"),Score);

}

void ACitysimGameMode::ResetScore() {
	Score = 0;
}


