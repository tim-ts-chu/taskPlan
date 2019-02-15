/******************************************************
NTU EECS Advanced Control Lab, Intelligent Robot Lab

2010 Kuo-Chen Huang

******************************************************/
#ifndef COMM_HPP
#define COMM_HPP

#include "Messages.h"

//--------------------------------------------------//
// message types
//--------------------------------------------------//
enum MessageType{ LASERPOSE, SLASER, URG, VSLASER, SUBGOAL, ODOMETRY, MOTOR, SPEED_MODE, HEAD_MOTOR, HAND_POSE,
FACIAL_EXP, STATE, GOAL, PEOPLE, KEYWORD, DETECT, LOC_STATE, SPEAK, NAVI_PAR, RESULT_NAVI, ACTION_NAVI, SERVER_VEL, POSE_MODE, ACTION_APSTATE, RESULT_APSTATE, TOTAL_MSG_NUM};

void init_comm();
void connect_to_server(const char* server_name = "localhost");
void disconnect_to_server();
void subscribe(MessageType, ...);
void publish(MessageType, ...);
void listen();

// get messages
void getLaserPose(LaserPoseMgr& mgr);
void getSLaser(SLaserMgr& mgr);
void getURGLaser(URGLaser& mgr);
void getVSLaser(VSLaserMgr& mgr);
void getSubgoal(SubgoalMgr& mgr);
void getOdometry(OdometryMgr& mgr);
void getMotor(MotorMgr& mgr);
void getSpeedMode(SpeedModeMgr&mgr);
void getHeadMotor(HeadMotorMgr& mgr);
void getHandPos(HandPoseMgr& mgr);
void getFacialExp(FacialExpMgr& mgr);
void getState(StateMgr& mgr);
void getGoal(GoalMgr& mgr);
void getPeople(PeopleMgr& mgr);
void getWord(WordMgr& mgr);
void getDetect(Detect& mgr);
void getLocState(LocState& mgr);
void getSpeak(SpeakMgr& mgr);
void getNaviParMsg( NaviParMsg& msg );
void getResultNavi(Result_Navi& msg);
void getActionNavi(Action_Navi & msg);
void getServerVel(ServerVelMgr & msg);
void getPoseMode(PoseModeMgr & msg);
void getAction_apState(Action_apStateMgr& mgr);
void getResult_apState(Result_apStateMgr& mgr);

// set messages
void setLaserPose(LaserPoseMgr& mgr);
void setLaserPose(LaserPoseMgr& lmgr, OdometryMgr& omgr);
void setSLaser(SLaserMgr& mgr);
void setURGLaser(URGLaser& mgr);
void setVSLaser(VSLaserMgr& mgr);
void setSubgoal(SubgoalMgr& mgr);
void setOdometry(OdometryMgr& mgr);
void setMotor(MotorMgr& mgr);
void setSpeedMode(SpeedModeMgr& mgr);
void setHeadMotor(HeadMotorMgr& mgr);
void setHandPose(HandPoseMgr& mgr);
void setFacialExp(FacialExpMgr& mgr);
void setState(StateMgr& mgr);
void setGoal(GoalMgr& mgr);
void setPeople(PeopleMgr& mgr);
void setWord(WordMgr& mgr);
void setDetect(Detect& mgr);
void setLocState(LocState& mgr);
void setSpeak(SpeakMgr& mgr);
void setNaviParMsg( NaviParMsg& msg );
void setResultNavi(Result_Navi& msg);
void setActionNavi(Action_Navi & msg);
void setServerVel( ServerVelMgr& msg );
void setPoseMode( PoseModeMgr& msg );
void setAction_apState(Action_apStateMgr& mgr);
void setResult_apState(Result_apStateMgr& mgr);

// send messages
int sendLaserPose(LaserPoseMgr& mgr);
int sendSLaser(SLaserMgr& mgr);
int sendURGLaser(URGLaser& mgr);
int sendVSLaser(VSLaserMgr& mgr);
int sendSubgoal(SubgoalMgr& mgr);
int sendOdometry(OdometryMgr& mgr);
int sendMotor(MotorMgr& mgr);
int sendSpeedMode(SpeedModeMgr& mgr);
int sendHeadMotor(HeadMotorMgr& mgr);
int sendHandPose(HandPoseMgr& mgr);
int sendFacialExp(FacialExpMgr& mgr);
int sendState(StateMgr& mgr);
int sendGoal(GoalMgr& mgr);
int sendPeople(PeopleMgr& mgr);
int sendWord(WordMgr& mgr);
int sendDetect(Detect& mgr);
int sendLocState(LocState& mgr);
int sendSpeak(SpeakMgr& mgr);
int sendNaviParMsg( NaviParMsg& msg );
int sendResultNavi(Result_Navi& msg);
int sendActionNavi(Action_Navi & msg);
int sendServerVel(ServerVelMgr & msg);
int sendPoseMode(PoseModeMgr & msg);
int sendAction_apState(Action_apStateMgr& mgr);
int sendResult_apState(Result_apStateMgr& mgr);

#endif
