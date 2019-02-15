
#ifndef ACTIONPLANER_H
#define ACTIONPLANER_H

#include <string>

namespace taskPlanerNamespace
{
	using namespace std;
	struct ActionPlaner
	{
		string actoinName;
		string actionParameter;
		string actionState;
		int actionRunTimeThreshold;	
	};
}

#endif	//ACTIONPLANER_H