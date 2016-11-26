// Fill out your copyright notice in the Description page of Project Settings.
#include "Citysim.h"


#include "AllowWindowsPlatformTypes.h"
#include "SocketClient.h"
#include <winsock2.h>
//#include "HideWindowsPlatformTypes.h"
//#include "stdafx.h"

#include <iostream>


#include <windows.h>
#include <objidl.h>
//#include <gdiplus.h>

//using namespace Gdiplus;
//#pragma comment (lib,"Gdiplus.lib")
#include <memory>


using namespace std;

#define WIN32_LEAN_AND_MEAN



#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 155000
#define DEFAULT_PORT "27015"



SocketClient::SocketClient()
{
}

SocketClient::~SocketClient()
{
}

void SocketClient::Send(char* message) {

	char *argv[] = {message,"127.0.0.1" };


	clientsocket(2, argv);

}

char* SocketClient::generateimage() {
	unsigned __int8 imagebuffer[154587];

	int i, j;
	unsigned __int8 ***image = new unsigned __int8**[227];
	for (i = 0; i < 227; i++)
		image[i] = new unsigned __int8*[227];
	for (i = 0; i < 227; i++) {
		for (j = 0; j < 227; j++)
			image[i][j] = new unsigned __int8[3];
	}

	//get unreal screen inside hBmp
	HWND hWnd = ::FindWindow(0, _T("Calculator"));
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
			image[i][j][0] = GetRValue(Test);
			image[i][j][1] = GetGValue(Test);
			image[i][j][2] = GetBValue(Test);
		}
	}


	//format image


	for (i = 0; i < 227; i++) {
		for (j = 0; j < 227; j++) {
			imagebuffer[(i * 227 + j) + 51529 * 0] = image[i][j][0];
			imagebuffer[(i * 227 + j) + 51529 * 1] = image[i][j][1];
			imagebuffer[(i * 227 + j) + 51529 * 2] = image[i][j][2];
		}
	}

	char* str = (char*)malloc(154587 * sizeof(char));

	memcpy(str, imagebuffer, 154587);

	return str;

}


int __cdecl SocketClient::clientsocket(int argc, char **argv)
{
	WSADATA wsaData;
	SOCKET ConnectSocket = INVALID_SOCKET;
	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;

	char recvbuf[DEFAULT_BUFLEN];
	int iResult;
	int recvbuflen = DEFAULT_BUFLEN;

	//get image inside buffer

	// Validate the parameters
	if (argc != 2) {
		printf("usage: %s server-name\n", "noname");
		return 1;
	}

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo(argv[1], DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);
		if (ConnectSocket == INVALID_SOCKET) {
			printf("socket failed with error: %d\n", WSAGetLastError());
			WSACleanup();
			return 1;
		}

		// Connect to server.
		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		WSACleanup();
		return 1;
	}

	// Send an initial buffer

	//iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
	iResult = send(ConnectSocket, argv[0],154620, 0);

	if (iResult == SOCKET_ERROR) {
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}

	printf("Bytes Sent: %d\n", iResult);

	// shutdown the connection since no more data will be sent
	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}

	// Receive until the peer closes the connection
	do {

		iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0)
			printf("Bytes received: %d\n", iResult);
		else if (iResult == 0)
			printf("Connection closed\n");
		else
			printf("recv failed with error: %d\n", WSAGetLastError());

	} while (iResult > 0);

	printf("%s\n", recvbuf);
	// cleanup
	closesocket(ConnectSocket);
	WSACleanup();

	//Shutdown GDI+
	//GdiplusShutdown(gdiplusToken);

	return 0;
}