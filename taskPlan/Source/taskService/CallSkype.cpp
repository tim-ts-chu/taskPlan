

#include "CallSkype.h"

namespace taskPlanerNamespace
{
	const int CallSkype::addActionToTask()
	{
		actionList.addListElement("CallSkype", "10", INT_MAX);



		return 0;
	}	
}