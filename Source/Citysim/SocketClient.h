
#pragma once
#include "Citysim.h"


/**
 * 
 */
class CITYSIM_API SocketClient
{
public:
	SocketClient();
	~SocketClient();

	void Send(char* message);

	int clientsocket(int argc, char **argv);

	char* generateimage();

};

