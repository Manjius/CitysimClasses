// Fill out your copyright notice in the Description page of Project Settings.

#include "Citysim.h"
#include "Mover.h"


AMover::AMover() {

	gettoX = false;
	gettoY = false;
	gettoZ = false;

}

bool AMover::DisplacementX() {
	return gettoX;
}

bool AMover::DisplacementY() {
	return gettoY;
}

bool AMover::DisplacementZ() {
	return gettoZ;
}


