
#include "TaskPriorityQueue.h"
#include "TaskPlaner.h"
#include "TaskIpc.h"

#include "TakeWater.h"
#include "Wander.h"
#include "ToPoint.h"
#include "Welcome.h"
#include "Sign.h"
#include "Calendar.h"
#include "CallSkype.h"
#include "Asking.h"

namespace taskPlanerNamespace
{
	TaskPriorityQueue::TaskPriorityQueue()
	{
		tempQueueStruct.isQueueExecute = false;
		tempQueueStruct.isQueuePause = false;
		tempQueueStruct.interruptFlag.clear();
		tempQueueStruct.taskQueue.clear();
		setShareVariable(tempQueueStruct);
	}

	TaskPriorityQueue::~TaskPriorityQueue()
	{
	}

	const int TaskPriorityQueue::executeTaskQueue()
	{
		tempQueueStruct = getShareVariable();
		tempQueueStruct.isQueueExecute = true;
		setShareVariable(tempQueueStruct);
		this->startThread();
		cout << "Executing the task queue" << endl;
		return 0;
	}

	const int TaskPriorityQueue::terminateTaskQueue()
	{
		tempQueueStruct = getShareVariable();
		tempQueueStruct.isQueueExecute = false;
		setShareVariable(tempQueueStruct);
		cout << "Terminating the task queue" << endl;
		return 0;
	}

	const int TaskPriorityQueue::queueClear()
	{
		tempQueueStruct = getShareVariable();
		if(tempQueueStruct.isQueueExecute==false)
		{
			tempQueueStruct.interruptFlag.clear();
			tempQueueStruct.taskQueue.clear();
			tempQueueStruct.isQueuePause = false;
			setShareVariable(tempQueueStruct);
		}
		else
			cout << "The task is executing and can't be clear" << endl;
		return 0;
	}

	const int TaskPriorityQueue::queueDelete()
	{
		tempQueueStruct = getShareVariable();
		if(tempQueueStruct.taskQueue.size()!=0)			// check the queue is empty or not
		{
			if(tempQueueStruct.isQueueExecute==false)	// if the queue is not in processing
			{
				pop();
				cout << "Pop one task out" << endl;
			}
			else										// if the queue is in processing
			{	
				if(tempQueueStruct.interruptFlag.begin()->second==false)	// the executing task can't be interrupt
				{
					cout << "Sorry, the executing task can't be interrupt & return -1" << endl;
					return -1;
				}
				else									// the executing task can be interrupt
				{
					abortCurrentTaskAndStopThread();
					pop();
					startThread();
					cout << "The exeuting task is terminated and dropped" << endl;
				}
			}
		}
		else
			cout << "The queue is empty." << endl;

		return 0;
	}

	const int TaskPriorityQueue::queueInsert(const int priority, const string taskName, const bool isInterrupt)
	{
		tempQueueStruct = getShareVariable();
		if(tempQueueStruct.isQueueExecute==false)	// The queue is not in processing
		{
			push(priority, taskName, isInterrupt);
			cout << "Insert the " << taskName << " after the current task" << endl;
		}
		else										// The queue is in processing
		{
			if(tempQueueStruct.taskQueue.empty())
			{
				//abortCurrentTaskAndStopThread();
				push(priority, taskName, isInterrupt);	// directly insert
				//startThread();
				cout << "Insert the " << taskName << " in the current empty task" << endl;
			}
			else if( priority > (tempQueueStruct.taskQueue.begin()->first) ) // insert priority larger than the executeing task
			{
				if(tempQueueStruct.interruptFlag.begin()->second==false)	// if the executing task can't be interrupt
				{
					cout << "Sorry, the executing task can't be interrupt & return -1" << endl;
					cout << "Please decrease the task priority and insert again" << endl;
					return -1;
				}
				else		// if the executing task can be interrupt
				{
					//abortCurrentTaskAndStopThread();
					//int currentPriority(tempQueueStruct.taskQueue.begin()->first);				// save current task state
					//string currentTaskName(tempQueueStruct.taskQueue.begin()->second);	
					//bool cruuentInterruptFlag(tempQueueStruct.interruptFlag.begin()->second);
					
					TaskIpc::sendResultMgr("TaskPriorityQueue", AP_FAIL);	// abort current task
					cout << "The current task is aborted by higher priority task" << endl;
					
					pauseTaskQueue();
					push(priority, taskName, isInterrupt);	// and insert new higher priority task, but did't pop originial task
					push(priority, taskName, isInterrupt);	// insert two times, because one will be pop after execute task

					//push(currentPriority, currentTaskName, cruuentInterruptFlag);
					//startThread();
					cout << "Insert the " << taskName << " before the current task" << endl;
					resumeTaskQueue();
				}
			}
			else			// insert priority smaller than the executeing task
			{
				push(priority, taskName, isInterrupt);	// directly insert
				cout << "Insert the " << taskName << " after the current task" << endl;
			}	
		}
		return 0;
	}

