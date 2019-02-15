/******************************************************
NTU EECS Advanced Control Lab, Intelligent Robot Lab

2010 Kuo-Chen Huang
2012 Ming-Fang Chang 
	 add Action/Result mgrs

******************************************************/

#ifndef MESSAGE_H
#define MESSAGE_H

#include <stdio.h>
#include <cstring>

//--------------------------------------------------//
// define the message structures of each sensor data
//--------------------------------------------------//

class PoseMsg{
public:
	PoseMsg(){}
	PoseMsg( double i_x, double i_y, double i_theta ) : x(i_x), y(i_y), theta(i_theta) {}
	double x;
	double y;
	double theta;
};

typedef PoseMsg Pose;
typedef PoseMsg SubgoalMgr;
typedef PoseMsg LaserPoseMgr;

#define LASERPOSE_NAME "LaserPoseMgr"
#define LASERPOSE_FORMAT "{double, double, double}"

#define SUBGOAL_NAME "SubgoalMgr"
#define SUBGOAL_FORMAT "{double, double, double}"

// small laser
#define SLASER_NUM 541
class SLaser{
public:
	SLaser(){memset(range,0,SLASER_NUM);}
	int range[SLASER_NUM];
};

typedef SLaser VSLaserMgr;
#define SLASER_NAME "SLaserMgr"
#define SLASER_FORMAT "{[int:541]}"

typedef SLaser SLaserMgr;
#define VSLASER_NAME "VSLaserMgr"
#define VSLASER_FORMAT "{[int:541]}"

#define URG_LASER_NUM 682
class URGLaser{
public:
	URGLaser(){memset(range,0,URG_LASER_NUM);}
	int range[URG_LASER_NUM];
};
#define URGLASER_NAME "URGLaserMgr"
#define URGLASER_FORMAT "{[int:682]}"


// odometry
class OdometryMgr{
public:
	double x;
	double y;
	double theta;
	double velocity;
	double angularVelocity;
};
#define ODOMETRY_NAME "OdometryMgr"
#define ODOMETRY_FORMAT "{double, double, double, double, double}"

// motor
class MotorMgr{
public:
	double lEncoder;
	double rEncoder;
};
#define MOTOR_NAME "MotorMgr"
#define MOTOR_FORMAT "{double, double}"

//SpeedMode
class SpeedModeMgr{
public:
	int x;
};
#define SPEEDMODE_NAME "SpeedModeMgr"
#define SPEEDMODE_FORMAT "{int}"

//HeadMotor
class HeadMotorMgr{
public:
	int x;
};
#define HEADMOTOR_NAME "HeadMotorMgr"
#define HEADMOTOR_FORMAT "{int}"

// Hand
class HandPoseMgr{
public:
	int HPos;
};
#define HANDPOS_NAME "HandPoseMgr"
#define HANDPOS_FORMAT "{int}"

// facial expression
class FacialExpMgr{
public:
	int state;
};
#define FACIAlEXP_NAME "FacialExpMgr"
#define FACIAlEXP_FORMAT "{int}"

// microphone--19
class MicMgr{
public:
	int input;
	int Rchannel;
	int Lchannel;
};

typedef MicMgr Mic19Mgr;
typedef MicMgr Mic20Mgr;
typedef MicMgr Mic21Mgr;
typedef MicMgr Mic22Mgr;

#define MIC19_NAME "Mic19Mgr"
#define MIC19_FORMAT "{int, int, int}"

#define MIC20_NAME "Mic20Mgr"
#define MIC20_FORMAT "{int, int, int}"

#define MIC21_NAME "Mic21Mgr"
#define MIC21_FORMAT "{int, int, int}"

#define MIC22_NAME "Mic22Mgr"
#define MIC22_FORMAT "{int, int, int}"

class StateMgr{
public: 
	char status[256];
	//char webcontrol[256];

};

#define STATE_NAME "StateMgr"
#define STATE_FORMAT "{[char:256]}"

class GoalMgr{
public: 
	char room[256];
	double x;
	double y;
	double theta;
};
#define GOAL_NAME "GoalMgr"
#define GOAL_FORMAT "{ [char:256], double, double, double}"

#define MAX_PEOPLE  10
class PeopleMgr{
public:
	PeopleMgr():count(0){
		memset(x,0,MAX_PEOPLE*sizeof(float));
		memset(y,0,MAX_PEOPLE*sizeof(float));
		memset(vel,0,MAX_PEOPLE*sizeof(float));
		memset(theta,0,MAX_PEOPLE*sizeof(float));
	}
	float count;
	float x[MAX_PEOPLE];
	float y[MAX_PEOPLE];
	float vel[MAX_PEOPLE];
	float theta[MAX_PEOPLE];
};
#define PEOPLE_NAME "PeopleMgr"
#define PEOPLE_FORMAT "{float, [float:10], [float:10], [float:10], [float:10]}"

