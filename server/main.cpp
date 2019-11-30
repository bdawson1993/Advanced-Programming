#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <Windows.h>

using namespace std;

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

WSADATA wsaData;
int iResult;

SOCKET ListenSocket = INVALID_SOCKET;
vector<SOCKET> ClientSocket;

struct addrinfo* result = NULL;
struct addrinfo hints;

int iSendResult;
char recvbuf[DEFAULT_BUFLEN];
string player1;
string player2;

int recvbuflen = DEFAULT_BUFLEN;



mutex clientLock;
mutex clientLock2;
void SendAndRecv(int index)
{

	iResult = recv(ClientSocket[index], recvbuf, recvbuflen, 0);
	string message = recvbuf;
	std::string reply;

	if (iResult > 0) {
		//printf("Bytes received: %d\n", iResult);
		printf("Client says: %s\n", recvbuf);

		//send ID to client
		if (message == "Hello")
		{
			reply = "";
			reply += to_string(ClientSocket.size() - 1);
			iSendResult = send(ClientSocket[index], reply.c_str(), iResult, 0);
			if (iSendResult == SOCKET_ERROR) {
				printf("send failed with error: %d\n", WSAGetLastError());
				closesocket(ClientSocket[0]);
				WSACleanup();
			}
		}


		//store buffers
		else if (message.back() == '0') //store player 1 buffer
		{
			player1 = message;
			reply = "";
			reply += player2;
			iSendResult = send(ClientSocket[index], reply.c_str(), iResult, 0);
			if (iSendResult == SOCKET_ERROR) {
				printf("send failed with error: %d\n", WSAGetLastError());
				closesocket(ClientSocket[0]);
				WSACleanup();
			}

		}

		else if (message.back() == '1') //store player 2 buffer
		{
			player2 = message;
			reply = "";
			reply += player1;
			iSendResult = send(ClientSocket[index], reply.c_str(), iResult, 0);
			if (iSendResult == SOCKET_ERROR) {
				printf("send failed with error: %d\n", WSAGetLastError());
				closesocket(ClientSocket[0]);
				WSACleanup();
			}

		}
		else if (iResult == 0)
			printf("Connection closing...\n");
		else {
			printf("recv failed with error: %d\n", WSAGetLastError());
			closesocket(ClientSocket[index]);
			WSACleanup();
		}
	}
}
	


void ListenForConnection()
{
	
	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		//return 1;
	}

	// Accept a client socket
	SOCKET sock = INVALID_SOCKET;
	sock = accept(ListenSocket, NULL, NULL);

	clientLock.lock();
		ClientSocket.push_back(sock);
	

		if (ClientSocket[ClientSocket.size() - 1] == INVALID_SOCKET) {
			printf("accept failed with error: %d\n", WSAGetLastError());
			closesocket(ListenSocket);
			WSACleanup();
			//return 1;
		}

	clientLock.unlock();
}

void InitServer()
{
	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		//return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		//return 1;
	}

	// Create a SOCKET for connecting to server
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		//return 1;
	}

	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		//return 1;
	}

	freeaddrinfo(result);

	
}

void ListenForConnectionT()
{
	while (true)
	{
		ListenForConnection();
	}
}


int main(int argc, const char** argv)
{
	if (argc > 1)
	{
		HWND consoleWindow = GetConsoleWindow();
		SetWindowPos(consoleWindow, 0, stoi(argv[1]), stoi(argv[2]), 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	}
	

	
	// No longer need server socket
	//closesocket(ListenSocket);
	InitServer();
	ListenForConnection();

	thread listenThread(ListenForConnectionT);
	
	

	// Receive until the peer shuts down the connection
	do {
		clientLock2.lock();
			for (int i = 0; i < ClientSocket.size(); i++)
			{
				SendAndRecv(i);
			}
			clientLock2.unlock();
		
	} while (iResult > 0);

	// shutdown the connection since we're done
	iResult = shutdown(ClientSocket[0], SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(ClientSocket[0]);
		WSACleanup();
		return 1;
	}

	// cleanup
	closesocket(ClientSocket[0]);
	WSACleanup();

	

	return 0;
}