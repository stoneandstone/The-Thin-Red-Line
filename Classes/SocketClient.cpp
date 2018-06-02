#include "SocketClient.h"

//使用方式：创建对象，调用connectserver，判断连接失败或成功--重连接
SocketClient::SocketClient(void) :onRecv(nullptr),_socektClient(0)  //成员初始化列表，确认接受消息的执行函数
{
}


SocketClient::~SocketClient(void)
{
	if (_socektClient != 0)
	{
		_mutex.lock();
		this->closeConnect(_socektClient);
		_mutex.unlock();
	}
}

bool SocketClient::initClient()
{
	if (_socektClient != 0)
	{
		_mutex.lock();
		this->closeConnect(_socektClient);
		_mutex.unlock();
	}

	_socektClient = socket(AF_INET, SOCK_STREAM, 0);  //创建流式套接字（IPv4 Internet协议，tcp）
	if (error(_socketServer))
	{
		log("init client error!");
		_socektClient = 0;
		return false;
	}

	return true;
}

bool SocketClient::connectServer(const char* serverIP, unsigned short port) //连接服务端，输入服务端“IP地址”和“端口号”
{
	if (!this->initClient())
	{
		return false;
	}

	struct sockaddr_in serverAddr;      //网络编程常用结构体
	memset(&serverAddr, 0, sizeof(struct sockaddr_in));   //内存初始化

	serverAddr.sin_family = AF_INET;   //地址族初始化
	serverAddr.sin_port = htons(port);   //端口号类型转换
	serverAddr.sin_addr.s_addr = inet_addr(serverIP);   //IP地址类型转换

	int result = 0;
	result = connect(_socektClient, (struct sockaddr*)&serverAddr, sizeof(struct sockaddr));   //开始连接
	if (result < 0)   //连接状态判断
	{
		this->closeConnect(_socektClient);
		_socektClient = 0;
		return false;
	}

	std::thread recvThread(&SocketClient::recvMessage, this);  //创建接收线程接受消息
	recvThread.detach();
	return true;
}

void SocketClient::recvMessage()
{
	char recvBuf[1024];
	int amount = 0;
	while (true)    //接收消息
	{
		amount = recv(_socektClient, recvBuf, sizeof(recvBuf), 0);
		if (amount < 0)
		{
			log("recv error");
			break;
		}
		if (amount > 0 && onRecv != nullptr)
		{
			onRecv(recvBuf, amount);
		}
	}
	_mutex.lock();
	this->closeConnect(_socektClient);
	if (onDisconnect != nullptr)
	{
		onDisconnect();
	}
	_socektClient = 0;
	_mutex.unlock();
}

void SocketClient::sendMessage(const char* data, int length)    //发送消息，字符串数据，数据长度
{
	if (_socektClient != 0)
	{
		int result = send(_socektClient, data, length, 0);
		if (result < 0)
		{
			log("send error!");
		}
	}
}