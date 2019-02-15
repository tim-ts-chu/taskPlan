

#ifndef TASKAPREMORTECTRL_H
#define TASKAPREMORTECTRL_H

#include <string>

namespace taskPlanerNamespace
{
	using namespace std;

		class TaskApRemoteCtrl
	{
	public:

		void executeActionPlaner(string actionName);
		void killActionPlaner(string actionName);

	private:

	};
}

#endif //TASKAPREMORTECTRL_H