class WordMgr{
public:
	char keyword[256];
};
#define WORD_NAME "WordMgr"
#define WORD_FORMAT "{ [char:256]}"

class Detect{
public:
	int x;
	int y;
};
#define DETECT_NAME "Detect"
#define DETECT_FORMAT "{int, int}"

// loc state : LOC_INIT, LOC_OK, LOC_FAILURE
class LocState{
public:
	LocState(){ sprintf( state, "LOC_INIT"); }
	char state[16];
};
#define LOCSTATE_NAME "LocState"
#define LOCSTATE_FORMAT "{[char:16]}"

class SpeakMgr{
public:
	char words[256];
};
#define SPEAK_NAME "SpeakMgr"
#define SPEAK_FORMAT "{ [char:256]}"

typedef enum { MANUAL_MODE, AUTO_MODE } NAVI_MODE;
typedef enum { NO_OP, UP, DOWN, LEFT, RIGHT } MANUAL_DIRECTION;

/*
class ManualControlCommand(){
public:
	ManualControlCommand() : direction(NO_OP){}
	MANUAL_DIRECTION direction;
}
typedef ManualControlCommand ManualDirectionMsg
#define MANUALDIRECTMSG_NAME "ManualDirectionMsg"
*/

class NaviParMsg{
public:
	NaviParMsg() : NaviMode(AUTO_MODE), Map_Enable(true), GoalSeeking_Enable(true), ObstacleAvoidance_Enable(true),
	PathPlanning_Enable(true), ND_Enable(true), Localization_Enable(true){}

	NAVI_MODE NaviMode;
	int dummy;

	bool Map_Enable;
	bool GoalSeeking_Enable;
	bool ObstacleAvoidance_Enable;
	bool PathPlanning_Enable;
	bool ND_Enable;
	bool Localization_Enable;

	// Manual
	double M_LinearV;
	double M_AngularV;
	//int Manual_Direction;
	// Auto
	double A_LinearV;
	double A_AngularV;
	double MaxLinearV;
	double MaxAngularV;
	double Kv;
	double Kw;
	double Ke;
	double ActiveRange;
	double DeadZoneRange;
	double LeftBalance;
	double AngleBalance;
	double TotalBalance;
};
#define NAVIPAR_MSG "NaviParMsg"
#define NAVIPAR_MSG_FORMAT "{double, byte, byte, byte, byte, byte, byte, byte, byte, double, double, double, double, double, double, double, double, double, double, double, double, double, double}"

//typedef enum { MANUAL_MODE, AUTO_MODE } NAVI_MODE;
//typedef enum { NO_OP, UP, DOWN, LEFT, RIGHT } MANUAL_DIRECTION;

typedef enum {WAITING_FOR_BEGINNING, EXECUTING, FINISHED, ERRORING, RECOVERING} CURRENT_STATUS;
typedef enum {GENERAL, TO_POINT, HUMAN_FOLLOWING, HUMAN_GUIDING, CONTROL_BY_IPC, CONTROL_BY_KEYBOARD } NAVI_ACTIONS;

class Action_Navi{
public:
	int action_name; //NAVI_ACTIONS
};
#define ACTION_NAVI_NAME "Action_Navi"
#define ACTION_NAVI_FORMAT "{ int }"


class Result_Navi{
public:
	int current_status; //CURRENT_STATUS
	int action_name; // NAVI_ACTIONS
};

#define RESULT_NAVI_NAME "Result_Navi"
#define RESULT_NAVI_FORMAT "{int, int}"

class ServerVelMgr{
public:
	int RVel; 
	int LVel;
};

#define SERVER_VEL_NAME "Server_Vel"
#define SERVER_VEL_FORMAT "{int, int}"

class PoseModeMgr{
public:
	int pose_name; //NAVI_ACTIONS
};
#define POSE_MODE_NAME "PoseModeMgr"
#define POSE_MODE_FORMAT "{ int }"


typedef enum {
	AP_READY,
	AP_RUNNING,
	AP_RECOVERING,
	AP_FINISH,
	AP_FAIL,
	AP_KILL
} ApState;

class Action_apStateMgr {
public:
	char apName[16];
	char argument[128];
	ApState state;
};

#define ACTION_APSTATE_NAME "Action_apStateMgr"
#define ACTION_APSTATE_FORMAT "{[char:16],[char:128], int}"

class Result_apStateMgr {
public:
	char apName[16];
	ApState state;
};

#define RESULT_APSTATE_NAME "Result_apStateMgr"
#define RESULT_APSTATE_FORMAT "{[char:16], int}"

#endif
