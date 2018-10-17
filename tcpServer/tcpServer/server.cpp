#include<iostream>
#include<tchar.h>
#include<WinSock2.h>
#include<windows.h>
using namespace std;
#define LEN 1024
#pragma comment(lib,"WS2_32.lib")
int _tmain(int argc, _TCHAR* argv[]){
	WSADATA wasData;
	SOCKET serverSocket;//����
	SOCKET clientSocket;//ͨ��
	SOCKADDR_IN serverAddr;//����socket��ַ
	//int port = 8888;
	int retVal;
	char recvBuf[LEN] = { '\0' };
	
	sockaddr_in clientAddr;
	int clientAddrLen = sizeof(clientAddr);
	int ret;
	//��ʼ��winsock
	ret = WSAStartup(MAKEWORD(2, 2), &wasData);
	if (ret != 0){
		cout << "wsastartup error" << endl;
		return 1;
	}
	//�������ڼ�����socket
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == INVALID_SOCKET){
		printf("socket failed/n");
		WSACleanup();
		return -1;
	}
	//����socket��ַ
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(9990);
	serverAddr.sin_addr .S_un.S_addr= htonl(INADDR_ANY);
	//��
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
	//�������Կͻ��˵�����

	printf("TCP server start...\n");
	clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientAddrLen);
	if (clientSocket == INVALID_SOCKET){
		printf("accept failed\n");
		closesocket(serverSocket);
		WSACleanup();
		return -1;
	}
	ZeroMemory(recvBuf, LEN);
	Sleep(15000);//������ʱ������һ�����յ������ͻ��˷����ı���
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