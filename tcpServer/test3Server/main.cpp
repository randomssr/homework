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
	serverAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
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
	//for (int i = 0; i<5; i++){
	printf("TCP server start...\n");
	clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientAddrLen);
	if (clientSocket == INVALID_SOCKET){
		printf("accept failed\n");
		closesocket(serverSocket);
		WSACleanup();
		return -1;
	}

	//int count = 0;
	//ѭ�����տͻ��˵����ݣ�ֱ���ͻ��˷���quit�����˳�
	//char re[64];
	
		ZeroMemory(recvBuf, LEN);
		Sleep(15000);
		retVal = recv(clientSocket, recvBuf,LEN, 0);
		if (retVal == SOCKET_ERROR){
			printf("recv failed\n");
			closesocket(serverSocket);
			closesocket(clientSocket);

			WSACleanup();
			return -1;
		}
		for (int i = 0; i < strlen(recvBuf); i++){
			if (recvBuf[i] != '\0'){
				cout << recvBuf[i];

			}
		}
		cout << endl;
		/*for (int i = 0; i < strlen(re); i++){

			recvBuf[count] = re[i];
			count++;

		}*/
		//Sleep(8000);
		//��ȡ��ǰϵͳʱ��
		//SYSTEMTIME st;
		//GetLocalTime(&st);
		//char sDateTime[30];
		//sprintf(sDateTime, "%4d-%2d-%2d %2d:%2d:%2d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
		//printf("%s,recv from client[%s:%d]:%s\n", sDateTime, inet_ntoa(clientAddr.sin_addr), clientAddr.sin_port, recvBuf);
		//if (strcmp(re, "quit") == 0){
		//	cout << recvBuf << endl;
		//	retVal = send(clientSocket, "quit", strlen("quit"), 0);
		//	//closesocket(clientSocket);
		//	break;
		//}
		//else{
		//	char msg[64];
		//	sprintf(msg, "Message reveived %s", re);
		//	retVal = send(clientSocket, msg, strlen(msg), 0);
		//	if (retVal == SOCKET_ERROR){
		//		printf("send failed\n");
		//		closesocket(serverSocket);
		//		closesocket(clientSocket);

		//		WSACleanup();
		//		return -1;
		//	}
		//}


	//}

	closesocket(serverSocket);
	closesocket(clientSocket);
	WSACleanup();
	getchar();
	return 0;
}