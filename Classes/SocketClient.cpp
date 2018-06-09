#include "SocketClient.h"

//ʹ�÷�ʽ���������󣬵���connectserver���ж�����ʧ�ܻ�ɹ�--������
SocketClient::SocketClient(void) :onRecv(nullptr),_socektClient(0)  //��Ա��ʼ���б�ȷ�Ͻ�����Ϣ��ִ�к���
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

	_socektClient = socket(AF_INET, SOCK_STREAM, 0);  //������ʽ�׽��֣�IPv4 InternetЭ�飬tcp��
	if (error(_socketServer))
	{
		log("init client error!");
		_socektClient = 0;
		return false;
	}

	return true;
}

bool SocketClient::connectServer(const char* serverIP, unsigned short port) //���ӷ���ˣ��������ˡ�IP��ַ���͡��˿ںš�
{
	if (!this->initClient())
	{
		return false;
	}

	struct sockaddr_in serverAddr;      //�����̳��ýṹ��
	memset(&serverAddr, 0, sizeof(struct sockaddr_in));   //�ڴ��ʼ��

	serverAddr.sin_family = AF_INET;   //��ַ���ʼ��
	serverAddr.sin_port = htons(port);   //�˿ں�����ת��
	serverAddr.sin_addr.s_addr = inet_addr(serverIP);   //IP��ַ����ת��

	int result = 0;
	result = connect(_socektClient, (struct sockaddr*)&serverAddr, sizeof(struct sockaddr));   //��ʼ����
	if (result < 0)   //����״̬�ж�
	{
		this->closeConnect(_socektClient);
		_socektClient = 0;
		return false;
	}

	std::thread recvThread(&SocketClient::recvMessage, this);  //���������߳̽�����Ϣ
	recvThread.detach();
	return true;
}

void SocketClient::recvMessage()
{
	char recvBuf[1024];
	int amount = 0;
	while (true)    //������Ϣ
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

void SocketClient::sendMessage(const char* data, int length)    //������Ϣ���ַ������ݣ����ݳ���
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