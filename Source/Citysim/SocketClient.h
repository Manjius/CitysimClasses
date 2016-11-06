
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

	void Send();

	int clientsocket(int argc, char **argv);

};
