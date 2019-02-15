
#include <iostream>
#include <map>
#include "TaskPlaner.h"

namespace taskPlanerNamespace
{
	using namespace std;

	TaskPlaner::TaskPlaner()
	{
		initializeTime = 8;
		timeoutOfReady = 5;
		timeoutOfRunning = 5;
		timeoutOfKill = 5;
	}

	const int TaskPlaner::doTask()
	{
		if(initializeTask()==0)
		{
			if(executeTask()==0)
			{
				if(finishTask()==0)
				{
					cout << "doTask finish" << endl;
					return 0;
				}
				else
				{
					cout << "finishTask error" << endl;
					return -1;
				}
			}
			else
			{
				cout << "executeTask error" << endl;
				if(finishTask()==0)
				{
					cout << "doTask finish" << endl;
					return 0;
				}
				else
				{
					cout << "finishTask error" << endl;
					return -1;
				}
			}
		}
		else
		{
			cout << "initializeTask error" << endl;
			return -1;
		}
	}
	
	const int TaskPlaner::initializeTask()
	{
		cout << endl << "Enter initializeTask process" << endl;

		/*	Connect to Server	*/
		TaskIpc::conncetServer();

		/*	Add Action To Task	*/
		addActionToTask();
		
		/*	Check Action List Is Empty Or Not	*/
		if(actionList.isEmpty())
		{
			cout << "Don't have any acitonPlan be execute" << endl;
			return -1;
		}

		/*	Omit Repeat ActionName	*/
		actionList.movePtrToHead();
		string actionName;

		map<string, int> actionMap;
		map<string, int>::iterator actionMapIt;
		
		while(1)	
		{
			actionName = actionList.getPtrActionName();			// Put actionName to map
			actionMap.insert(pair<string,int>(actionName, 0));	// To avoid repeat actionName
			if(actionList.movePtrToNext()<0)
				break;
		}

		/*	Remote Start Action Planer	*/
		for(actionMapIt=actionMap.begin(); actionMapIt!=actionMap.end(); actionMapIt++)
		{
			actionName = actionMapIt->first;
			//apRemortController.executeActionPlaner(actionName); 
		}
		cout << "Waiting for action planers initialize..." << endl;
		Result_apStateMgr mgr;
		//TaskIpc::receiveResultMgr(initializeTime, mgr);
		if(TaskIpc::receiveResultMgr(initializeTime, mgr)==0)	// receive the message
		{
			cout << "Receive message in the initial process" << endl;
			if(mgr.state==AP_FAIL)
			{
				cout << "Receive AP_FAIL from: " << mgr.apName << endl;
				finishTask();			// dircetly enter the finish process
				return -1;
			}
		}
		//Sleep(initializeTime*1000);
		cout << "Action planners initialized" << endl;
		return 0;
	}

