
#include <iostream>
#include <vector>

#include <QtGui/QApplication>

#include "TaskPriorityQueue.h"
#include "taskServiceHeader.h"


int main(int argc, char *argv[])
{
	using namespace std;
	using namespace taskPlanerNamespace;

	TaskPriorityQueue tq;
	tq.executeTaskQueue();

	int input;
	while(1)
	{
		cin >> input;
		switch(input)
		{
		case 1:
			tq.queueInsert(10, "Welcome", true);
			break;
		case 2:
			tq.queueInsert(5, "Wander", true);
			break;
		case 3:
			tq.queueInsert(20, "TakeWater", true);
			break;
		case 4:
			tq.queueInsert(10, "Sign", true);
			break;
		case 5:
			tq.queueInsert(10, "Asking", true);
			break;
		case 6:
			tq.queueInsert(10, "CallSkype", true);
			break;
		case 7:
			tq.queueInsert(10, "Calendar", true);
		default:
			break;
		}
	}
	return 0;
}

