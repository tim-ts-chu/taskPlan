
#ifndef TASKLIST_H
#define TASKLIST_H

#include <vector>
#include <string>
#include "ActionPlaner.h"

namespace taskPlanerNamespace
{
	using namespace std;

	class TaskList
	{
	public:

		TaskList();
		~TaskList();

		const int addListElement( const string& actionName, 
			                      const string& actionParameter,
								  const int& actionRunTimeThreshold);				  
			
		const int deleteListElement(const int& actionIndex);
		const int movePtrToNext();
		const int movePtrToLast();
		const int movePtrToHead();
		const int movePtrToEnd();
		const string getPtrActionName() const;
		const string getPtrActionPara() const;
		const int getPtrActionRuntimeThresh() const;
		const int getPtrIndex() const;
		const int printList() const;
		const int isEmpty() const;


	private:


		vector <ActionPlaner> actionList;
		vector <string> actionState;
		int actionPtrIndex;

	};
}

#endif //TASKLIST_H