

#include <string>
#include <iostream>

#include "TaskApRemoteCtrl.h"

namespace taskPlanerNamespace
{
	using namespace std;

	void TaskApRemoteCtrl::executeActionPlaner(string actionName)
	{
		string psexecDir, psexecHost, psexecUser, psexecPswd;
		string psexecParam, psexecProgDir, psexecProgName; 
		string systemCallParam;

		/*	Global Variable in This Function	*/

		psexecDir = ".\\Library\\PSTools\\psexec ";
		psexecParam = "/accepteula -d -i 1 ";

		/*	Local Variable for Each Situation	*/

		if(actionName == "Wander")
		{
			psexecHost		= "\\\\192.168.11.4 ";
			psexecUser		= "-u robot ";
			psexecPswd		= "-p robot ";
			psexecProgDir	= "-w C:\\Users\\robot\\Desktop\\Wander_ActionPlanner_v0.68\\Debug\\ ";
			psexecProgName	= "C:\\Users\\robot\\Desktop\\Wander_ActionPlanner_v0.68\\Debug\\Wander_ActionPlanner.exe ";
		}
		else if(actionName == "ToPoint")
		{
			psexecHost		= "\\\\192.168.11.4 ";
			psexecUser		= "-u robot ";
			psexecPswd		= "-p robot ";
			psexecProgDir	= "-w C:\\Users\\robot\\Desktop\\Topoint_Debug\\ ";
			psexecProgName	= "C:\\Users\\robot\\Desktop\\Topoint_Debug\\ToPoint.exe ";
		}
		else if(actionName == "GraspingObject")
		{
			psexecHost		= "\\\\192.168.11.2 ";
			psexecUser		= "-u robot ";
			psexecPswd		= "-p robot ";
			psexecProgDir	= "-w C:\\Users\\robot\\Desktop\\Shao-Ting\\HeadArm_competition\\Release\\ ";
			psexecProgName	= "C:\\Users\\robot\\Desktop\\Shao-Ting\\HeadArm_competition\\Release\\HeadArm.exe ";
		}
		else if(actionName == "MakingService")
		{
			psexecHost		= "\\\\192.168.11.4 ";
			psexecUser		= "-u robot ";
			psexecPswd		= "-p robot ";
			psexecProgDir	= "-w C:\\Users\\robot\\Desktop\\MakingService\\MakingService\\Debug\\ ";
			psexecProgName	= "C:\\Users\\robot\\Desktop\\MakingService\\MakingService\\Debug\\MakingService.exe ";
		}
		else if(actionName == "Calendar")
		{
			psexecHost		= "\\\\192.168.11.4 ";
			psexecUser		= "-u robot ";
			psexecPswd		= "-p robot ";
			psexecProgDir	= "-w C:\\Users\\robot\\Desktop\\MakingService\\MakingService\\Debug\\ ";
			psexecProgName	= "C:\\Users\\robot\\Desktop\\MakingService\\MakingService\\Debug\\MakingService.exe ";
		}
		else if(actionName == "CallSkype")
		{
			psexecHost		= "\\\\192.168.11.4 ";
			psexecUser		= "-u robot ";
			psexecPswd		= "-p robot ";
			psexecProgDir	= "-w C:\\Users\\robot\\Desktop\\MakingService\\MakingService\\Debug\\ ";
			psexecProgName	= "C:\\Users\\robot\\Desktop\\MakingService\\MakingService\\Debug\\MakingService.exe ";
		}
		else if(actionName == "Asking")
		{
			psexecHost		= "\\\\192.168.11.4 ";
			psexecUser		= "-u robot ";
			psexecPswd		= "-p robot ";
			psexecProgDir	= "-w C:\\Users\\robot\\Desktop\\MakingService\\MakingService\\Debug\\ ";
			psexecProgName	= "C:\\Users\\robot\\Desktop\\MakingService\\MakingService\\Debug\\MakingService.exe ";
		}
		else
		{
			cout << "Wrong Action name:" <<  actionName << endl;
			cout << "Can't remote start program." << endl;
			return;
		}

		cout << "Remote Start: " << actionName << endl;
		systemCallParam = psexecDir + psexecHost + psexecUser + psexecPswd + 
			              psexecParam + psexecProgDir + psexecProgName;

		//cout << "systemCallParam:" << systemCallParam << endl;				// for degub
		cout << endl << "******************** PSEXEC ********************" << endl;
		system(systemCallParam.c_str());
		cout << endl << "************************************************" << endl << endl;
		// For debug
		/*system(".\\Library\\PSTools\\psexec /accepteula \\\\192.168.11.4 -u robot -p robot -d -i 1 "
		"-w C:\\Users\\robot\\Desktop\\Topoint_Debug\\ "
		"C:\\Users\\robot\\Desktop\\Topoint_Debug\\ToPoint.exe */

		/*system(".\\Library\\PSTools\\psexec /accepteula \\\\192.168.11.2 -u robot -p robot -d -i 1 "
		"-w C:\\Users\\robot\\Desktop\\Shao-Ting\\HeadArm_competition\\Release\\ "
		" C:\\Users\\robot\\Desktop\\Shao-Ting\\HeadArm_competition\\Release\\HeadArm.exe ");*/
		return;
	}