	const int TaskPlaner::executeTask()
	{
		int errorFlag(0);
		string actionName;
		string actionParam;
		int actionRunningThreshold;
		Result_apStateMgr mgr;
		
		cout << endl << "Enter executeTask process" << endl;

		/*	For All Action In ActionList	*/
		actionList.movePtrToHead();
		while(1)
		{
			actionName = actionList.getPtrActionName();
			actionParam = actionList.getPtrActionPara();
			actionRunningThreshold = actionList.getPtrActionRuntimeThresh();

			cout << endl << "Start to execute the actionPlaner: " << actionName << endl;

			/**** Ready state ****/
			TaskIpc::sendActionMgr(	actionName, actionParam, AP_READY);
			cout << "send action: " << actionName << "  READY" << endl;
			if(TaskIpc::receiveResultMgr(timeoutOfReady, mgr)<0)
			{
				cout << actionName << " Ready state timeout" << endl;
				errorFlag=1; break;
			}
			if(mgr.apName != actionName)
			{
				cout << actionName << " message action name error, receive:" << mgr.apName << " " << taskPlanMsgPaser(mgr.state) << endl;
				errorFlag=1; break;
			}
			if(mgr.state != AP_READY)
			{
				cout << actionName << " message action state error, receive:" << taskPlanMsgPaser(mgr.state) << endl;
				errorFlag=1; break;
			}
			cout << "receive message correct" << endl;

			/**** Running state ****/
			TaskIpc::sendActionMgr(	actionName, actionParam, AP_RUNNING);
			cout << "send action: " << actionName << "  RUNNING" << endl;
			if(TaskIpc::receiveResultMgr(timeoutOfRunning, mgr)<0)
			{
				cout << actionName << " Running state timeout" << endl;
				errorFlag=1; break;
			}
			if(mgr.apName != actionName)
			{
				cout << actionName << " message action name error, receive:" << mgr.apName << " " << taskPlanMsgPaser(mgr.state) << endl;
				errorFlag=1; break;
			}
			if(mgr.state!=AP_RUNNING)
			{
				cout << actionName << " message action state error, receive:" << taskPlanMsgPaser(mgr.state) << endl;
				errorFlag=1; break;
			}
			cout << "receive message correct" << endl;

			/**** Finish state ****/
			TaskIpc::sendActionMgr(	actionName, actionParam, AP_FINISH);
			cout << "send action: " << actionName << "  FINISH" << endl;
			if(TaskIpc::receiveResultMgr(actionRunningThreshold, mgr)<0)
			{
				cout << actionName << " Finish state timeout" << endl;
				errorFlag=1; break;
			}
			if(mgr.apName != actionName)
			{
				cout << actionName << " message action name error, receive:" << mgr.apName << " " << taskPlanMsgPaser(mgr.state) << endl;
				errorFlag=1; break;
			}
			if(mgr.state!=AP_FINISH)
			{
				cout << actionName << " message action state error, receive:" << taskPlanMsgPaser(mgr.state) << endl;
				errorFlag=1; break;
			}
			cout << "receive message correct" << endl;

			//if end of action list
			if(actionList.movePtrToNext()<0)
				break;

		}// while

		if(errorFlag==1)
		{
			cout << "Task error, and it's droped" << endl;
			return -1;
		}
		cout << "Task finish" << endl;
		return 0;
	}

	const int TaskPlaner::finishTask()
	{
		int errorFlag(0);
		Result_apStateMgr mgr;

		cout << endl << "Enter finishTask process" << endl;

		/*	Omit Repeat ActionName	*/
		actionList.movePtrToHead();
		string actionName;

		map<string, int> actionMap;
		map<string, int>::iterator actionMapIt;
		actionList.movePtrToHead();

		while(1)	
		{
			actionName = actionList.getPtrActionName();			// Put actionName to map
			actionMap.insert(pair<string,int>(actionName, 0));	// To avoid repeat actionName
			if(actionList.movePtrToNext()<0)
				break;
		}

		/*	Send Kill to All Action Planer	*/
		actionList.movePtrToHead();
		for(actionMapIt=actionMap.begin(); actionMapIt!=actionMap.end(); actionMapIt++)
		{
			actionName = actionMapIt->first;
			TaskIpc::sendActionMgr(	actionName, "", AP_KILL);
			cout << "send action: " << actionName << "  KILL" << endl;
			if( TaskIpc::receiveResultMgr(timeoutOfKill, mgr)<0)			// timeout of kill action planer
			{
				cout << "Kill " << actionName << " error, force kill" << endl;
				//apRemortController.killActionPlaner(actionName);	// remote kill
			}
			else if(mgr.apName != actionName)
			{
				cout << actionName << " message action name error, receive:" << mgr.apName << " " << taskPlanMsgPaser(mgr.state) << endl;
				cout << "Kill " << actionName << " error, force kill" << endl;
				//apRemortController.killActionPlaner(actionName);	// remote kill
			}
			else if(mgr.state != AP_KILL)
			{
				cout << actionName << " message action state error, receive:" << taskPlanMsgPaser(mgr.state) << endl;
				cout << "Kill " << actionName << " error, force kill" << endl;
				//apRemortController.killActionPlaner(actionName);	// remote kill
			}
			else
			{
				cout << "receive message correct" << endl;
			}
			if(actionList.movePtrToNext()<0)	// the end of actionList
				break;
		}
		return 0;
	}

	const string TaskPlaner::taskPlanMsgPaser(int msgState)
	{
		switch(msgState)
		{
		case 0:
			return string("AP_READY");
		case 1:
			return string("AP_RUNNING");
		case 2:
			return string("AP_RECOVERING");
		case 3:
			return string("AP_FINISH");
		case 4:
			return string("AP_FAIL");
		case 5:
			return string("AP_KILL");
		default:
			return string("Error Msg Ap_state");
		}
	}
}