	const int TaskPriorityQueue::push(const int priority, const string TaskName, const bool isInterrupt)
	{
		tempQueueStruct = getShareVariable();
		tempQueueStruct.taskQueue.insert(pair<int, string>(priority, TaskName));
		tempQueueStruct.interruptFlag.insert(pair<int, bool>(priority, isInterrupt));
		setShareVariable(tempQueueStruct);
		return 0;
	}

	const int TaskPriorityQueue::pop()
	{
		tempQueueStruct = getShareVariable();
		if(tempQueueStruct.taskQueue.size()!=0)
		{
			tempQueueStruct.taskQueue.erase(tempQueueStruct.taskQueue.begin());
			tempQueueStruct.interruptFlag.erase(tempQueueStruct.interruptFlag.begin());
			setShareVariable(tempQueueStruct);
		}
		else
			cout << "The queue is already empty." << endl;
		return 0;
	}

	const int TaskPriorityQueue::pauseTaskQueue()
	{
		tempQueueStruct = getShareVariable();
		tempQueueStruct.isQueuePause = true;
		setShareVariable(tempQueueStruct);
		return 0;
	}

	const int TaskPriorityQueue::resumeTaskQueue()
	{
		tempQueueStruct = getShareVariable();
		tempQueueStruct.isQueuePause = false;
		setShareVariable(tempQueueStruct);
		return 0;
	}

	/*const int TaskPriorityQueue::deleteByPriority(const int priority)
	{
		tempQueueStruct = getShareVariable();
		if(tempQueueStruct.taskQueue.size()!=0)
		{
			multimap<int, string>::iterator queueIt;
			multimap<int, bool>::iterator flagIt;
			queueIt = tempQueueStruct.taskQueue.find(priority);
			flagIt = tempQueueStruct.interruptFlag.find(priority);
			if(queueIt != tempQueueStruct.taskQueue.end())
			{
				tempQueueStruct.taskQueue.erase(queueIt);
				tempQueueStruct.interruptFlag.erase(flagIt);
				setShareVariable(tempQueueStruct);
			}
			else
				cout << "Can't not find the task in protrity " << priority << endl;
		}
		else
			cout << "The queue is empty." << endl;
		return 0;
	}*/

	/*const int TaskPriorityQueue::deleteByName(const string elementName)
	{
		tempQueueStruct = getShareVariable();
		if(tempQueueStruct.taskQueue.size()!=0)
		{
			multimap<int, string>::iterator queueIt;
			multimap<int, bool>::iterator flagIt;

			flagIt = tempQueueStruct.interruptFlag.begin();
			for(queueIt=tempQueueStruct.taskQueue.begin(); queueIt!=tempQueueStruct.taskQueue.end(); queueIt++)
			{
				if(queueIt->second == elementName)
					break;
				flagIt++;
			}
			if(queueIt != tempQueueStruct.taskQueue.end())
			{
				tempQueueStruct.taskQueue.erase(queueIt);
				tempQueueStruct.interruptFlag.erase(flagIt);
				setShareVariable(tempQueueStruct);
			}
			else
				cout << "Can't not find the task in elementName " << elementName << endl;
		}
		else
			cout << "The queue is empty." << endl;
		return 0;
	}*/

