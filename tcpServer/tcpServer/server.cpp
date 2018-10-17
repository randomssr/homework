#include<iostream>
#include<tchar.h>
#include<WinSock2.h>
#include<windows.h>
using namespace std;
#define LEN 1024
#pragma comment(lib,"WS2_32.lib")
int _tmain(int argc, _TCHAR* argv[]){
	WSADATA wasData;
	SOCKET serverSocket;//监听
	SOCKET clientSocket;//通信
	SOCKADDR_IN serverAddr;//监听socket地址
	//int port = 8888;
	int retVal;
	char recvBuf[LEN] = { '\0' };
	
	sockaddr_in clientAddr;
	int clientAddrLen = sizeof(clientAddr);
	int ret;
	//初始化winsock
	ret = WSAStartup(MAKEWORD(2, 2), &wasData);
	if (ret != 0){
		cout << "wsastartup error" << endl;
		return 1;
	}
	//创建用于监听的socket
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == INVALID_SOCKET){
		printf("socket failed/n");
		WSACleanup();
		return -1;
	}
	//设置socket地址
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(9990);
	serverAddr.sin_addr .S_un.S_addr= htonl(INADDR_ANY);
	//绑定
	retVal = bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
	if (retVal == SOCKET_ERROR){
		printf("bind error\n");
		closesocket(serverSocket);
		WSACleanup();
		return -1;
	}
	//listen
	retVal = listen(serverSocket, 5);
	if (retVal == SOCKET_ERROR){
		printf("listen error\n");
		closesocket(serverSocket);
		WSACleanup();
		return -1;
	}
	//接收来自客户端的请求

	printf("TCP server start...\n");
	clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientAddrLen);
	if (clientSocket == INVALID_SOCKET){
		printf("accept failed\n");
		closesocket(serverSocket);
		WSACleanup();
		return -1;
	}
	ZeroMemory(recvBuf, LEN);
	Sleep(15000);//设置延时，可以一次性收到三个客户端发来的报文
	retVal = recv(clientSocket, recvBuf, LEN, 0);
	if (retVal == SOCKET_ERROR){
		printf("recv failed\n");
		closesocket(serverSocket);
		closesocket(clientSocket);

		WSACleanup();
		return -1;
	}
	cout << recvBuf << endl;


	
	closesocket(serverSocket);
	closesocket(clientSocket);
	WSACleanup();
	getchar();
	return 0;
}