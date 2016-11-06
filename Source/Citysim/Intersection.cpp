// Fill out your copyright notice in the Description page of Project Settings.

#include "Citysim.h"
#include "Intersection.h"

AIntersection::AIntersection()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//int dir = (rand() % 3)+1;
	
	North = true;
	West = true;
	East = true;
	South = true;

}
bool AIntersection::IsDrivable(FName direction)
{
	FName north = FName(TEXT("North"));
	FName west = FName(TEXT("West"));
	FName east = FName(TEXT("East"));
	FName south = FName(TEXT("South"));
	bool result = false;
	if (direction==north)
		result = North;
	if (direction == west)
		result = West;
	if (direction == east)
		result = East;
	if (direction == south)
		result = South;
	return result;
}
