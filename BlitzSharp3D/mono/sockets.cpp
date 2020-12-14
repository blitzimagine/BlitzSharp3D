#include "monoutil.h"
#include "../bbruntime/bbsockets.h"

PUBLIC_METHOD void DottedIP_internal(char* ret, int retLen, int ip)
{
	BBStr* i = bbDottedIP(ip);
	strcpy_s(ret, retLen, i->c_str());
	freeBBStr(i);
}

PUBLIC_METHOD int CountHostIPs(const char* hostName)
{
	BBStr* h = toBBStr(hostName);
	int ret = bbCountHostIPs(h);
	freeBBStr(h);
	return ret;
}

PUBLIC_METHOD int HostIP(int hostIndex)
{
	return bbHostIP(hostIndex);
}

PUBLIC_METHOD UDPStream* CreateUDPStream_internal(int port)
{
	return bbCreateUDPStream(port);
}

PUBLIC_METHOD void CloseUDPStream_internal(UDPStream* stream)
{
	bbCloseUDPStream(stream);
}

PUBLIC_METHOD void SendUDPMsg_internal(UDPStream* stream, int destIp, int destPort)
{
	bbSendUDPMsg(stream, destIp, destPort);
}

PUBLIC_METHOD int RecvUDPMsg_internal(UDPStream* stream)
{
	return bbRecvUDPMsg(stream);
}

PUBLIC_METHOD int UDPStreamIP_internal(UDPStream* stream)
{
	return bbUDPStreamIP(stream);
}

PUBLIC_METHOD int UDPStreamPort_internal(UDPStream* stream)
{
	return bbUDPStreamPort(stream);
}

PUBLIC_METHOD int UDPMsgIP_internal(UDPStream* stream)
{
	return bbUDPMsgIP(stream);
}

PUBLIC_METHOD int UDPMsgPort_internal(UDPStream* stream)
{
	return bbUDPMsgPort(stream);
}

PUBLIC_METHOD void UDPTimeouts(int recvTimeout)
{
	return bbUDPTimeouts(recvTimeout);
}

PUBLIC_METHOD TCPStream* OpenTCPStream_internal(const char* server, int serverPort, int localPort)
{
	BBStr* s = toBBStr(server);
	TCPStream* ret = bbOpenTCPStream(s, serverPort, localPort);
	freeBBStr(s);
	return ret;
}

PUBLIC_METHOD void CloseTCPStream_internal(TCPStream* stream)
{
	bbCloseTCPStream(stream);
}

PUBLIC_METHOD TCPServer* CreateTCPServer_internal(int port)
{
	return bbCreateTCPServer(port);
}

PUBLIC_METHOD void CloseTCPServer_internal(TCPServer* server)
{
	bbCloseTCPServer(server);
}

PUBLIC_METHOD TCPStream* AcceptTCPStream_internal(TCPServer* server)
{
	return bbAcceptTCPStream(server);
}

PUBLIC_METHOD int TCPStreamIP_internal(TCPStream* stream)
{
	return bbTCPStreamIP(stream);
}

PUBLIC_METHOD int TCPStreamPort_internal(TCPStream* stream)
{
	return bbTCPStreamPort(stream);
}

PUBLIC_METHOD void TCPTimeouts(int readTime, int acceptTime)
{
	bbTCPTimeouts(readTime, acceptTime);
}