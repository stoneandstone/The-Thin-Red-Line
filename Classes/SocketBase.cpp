#include"SocketBase.h"

SocketBase::SocketBase()
{
	_SInitSuccess = false;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)    //��ƽ̨��windows32�ж�
	WORD wVersionRequested;   //����WORD������2bytes
	wVersionRequested = MAKEWORD(2, 0);   //0�ڸ߰�λ��2�ڵͰ�λ���汾ѡ��
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