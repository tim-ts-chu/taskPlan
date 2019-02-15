

#include <cstring>
#include <iostream>
#include <ctime>
#include "TaskIpc.h"
#include "Client.h"


namespace taskPlanerNamespace
{
	using namespace std;

	//HANDLE TaskIpc::mutex = CreateMutex( NULL, FALSE, NULL);    
	short TaskIpc::receiveFlag = 0;
	short TaskIpc::connectFlag = 0;

	/*TaskIpc::TaskIpc(string serverName)
	{   
		server = serverName;
		init_comm();
		connect_to_server(server.c_str());
		publish( ACTION_APSTATE, TOTAL_MSG_NUM);
		subscribe( RESULT_APSTATE, TOTAL_MSG_NUM );
		listen();
	}*/
	
	/*TaskIpc::TaskIpc()
	{
		server = "localhost";
		init_comm();
		connect_to_server(server.c_str());
		publish( ACTION_APSTATE, TOTAL_MSG_NUM);
		subscribe( RESULT_APSTATE, TOTAL_MSG_NUM );
		listen();
	}*/

	/*TaskIpc::~TaskIpc()
	{
		disconnect_to_server();
	}*/

	const int TaskIpc::conncetServer()
	{
		if(connectFlag==0)
		{
			connectFlag = 1;	// set connectFlag
			init_comm();
			connect_to_server("localhost");
			publish( ACTION_APSTATE, RESULT_APSTATE, TOTAL_MSG_NUM);
			subscribe( RESULT_APSTATE, TOTAL_MSG_NUM );
			listen();
		}

		return 0;
	}

	const int TaskIpc::disConncetServer()
	{
		if(connectFlag==1)
			disconnect_to_server();
		return 0;
	}
	
	const int TaskIpc::sendActionMgr(const string& actionName, 
									 const string& parameter,
									 const ApState& state)
	{
		if(connectFlag==0)
			conncetServer();

		Action_apStateMgr mgr;
		strcpy(mgr.apName, actionName.c_str());
		strcpy(mgr.argument, parameter.c_str());
		mgr.state = state;
		setAction_apState(mgr);
		sendAction_apState(mgr);
		cout << "send Action_apStateMgr to: " << actionName << endl;
		return 0;
	}

	const int TaskIpc::sendResultMgr(const string& actionName, 
									 const ApState& state)
	{
		if(connectFlag==0)
			conncetServer();

		Result_apStateMgr mgr;
		strcpy(mgr.apName, actionName.c_str());
		mgr.state = state;
		setResult_apState(mgr);
		sendResult_apState(mgr);
		cout << "send Result_apStateMgr to: " << actionName << endl;
		return 0;
	}

	const int TaskIpc::receiveResultMgr(const int timeThreshold, 
		                                Result_apStateMgr& mgr)
	{
		int startTime;
		int currentTime;

		// initialize
		if(receiveFlag!=0)
			receiveFlag = 0;

		if(connectFlag==0)
			conncetServer();

		startTime = time(NULL);
		currentTime = time(NULL);
	
		// busy wait
		while(currentTime - startTime < timeThreshold)
		{
			if(receiveFlag==1)
			{
				cout << "receive message" << endl;
				getResult_apState(mgr);
				return 0;
			}
			Sleep(100);
			currentTime = time(NULL);
		}

		cout << "receive timeout" << endl;
		return -1;
	}

}