	/* The Print Function is Only for Debug	*/
	const int TaskPriorityQueue::printOutAllTask()
	{
		tempQueueStruct = getShareVariable();
		multimap<int, string, greater<int> >::iterator queueIt;
		multimap<int, bool, greater<int> >::iterator flagIt;

		if(tempQueueStruct.taskQueue.size()!=0)
		{

			flagIt = tempQueueStruct.interruptFlag.begin();
			for(queueIt=tempQueueStruct.taskQueue.begin(); queueIt!=tempQueueStruct.taskQueue.end(); queueIt++)
			{
				cout << "task priority: " << queueIt->first << endl;
				cout << "task naem: " << queueIt->second << endl;
				cout << "task interrupt: " << flagIt->second << endl;
				cout << "######" << endl;
				flagIt++;
			}
		}
		else
			cout << "The queue is empty." << endl;

		return 0;
	}

	void TaskPriorityQueue::thread()
	{
		/*	Check All Kinds of Flag are in Correct or Not	*/
		while(getShareVariable().isQueueExecute==true)
		{
			if(getShareVariable().isQueueExecute==false)		// if the task queue is terminated
					abortCurrentTaskAndStopThread();

			while(getShareVariable().isQueuePause==true)		// check the queue is pause or not
			{
				if(getShareVariable().isQueueExecute==false)	// if the task queue is terminated
					abortCurrentTaskAndStopThread();
				Sleep(200);
			}

			string taskName;
			tempQueueStruct = getShareVariable();
			if(tempQueueStruct.taskQueue.size()!=0)		// if the queue is not empty, then execute task
			{
				taskName = tempQueueStruct.taskQueue.begin()->second;

				/*	The Switch to Parser All Kinds of Task Name	*/
				if(taskName=="TakeWater")
				{
					cout << "Do TakeWater" << endl;
					//Sleep(3000);
					taskPlanerNamespace::TakeWater task;
					task.doTask();
					while(getShareVariable().isQueuePause==true){Sleep(200);} // check the queue is pause or not
					pop();
				}
				else if(taskName=="ToPoint")
				{
					cout << "Do ToPoint" << endl;
					//Sleep(3000);
					taskPlanerNamespace::ToPoint task;
					task.doTask();
					while(getShareVariable().isQueuePause==true){Sleep(200);} // check the queue is pause or not
					pop();
				}
				else if(taskName=="Wander")
				{
					cout << "Do Wander" << endl;
					//Sleep(3000);
					taskPlanerNamespace::Wander task;
					task.doTask();
					while(getShareVariable().isQueuePause==true){Sleep(200);} // check the queue is pause or not
					pop();
				}
				else if(taskName=="Welcome")
				{
					cout << "Do Welcome" << endl;
					//Sleep(3000);
					taskPlanerNamespace::Welcome task;
					task.doTask();
					while(getShareVariable().isQueuePause==true){Sleep(200);} // check the queue is pause or not
					pop();
				}
				else if(taskName=="Sign")
				{
					cout << "Do Sign" << endl;
					//Sleep(3000);
					taskPlanerNamespace::Sign task;
					task.doTask();
					while(getShareVariable().isQueuePause==true){Sleep(200);} // check the queue is pause or not
					pop();
				}
				else if(taskName=="Calendar")
				{
					cout << "Do Calendar" << endl;
					//Sleep(3000);
					taskPlanerNamespace::Calendar task;
					task.doTask();
					while(getShareVariable().isQueuePause==true){Sleep(200);} // check the queue is pause or not
					pop();
				}
				else if(taskName=="CallSkype")
				{
					cout << "Do CallSkype" << endl;
					//Sleep(3000);
					taskPlanerNamespace::CallSkype task;
					task.doTask();
					while(getShareVariable().isQueuePause==true){Sleep(200);} // check the queue is pause or not
					pop();
				}
				else if(taskName=="Asking")
				{
					cout << "Do Asking" << endl;
					//Sleep(3000);
					taskPlanerNamespace::Asking task;
					task.doTask();
					while(getShareVariable().isQueuePause==true){Sleep(200);} // check the queue is pause or not
					pop();
				}
				else
				{
					cout << "taskName error: " << taskName << endl;
					pop();
				}
			}
			else
			{
				cout << "The queue is empty and doing nothing" << endl;
				Sleep(1000);
			}
			Sleep(200);
		}
	}

	const int TaskPriorityQueue::abortCurrentTaskAndStopThread()
	{
		//cout << CloseHandle(localhotHANDLE) << " " << true << endl;
		stopCurrentThread();
		cout << "abort current task thread" << endl;
		return 0;
	}
}