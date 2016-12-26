
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

	char* Send(char* message);

	char* clientsocket(int argc, char **argv);


};

