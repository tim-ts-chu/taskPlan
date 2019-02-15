
/******************************************************
NTU EECS Advanced Control Lab, Intelligent Robot Lab

2010 Kuo-Chen Huang

******************************************************/
#ifndef IPC_CLIENT_H
#define IPC_CLIENT_H

#include "Comm.h"
#include "Thread.h"
#include "ipc.h"
#include <string>

using std::string;

namespace ROBOT{

class MsgInfo{
public:
	MsgInfo(){}
	MsgInfo( string n, string f, HANDLER_TYPE ptr ){
		msg_name = n;
		msg_format = f;
		msg_handler = ptr;
	}
	string msg_name;
	string msg_format;
	HANDLER_TYPE msg_handler;
};

class ClientThread: public Thread {
public:
	ClientThread() {}
	virtual void* run() {
		while(!shouldStop()){
			IPC_listenClear(10);
			yield();
		}
		return 0;
	}
};

} // namespace

#endif
