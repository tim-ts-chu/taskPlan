
#ifndef TASKPRIORITYQUEUE_H
#define TASKPRIORITYQUEUE_H

#include <string>
#include <vector>
#include <map>

#include "ChuThread.h"
#include "TaskIpc.h"

namespace taskPlanerNamespace
{
	using namespace std;

	struct QueueStruct
	{
		bool isQueueExecute;		// true: means the queue is executing
		bool isQueuePause;			// true: means hte queue need to be pause
		multimap<int, bool, greater<int> > interruptFlag;	// true: means the task can be interrupe, else is not
		multimap<int, string, greater<int> > taskQueue;		// Save the priority and task name	
	};

	class TaskPriorityQueue : public chuThreadNamespace::ChuThread<int, QueueStruct>
	{

	public:

		TaskPriorityQueue();							// Initialize the flags
		~TaskPriorityQueue();							// Do nothing

		const int executeTaskQueue();					// Execute all task in queue
		const int terminateTaskQueue();					// Stop the executing queue when finished the current task
		const int queueClear();							// Abort all task when the task queue is not in executing
		const int queueDelete();						// Stop top task in queue and pop it  
		
		const int queueInsert(	const int priority,		// Insert one task in queue
								const string taskName,
								const bool isInterrupt);			

		void thread();									// Multi-thread for executing the taskQueue

		const int printOutAllTask();					// Only for debug

	private:
														// Push an task into the taskQueue
		const int push(const int priority, const string taskName, const bool isInterrupt);
		const int pop();								// Pop the top task out of taskQueue

		const int pauseTaskQueue();						// Pause the executing queue but not terminate
		const int resumeTaskQueue();					// Resume the pause executing queue 
		
		const int abortCurrentTaskAndStopThread();		// Stop the current running thread

		//const int deleteByPriority(const int priority);
		//const int deleteByName(const string elementName);

		QueueStruct tempQueueStruct;
		//TaskIpc taskIpc;
		
	};
}

#endif