	void TaskApRemoteCtrl::killActionPlaner(string actionName)
	{

		string pskillDir, pskillHost, pskillUser, pskillPswd;
		string pskillParam, pskillProgName; 
		string systemCallParam;

		/*	Global Variable in This Function	*/

		pskillDir = ".\\Library\\PSTools\\pskill ";
		pskillParam = "";

		/*	Local Variable for Each Situation	*/

		if(actionName == "Wander")
		{
			pskillHost		= "\\\\192.168.11.4 ";
			pskillUser		= "-u LabUser ";
			pskillPswd		= "-p newaclab ";
			pskillProgName	= "Wander_ActionPlanner.exe ";
		}
		else if(actionName == "ToPoint")
		{
			pskillHost		= "\\\\192.168.11.4 ";
			pskillUser		= "-u robot ";
			pskillPswd		= "-p robot ";
			pskillProgName	= "ToPoint.exe ";
		}
		else if(actionName == "GraspingObject")
		{
			pskillHost		= "\\\\192.168.11.2 ";
			pskillUser		= "-u robot ";
			pskillPswd		= "-p robot ";
			pskillProgName	= "HeadArm.exe ";
		}
		else if(actionName == "MakingService")
		{
			pskillHost		= "\\\\192.168.11.4 ";
			pskillUser		= "-u robot ";
			pskillPswd		= "-p robot ";
			pskillProgName	= "MakingService.exe ";
		}
		else if(actionName == "Calendar")
		{
			pskillHost		= "\\\\192.168.11.4 ";
			pskillUser		= "-u robot ";
			pskillPswd		= "-p robot ";
			pskillProgName	= "Calendar.exe ";
		}
		else if(actionName == "CallSkype")
		{
			pskillHost		= "\\\\192.168.11.4 ";
			pskillUser		= "-u robot ";
			pskillPswd		= "-p robot ";
			pskillProgName	= "CallSkype.exe ";
		}
		else if(actionName == "Asking")
		{
			pskillHost		= "\\\\192.168.11.4 ";
			pskillUser		= "-u robot ";
			pskillPswd		= "-p robot ";
			pskillProgName	= "Asking.exe ";
		}
		else
		{
			cout << "Wrong Action name:" <<  actionName << endl;
			cout << "Can't remote kill program." << endl;
			return;
		}

		cout << "Remote Kill: " << actionName << endl;
		systemCallParam = pskillDir + pskillHost + pskillUser + pskillPswd + 
			              pskillParam + pskillProgName;

		cout << endl << "******************** PSKILL ********************" << endl;
		system(systemCallParam.c_str());
		cout << "************************************************" << endl;

		return;
	}
}