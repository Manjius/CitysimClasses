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
		char* name = (char*)malloc(20 * sizeof(char));
		unsigned __int8 ***image=(unsigned __int8***)malloc(154587 * sizeof(unsigned __int8));
	}result;
	char* Data;
	//struct Infraction GetInfraction(ACityActor one,ACityActor two);
	IncidentManager();
	~IncidentManager();
	void GenerateData();
	char* GetData();
	char* GetInfraction(ACityActor* hero, ACityActor* villain);
	char* GetIncident();//standard image return
	void Noaccident();
//private:
	char* Serialize(incident result);
	void GetImage();
	char* SerializeImage();
};
