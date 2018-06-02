#include"SocketBase.h"

SocketBase::SocketBase()
{
	_SInitSuccess = false;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)    //多平台，windows32判断
	WORD wVersionRequested;   //创建WORD变量，2bytes
	wVersionRequested = MAKEWORD(2, 0);   //0在高八位，2在低八位，版本选择
	WSADATA wsaData;
	int nRet = WSAStartup(wVersionRequested, &wsaData); 
	if (nRet != 0)
	{
		fprintf(stderr, "Initilize Error!\n");
		return;
	}
	_SInitSuccess = true;
#endif

}

SocketBase::~SocketBase()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)  
	if (_SInitSuccess)
	{
		WSACleanup();
	}
#endif   
}

void SocketBase::closeConnect(HSocket socket)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)  
	close(socket);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)  
	closesocket(socket);
#endif  
}

bool SocketBase::error(HSocket socket)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)  
	return socket == SOCKET_ERROR;
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)  
	return socket < 0;
#endif  
}