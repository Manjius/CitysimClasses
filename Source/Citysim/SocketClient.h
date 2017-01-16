
#pragma once
#include "Citysim.h"


/**
 * 
 */
class CITYSIM_API SocketClient
{
public:
	SocketClient();

	char* Send(char* message);

	char* clientsocket(int argc, char **argv);


	char*  SocketClient::Start();
	char* SocketClient::Continue(char* message);
	char*  SocketClient::End();

};

