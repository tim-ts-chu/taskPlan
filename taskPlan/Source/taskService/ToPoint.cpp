

#include "ToPoint.h"

namespace taskPlanerNamespace
{
	const int ToPoint::addActionToTask()
	{
		actionList.addListElement("ToPoint", "3.0 4.0 -90.0", INT_MAX/*60*/);
		//actionList.addListElement("Wander", "para1", 5);
		//actionList.addListElement("Wander", "para1", 5);

		return 0;
	}	
}