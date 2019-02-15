


#include <iostream>

#include "TaskList.h"
#include "ActionPlaner.h"

namespace taskPlanerNamespace
{
	using namespace std;

	TaskList::TaskList()
	{
		actionPtrIndex = 0;
	}

	TaskList::~TaskList()
	{
	}

	const int TaskList::addListElement( const string& actionName, 
										const string& actionParameter,
										const int& actionRunTimeThreshold)
	{
		ActionPlaner addedAction;
		addedAction.actoinName = actionName;
		addedAction.actionParameter = actionParameter;
		addedAction.actionState = "READY";
		addedAction.actionRunTimeThreshold = actionRunTimeThreshold;
		actionList.push_back(addedAction);
		return 0;
	}

	const int TaskList::deleteListElement(const int& actionIndex)
	{
		if(actionIndex>=0 && actionIndex<actionList.size())
			actionList.erase(actionList.begin()+actionIndex);
		else
		{
			cout << "delete index is out of range" << endl;
			return -1;
		}
		return 0;
	}

	const int TaskList::movePtrToNext()
	{
		if(actionPtrIndex < actionList.size()-1)
			actionPtrIndex++;
		else
		{
			cout << "actionPtr is at the end of acitonList" << endl;
			return -1;
		}
		return 0;
	}

	const int TaskList::movePtrToLast()
	{
		if(actionPtrIndex != 0)
			actionPtrIndex--;
		else
		{
			cout << "actionPtr is at the head of acitonList" << endl;
			return -1;
		}
		return 0;
	}

	const int TaskList::movePtrToHead()
	{
		actionPtrIndex = 0;
		return 0;
	}

	const int TaskList::movePtrToEnd()
	{
		actionPtrIndex = actionList.size()-1;
		return 0;
	}

	const string TaskList::getPtrActionName() const
	{
		if(actionList.empty())
		{
			cout << "actionList is empty" << endl;
			return "";
		}
		else
		{
			return actionList[actionPtrIndex].actoinName;
		}
	}

	const string TaskList::getPtrActionPara() const
	{
		if(actionList.empty())
		{
			cout << "actionList is empty" << endl;
			return "";
		}
		else
		{
			return actionList[actionPtrIndex].actionParameter;
		}
	}

	const int TaskList::getPtrActionRuntimeThresh() const
	{
		if(actionList.empty())
		{
			cout << "actionList is empty" << endl;
			return -1;
		}
		else
		{
			return actionList[actionPtrIndex].actionRunTimeThreshold;
		}
	}

	const int TaskList::getPtrIndex() const
	{
		return actionPtrIndex;
	}

	const int TaskList::printList() const
	{
		if(actionList.empty())
		{
			cout << "actionList is empty" << endl;
			return -1;
		}
		else
		{
			for(int i(0); i<actionList.size(); i++)
			{
				cout << "actoinName:" << actionList[i].actoinName << endl;
				cout << "actionParameter:" <<actionList[i].actionParameter << endl;
				cout << "actionState:" <<actionList[i].actionState << endl;
				cout << "actionRunTimeThreshold:" <<actionList[i].actionRunTimeThreshold << endl;
				cout << endl;
			}
			cout << "******** end of list ********" << endl;
			return 0;
		}
	}

	const int TaskList::isEmpty() const
	{
		if(actionList.empty())
			return 1;
		else
			return 0;
	}


}