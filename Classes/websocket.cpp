#include"websocket.h"

void Client::onOpen(WebSocket * ws)
{
	CCLOG("OnOpen");
}
void Client::onMessage(WebSocket * ws, const WebSocket::Data & data)
{
	std::string rec = data.bytes;
	CCLOG(rec.c_str());
}
void Client::onClose(WebSocket * ws)
{
	if (ws == Ws)
	{
		Ws = NULL;
	}
	CC_SAFE_DELETE(ws);
	CCLOG("onClose");
}
void Client::onError(WebSocket * ws, const WebSocket::ErrorCode & error)
{
	if (ws == Ws)
	{
		char buf[100] = { 0 };
		sprintf(buf, "an error was fired, code: %d", error);
	}
	CCLOG("Error was fired, error code: %d", error);
}
bool Client::init(const std::string & url)
{
	if (Ws == nullptr) Ws = new WebSocket();
	return Ws->init(*this, url);
}
//Client * Client::getInstance(){}
void Client::send(const std::string buf)
{
	if (isconnect()) Ws->send(buf);
}
void Client::close()
{
	if (isconnect()) Ws->closeAsync();
}
std::string Client::recieve()
{
	return rec;
}
bool Client::isconnect()
{
	return Ws == nullptr ? false : Ws->getReadyState() == WebSocket::State::OPEN;
}
WebSocket* Client::ws()
{
	return Ws;
}
Client::~Client()
{
	if (isconnect())
	{
		Ws->closeAsync();
		CC_SAFE_DELETE(Ws);
		Ws = nullptr;
	}
}