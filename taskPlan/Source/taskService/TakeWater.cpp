

#include "TakeWater.h"

namespace taskPlanerNamespace
{
	const int TakeWater::addActionToTask()
	{
		actionList.addListElement("GraspingObject", "", INT_MAX);
		actionList.addListElement("Wander", "para1", 5);
		actionList.addListElement("GraspingObject", "", INT_MAX);
		//actionList.addListElement("Wander", "para1", 5);

		return 0;
	}	
}

