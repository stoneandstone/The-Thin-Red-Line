#ifndef __SOCKET_BASE_H__
#define __SOCKET_BASE_H__
#include "cocos2d.h"
#include <list>
#include <thread>
USING_NS_CC;
// ����windowsƽ̨
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <WinSock2.h>
#pragma comment(lib, "WS2_32.lib")
#define HSocket SOCKET
// ����androidƽ̨
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <arpa/inet.h>   // for inet_**
#include <netdb.h>   // for gethost**
#include <netinet/in.h>  // for sockaddr_in
#include <sys/types.h>   // for socket
#include <sys/socket.h>  // for socket
#include <unistd.h>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#define HSocket int
#endif 

class SocketBase : public Ref
{
private:
	bool _SInitSuccess;

public:
	SocketBase();
	~SocketBase();

protected:
	void closeConnect(HSocket socket);
	bool error(HSocket socket);

	std::mutex _mutex;     //����������֤�߳�ֻ����

};

#endif
