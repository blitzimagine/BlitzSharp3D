#include "monoutil.h"
#include "../bbruntime/multiplay.h"

PUBLIC_METHOD int StartNetGame()
{
	return bbStartNetGame();
}

PUBLIC_METHOD int HostNetGame(const char* gameName)
{
	BBStr* n = toBBStr(gameName);
	int ret = bbHostNetGame(n);
	freeBBStr(n);
	return ret;
}

PUBLIC_METHOD int JoinNetGame(const char* gameName, const char* ip)
{
	BBStr* n = toBBStr(gameName);
	BBStr* i = toBBStr(ip);
	int ret = bbJoinNetGame(n, i);
	freeBBStr(n);
	return ret;
}

PUBLIC_METHOD void StopNetGame()
{
	bbStopNetGame();
}

PUBLIC_METHOD int CreateNetPlayer(const char* name)
{
	BBStr* n = toBBStr(name);
	int ret = bbCreateNetPlayer(n);
	freeBBStr(n);
	return ret;
}

PUBLIC_METHOD void DeleteNetPlayer(int player)
{
	bbDeleteNetPlayer(player);
}

PUBLIC_METHOD void NetPlayerName_internal(char* ret, int retLen, int player)
{
	BBStr* n = bbNetPlayerName(player);
	strcpy_s(ret, retLen, n->c_str());
	freeBBStr(n);
}

PUBLIC_METHOD int NetPlayerLocal(int player)
{
	return bbNetPlayerLocal(player) != 0;
}

PUBLIC_METHOD int SendNetMsg(int type, const char* msg, int from, int to, int reliable)
{
	BBStr* m = toBBStr(msg);
	int ret = bbSendNetMsg(type, m, from, to, reliable);
	freeBBStr(m);
	return ret;
}

PUBLIC_METHOD int RecvNetMsg()
{
	return bbRecvNetMsg();
}

PUBLIC_METHOD int NetMsgType()
{
	return bbNetMsgType();
}

PUBLIC_METHOD int NetMsgFrom()
{
	return bbNetMsgFrom();
}

PUBLIC_METHOD int NetMsgTo()
{
	return bbNetMsgTo();
}

PUBLIC_METHOD void NetMsgData_internal(char* ret, int retLen)
{
	BBStr* d = bbNetMsgData();
	strcpy_s(ret, retLen, d->c_str());
	freeBBStr(d);
}