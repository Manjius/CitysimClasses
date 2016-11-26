// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CitySim.h"
#include "CityActor.h"


/**
 * 
 */

class CITYSIM_API IncidentManager
{

public:
	struct incident {
		unsigned __int8 accident = 0;
		unsigned __int8 speed=0;
		char name[20];
		unsigned __int8 ***image=(unsigned __int8***)malloc(154587 * sizeof(unsigned __int8));
	}result;
	//struct Infraction GetInfraction(ACityActor one,ACityActor two);
	IncidentManager();
	~IncidentManager();
	char* GetInfraction(ACityActor* hero, ACityActor* villain);
	char* NoIncident();//standard image return
//private:
	char* Serialize(incident result);
	void GetImage();
	char* SerializeImage();
};
