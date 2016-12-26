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

char* SocketClient::Send(char* message) {

	char *argv[] = {message,"127.0.0.1" };


	char* result=clientsocket(2, argv);

	return result;

}


char* SocketClient::clientsocket(int argc, char **argv)
{
	WSADATA wsaData;
	SOCKET ConnectSocket = INVALID_SOCKET;
	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;

	char* recvbuf=(char*)malloc(20 * sizeof(char));
	int iResult;
	int recvbuflen = DEFAULT_BUFLEN;

	//get image inside buffer

	// Validate the parameters
	if (argc != 2) {
		printf("usage: %s server-name\n", "noname");
		return "00";
	}

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return "00";
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
		return "00";
	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);
		if (ConnectSocket == INVALID_SOCKET) {
			printf("socket failed with error: %d\n", WSAGetLastError());
			WSACleanup();
			return "00";
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
		return "00";
	}

	// Send an initial buffer

	//iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
	iResult = send(ConnectSocket, argv[0],154620, 0);

	if (iResult == SOCKET_ERROR) {
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return "00";
	}

	printf("Bytes Sent: %d\n", iResult);

	// shutdown the connection since no more data will be sent
	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return "00";
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


	return recvbuf;
}