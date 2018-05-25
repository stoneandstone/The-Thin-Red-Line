#ifndef CLIENT_H
#define CLIENT_H
#include "cocos2d.h"
#include "network/WebSocket.h"
#include<string>
USING_NS_CC;
//创建客户端类
using namespace cocos2d::network;
class Client:public cocos2d::Layer,public cocos2d::network::WebSocket::Delegate
{
public:
	virtual void onOpen(WebSocket* ws);
	virtual void onMessage(WebSocket* ws, const WebSocket::Data& data);
	virtual void onClose(WebSocket* ws);
	virtual void onError(WebSocket* ws, const WebSocket::ErrorCode& error);
	virtual bool init(const std::string & url);
	//static Client * getInstance();
	void send(const std::string buf);
	std::string recieve();
	void close();
	bool isconnect();
	WebSocket* ws();
	/*void operator=(const Client &) = delete;
	Client(const Client &) = delete;*/
	~Client();
private:
	Client() { Ws = new WebSocket; };
	WebSocket* Ws;
	std::string rec;
};

class Server
{

};
#endif