// Fill out your copyright notice in the Description page of Project Settings.

#include "Citysim.h"
#include "ForceRotation.h"


AForceRotation::AForceRotation() {
	Yaw = 0;
	Roll = 0;
	Pitch = 0;
	Isoptional = false;
}

FRotator AForceRotation::NewDirection() {
	FRotator result = GetActorRotation();
	if (Isoptional == true && (rand() % 2) == 1) {
		result.Yaw = 0;
		result.Roll = 0;
		result.Pitch = 0;
	}
	else {
		result.Yaw = Yaw;
		result.Roll = Roll;
		result.Pitch = Pitch;
	}
	return result;
}