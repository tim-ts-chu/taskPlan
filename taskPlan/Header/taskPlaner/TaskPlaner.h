

#ifndef TASKPLANER_H
#define TASKPLANER_H

#include "TaskIpc.h"
#include "TaskList.h"
#include "TaskApRemoteCtrl.h"

namespace taskPlanerNamespace
{

	class TaskPlaner
	{

	public:
		TaskPlaner();
		virtual const int addActionToTask() = 0;	/// Define actions in base class
		const int doTask();							/// Do the actions in task sequencely
		const string taskPlanMsgPaser(int msgState);/// Just transform the enum into string
		
	protected:

		TaskList actionList;						/// Save the all acitons in here

	private:

		const int initializeTask();					/// Check actionList & start action planer remotely 
		const int executeTask();					/// Execute actions sequencely
		const int finishTask();						/// Check is action kill | force kill remotely
		
		//TaskIpc ipc;								/// Ipc component 
		TaskApRemoteCtrl apRemortController;		/// Remote contral component

		int initializeTime;
		int timeoutOfReady;
		int timeoutOfRunning;
		int timeoutOfKill;
	};
}

#endif //TASKPLANER_H