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

	bool connectServer(const char* serverIP, unsigned short port);    //ip���˿ں�
	void sendMessage(const char* data, int count);   //�����ַ�������

	std::function<void(const char* data, int count)> onRecv;   //������װ
	std::function<void()> onDisconnect;  //������װ

};

#endif