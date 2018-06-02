#ifndef __SOCKET_CLIENT_H__
#define __SOCKET_CLIENT_H__
#include "SocketBase.h"

class SocketClient : public SocketBase
{

private:
	bool initClient();
	void recvMessage();

	HSocket _socketServer;
	HSocket _socektClient;

public:
	SocketClient(void);
	~SocketClient(void);

	bool connectServer(const char* serverIP, unsigned short port);    //ip，端口号
	void sendMessage(const char* data, int count);   //发送字符串数据

	std::function<void(const char* data, int count)> onRecv;   //函数封装
	std::function<void()> onDisconnect;  //函数封装

};

#endif