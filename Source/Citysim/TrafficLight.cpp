// Fill out your copyright notice in the Description page of Project Settings.

#include "Citysim.h"
#include "TrafficLight.h"


// Sets default values
ATrafficLight::ATrafficLight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Counter = 0;
	Timer = 300;
}

// Called when the game starts or when spawned
void ATrafficLight::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATrafficLight::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	Counter++;
	if (Counter >= Timer) {
		if (Yellow == true) {
			Yellow = false;
			Red = true;
			Counter = 0;
		}
	}
	if (Counter >= Timer * 4) {
		if (Green == true) {
			Green = false;
			Yellow = true;
			Counter = 0;
		}
	}
	if (Counter >= Timer * 5) {
		if (Red == true) {
			Red = false;
			Green = true;
			Counter = 0;
		}
	}
}

bool ATrafficLight::IsDrivable()
	{
		bool result = true;
		if (Red == true || Yellow == true) {
			result = false;
		}

		return result;
	}

