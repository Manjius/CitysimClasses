// Fill out your copyright notice in the Description page of Project Settings.

#include "Citysim.h"
#include "IncidentManager.h"
#include "AllowWindowsPlatformTypes.h"


IncidentManager::IncidentManager()
{

}

IncidentManager::~IncidentManager()
{

}

char* IncidentManager::GetIncident() {
	GetImage();
	char* total = Serialize(result);
	return total;
}

//for testing
void IncidentManager::GenerateData() {
	GetImage();
	Data = Serialize(result);
}

char* IncidentManager::GetData() {
	return Data;
}
//for testing
void IncidentManager::Noaccident()
{
	result.accident = 0;
}

char* IncidentManager::GetInfraction(ACityActor* hero, ACityActor* villain) { //hero calls the function
	result.accident = 1;
	result.speed = abs(hero->Speed - villain->Speed);


	char* str;// = (char*)malloc(30 * sizeof(char));
	//str = (char*)TCHAR_TO_ANSI(*(villain->GetClass()->GetName()));

	FString classname = villain->GetClass()->GetFName().ToString();


	str = TCHAR_TO_ANSI(*classname);

	memcpy(result.name,str,20);


	return result.name;
		
}

char* IncidentManager::Serialize(incident result) {

	char* total = (char*)malloc(154620 * sizeof(char));
	
	unsigned __int8 Data[2];



	char* image;// = (char*)malloc(154587 * sizeof(char));
	
	image=SerializeImage();
	

	char accident = (char)result.accident;

	char* name;// = (char*)malloc(20 * sizeof(char));

	name = (char*)result.name;
	
	char* sp = (char*)result.speed;

	

	memcpy(total,image,154587);
	free(image);
	Data[0] = result.accident;
	memcpy(total+154587,Data,1);
	Data[0] = result.speed;
	memcpy(total + 154588, Data, 1);
	memcpy(total+154608,name,20);
	
//	free(result.image);

	return total;


}
//possible_bottleneck
void IncidentManager::GetImage() {
	
	int i, j;
	result.image = new unsigned __int8**[227];
	for (i = 0; i < 227; i++)
		result.image[i] = new unsigned __int8*[227];
	for (i = 0; i < 227; i++) {
		for (j = 0; j < 227; j++)
			result.image[i][j] = new unsigned __int8[3];
	}

	//get unreal screen inside hBmp
	HWND hWnd = ::FindWindow(0, _T("Citysim Game Preview Standalone (64-bit/PCD3D_SM5)"));
	//HWND hWnd = ::FindWindow(0, _T("Calculator"));
	if (hWnd == NULL) {
		printf("program not found");
	}
	RECT rect;
	GetWindowRect(hWnd, &rect);

	//get measures
	int x1 = rect.left;
	int y1 = rect.top;
	int x2 = rect.right;
	int y2 = rect.bottom;

	int width = x2 - x1;
	int height = y2 - y1;


	//get bitmap
	HDC hDc = CreateCompatibleDC(0);
	HBITMAP hBmp = CreateCompatibleBitmap(GetDC(0), x2 - x1, y2 - y1);
	SelectObject(hDc, hBmp);
	BitBlt(hDc, 0, 0, x2 - x1, y2 - y1, GetDC(0), x1, y1, SRCCOPY);


	COLORREF Test = GetPixel(hDc, 20, 20);


	//write image
	float stepw = width / 227.0f;
	float steph = height / 227.0f;
	int newi, newj;

	for (i = 0; i < 227; i++) {
		for (j = 0; j < 227; j++) {
			newi = (int)round(stepw*i);
			newj = (int)round(steph*j);
			Test = GetPixel(hDc, newi, newj);
			result.image[i][j][0] = GetRValue(Test);
			result.image[i][j][1] = GetGValue(Test);
			result.image[i][j][2] = GetBValue(Test);
		}
	}

}

char* IncidentManager::SerializeImage(){
	//format image
	unsigned __int8 imagebuffer[154587];
	int i, j;
	for (i = 0; i < 227; i++) {
		for (j = 0; j < 227; j++) {
			imagebuffer[(i * 227 + j) + 51529 * 0] = result.image[i][j][0];
			imagebuffer[(i * 227 + j) + 51529 * 1] = result.image[i][j][1];
			imagebuffer[(i * 227 + j) + 51529 * 2] = result.image[i][j][2];
		}
	}

	char* str = (char*)malloc(154587 * sizeof(char));

	memcpy(str, imagebuffer, 154587);

	return str;

}