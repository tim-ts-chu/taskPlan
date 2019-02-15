

#ifndef TASKIPC_H
#define TASKIPC_H

#include <string>

#include "Comm.h"
#include "ipc.h"

#include "windows.h"
#include "process.h"

namespace taskPlanerNamespace
{
	using namespace std;

	class TaskIpc
	{
	public:

		//TaskIpc(string serverName);
		//TaskIpc();
		//~TaskIpc();

		static const int conncetServer();
		static const int disConncetServer();
		//const int conncetServer(const string& serverName);
		
		static const int sendActionMgr(	const string& actionName, 
										const string& parameter,
										const ApState& state);

		static const int sendResultMgr(	const string& actionName, 
										const ApState& state);

		static const int receiveResultMgr(const int timeThreshold, 
			                                Result_apStateMgr& mgr);	// busy wait

		static const void setReceiveFlag(){receiveFlag = 1;};
	

		//static const void mutexLock(){WaitForSingleObject(mutex, INFINITE);};
		//static const void mutexRelease(){ReleaseMutex(mutex);};



	private:

		//static void timer(void*);
		//static HANDLE mutex;
		string server;
		static short receiveFlag;
		static short connectFlag;


	};
}

#endif //TASKIPC_H