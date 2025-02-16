﻿#include "Network.h"


Network::~Network()
{
	closesocket(ConnectSocket);
	WSACleanup();
}

void Network::Connect()
{
	std::cout << "Connecting!..." << std::endl;
	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo("192.168.1.148", DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
	}

	// Attempt to connect to an address until one succeeds
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		// Create a SOCKET for connecting to server
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);
		if (ConnectSocket == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
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
	}

	// Send an initial buffer
	/*iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
	if (iResult == SOCKET_ERROR) {
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}
	printf("***Bytes Sent: %ld\n", iResult);
	// shutdown the connection since no more data will be sent
	iResult = shutdown(ConnectSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}*/

	/*// Receive until the peer closes the connection
	do {
		iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0)
			printf("Bytes received: %d\n", iResult);
		else if (iResult == 0)
			printf("Connection closed\n");
		else
			printf("recv failed with error: %d\n", WSAGetLastError());
	} while (iResult > 0);*/

	std::cout << "Connected!" << std::endl;

	//send hello to get back player id
	string id = SendData("Hello");
	playerID = stoi(id);
}

string Network::SendData(std::string data)
{

	//cout << sizeof(data) / 8;
	

	iResult = send(ConnectSocket, data.c_str(), sizeof(data) + 30, 0);
	if (iResult == SOCKET_ERROR) {
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
	}

	//bzero(buffer, 256);
	//n = read(sockfd, buffer, 255);
	//if (n < 0) msg("ERROR reading from socket");
	//printf("%s\n", buffer);

	iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
	if (iResult > 0)
	{
		string message = recvbuf;

		if (message[0] == 'B') //First char of message should be B
		{
			otherID = message.back() - '0';
			if (shownOtherID == false)
			{
				cout << "OtherID: " << to_string(otherID) << endl;
				shownOtherID = true;
			}
		}
		
	}

	return recvbuf;
}

int Network::PlayerID()
{
	return playerID;
}

int Network::OtherID()
{
	return otherID;
}


