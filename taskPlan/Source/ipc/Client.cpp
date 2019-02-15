/******************************************************
NTU EECS Advanced Control Lab, Intelligent Robot Lab

2010 Kuo-Chen Huang

******************************************************/

#include "TaskIpc.h"
#include "Client.h"
#include <cstdarg>
#include <map>
#include <sstream>
#include <string>

#ifdef WIN32
#include "process.h"
#else
#include <pthread.h>
#include "msleep.h"
#endif

using namespace std;
using namespace ROBOT;

//--------------------------------------------------//
// message container ( names, formats and handlers )
//--------------------------------------------------//
MsgInfo msg_info[TOTAL_MSG_NUM];

//--------------------------------------------------//
// message handlers
//--------------------------------------------------//
void laserpose_message_handler(MSG_INSTANCE msgRef, BYTE_ARRAY callData, void *clientData)
{
	LaserPoseMgr data;
	IPC_unmarshallData(IPC_msgInstanceFormatter(msgRef), callData, &data, sizeof(LaserPoseMgr));
	setLaserPose( data );
	IPC_freeByteArray(callData);
}

void slaser_message_handler(MSG_INSTANCE msgRef, BYTE_ARRAY callData, void *clientData)
{
	SLaserMgr data;
	IPC_unmarshallData(IPC_msgInstanceFormatter(msgRef), callData, &data, sizeof(SLaserMgr));
	setSLaser( data );
	IPC_freeByteArray(callData);
}

void urglaser_message_handler(MSG_INSTANCE msgRef, BYTE_ARRAY callData, void *clientData)
{
	URGLaser data;
	IPC_unmarshallData(IPC_msgInstanceFormatter(msgRef), callData, &data, sizeof(URGLaser));
	setURGLaser( data );
	IPC_freeByteArray(callData);
}

void vslaser_message_handler(MSG_INSTANCE msgRef, BYTE_ARRAY callData, void *clientData)
{
	VSLaserMgr data;
	IPC_unmarshallData(IPC_msgInstanceFormatter(msgRef), callData, &data, sizeof(VSLaserMgr));
	setVSLaser( data );
	IPC_freeByteArray(callData);
}

void subgoal_message_handler(MSG_INSTANCE msgRef, BYTE_ARRAY callData, void *clientData)
{
	SubgoalMgr data;
	IPC_unmarshallData(IPC_msgInstanceFormatter(msgRef), callData, &data, sizeof(SubgoalMgr));
	setSubgoal( data );
	IPC_freeByteArray(callData);
}

void odometry_message_handler(MSG_INSTANCE msgRef, BYTE_ARRAY callData, void *clientData)
{
	OdometryMgr data;
	IPC_unmarshallData(IPC_msgInstanceFormatter(msgRef), callData, &data, sizeof(OdometryMgr));
	setOdometry( data );
	IPC_freeByteArray(callData);
}

void motor_message_handler(MSG_INSTANCE msgRef, BYTE_ARRAY callData, void *clientData)
{
	MotorMgr data;
	IPC_unmarshallData(IPC_msgInstanceFormatter(msgRef), callData, &data, sizeof(MotorMgr));
	setMotor( data );
	IPC_freeByteArray(callData);
}

void SpeedMode_message_handler(MSG_INSTANCE msgRef, BYTE_ARRAY callData, void *clientData)
{
	SpeedModeMgr data;
	IPC_unmarshallData(IPC_msgInstanceFormatter(msgRef), callData, &data, sizeof(SpeedModeMgr));
	setSpeedMode( data );
	IPC_freeByteArray(callData);
}

void HeadMotor_message_handler(MSG_INSTANCE msgRef, BYTE_ARRAY callData, void *clientData)
{
	HeadMotorMgr data;
	IPC_unmarshallData(IPC_msgInstanceFormatter(msgRef), callData, &data, sizeof(HeadMotorMgr));
	setHeadMotor( data );
	IPC_freeByteArray(callData);
}

void handpos_message_handler(MSG_INSTANCE msgRef, BYTE_ARRAY callData, void *clientData)
{
	HandPoseMgr data;
	IPC_unmarshallData(IPC_msgInstanceFormatter(msgRef), callData, &data, sizeof(HandPoseMgr));
	setHandPose( data );
	IPC_freeByteArray(callData);
}

void facialexp_message_handler(MSG_INSTANCE msgRef, BYTE_ARRAY callData, void *clientData)
{
	FacialExpMgr data;
	IPC_unmarshallData(IPC_msgInstanceFormatter(msgRef), callData, &data, sizeof(FacialExpMgr));
	setFacialExp( data );
	IPC_freeByteArray(callData);
}

void state_message_handler(MSG_INSTANCE msgRef, BYTE_ARRAY callData, void *clientData)
{
	StateMgr data;
	IPC_unmarshallData(IPC_msgInstanceFormatter(msgRef), callData, &data, sizeof(StateMgr));
	setState( data );
	IPC_freeByteArray(callData);
}

void goal_message_handler(MSG_INSTANCE msgRef, BYTE_ARRAY callData, void *clientData)
{
	GoalMgr data;
	IPC_unmarshallData(IPC_msgInstanceFormatter(msgRef), callData, &data, sizeof(GoalMgr));
	setGoal( data );
	IPC_freeByteArray(callData);
}

void people_message_handler(MSG_INSTANCE msgRef, BYTE_ARRAY callData, void *clientData)
{
	PeopleMgr data;
	IPC_unmarshallData(IPC_msgInstanceFormatter(msgRef), callData, &data, sizeof(PeopleMgr));
	setPeople( data );
	IPC_freeByteArray(callData);
}

void word_message_handler(MSG_INSTANCE msgRef, BYTE_ARRAY callData, void *clientData)
{
	WordMgr data;
	IPC_unmarshallData(IPC_msgInstanceFormatter(msgRef), callData, &data, sizeof(WordMgr));
	setWord( data );
	IPC_freeByteArray(callData);
}

void detect_message_handler(MSG_INSTANCE msgRef, BYTE_ARRAY callData, void *clientData)
{
	Detect data;
	IPC_unmarshallData(IPC_msgInstanceFormatter(msgRef), callData, &data, sizeof(Detect));
	setDetect( data );
	IPC_freeByteArray(callData);
}

void locstate_message_handler(MSG_INSTANCE msgRef, BYTE_ARRAY callData, void *clientData)
{
	LocState data;
	IPC_unmarshallData(IPC_msgInstanceFormatter(msgRef), callData, &data, sizeof(LocState));
	setLocState( data );
	IPC_freeByteArray(callData);
}

void speak_message_handler(MSG_INSTANCE msgRef, BYTE_ARRAY callData, void *clientData)
{
	SpeakMgr data;
	IPC_unmarshallData(IPC_msgInstanceFormatter(msgRef), callData, &data, sizeof(SpeakMgr));
	setSpeak( data );
	IPC_freeByteArray(callData);
}

void resultnavi_message_handler(MSG_INSTANCE msgRef, BYTE_ARRAY callData, void *clientData)
{
	Result_Navi data;
	IPC_unmarshallData(IPC_msgInstanceFormatter(msgRef), callData, &data, sizeof(Result_Navi));
	setResultNavi( data );
	IPC_freeByteArray(callData);
}
void actionnavi_message_handler(MSG_INSTANCE msgRef, BYTE_ARRAY callData, void *clientData)
{
	Action_Navi data;
	IPC_unmarshallData(IPC_msgInstanceFormatter(msgRef), callData, &data, sizeof(Action_Navi));
	setActionNavi( data );
	IPC_freeByteArray(callData);
}

void servervel_message_handler(MSG_INSTANCE msgRef, BYTE_ARRAY callData, void *clientData)
{
	ServerVelMgr data;
	IPC_unmarshallData(IPC_msgInstanceFormatter(msgRef), callData, &data, sizeof(ServerVelMgr));
	setServerVel( data );
	IPC_freeByteArray(callData);
}

void posemode_message_handler(MSG_INSTANCE msgRef, BYTE_ARRAY callData, void *clientData)
{
	PoseModeMgr data;
	IPC_unmarshallData(IPC_msgInstanceFormatter(msgRef), callData, &data, sizeof(PoseModeMgr));
	setPoseMode( data );
	IPC_freeByteArray(callData);
}

void action_apState_message_handler(MSG_INSTANCE msgRef, BYTE_ARRAY callData, void *clientData)
{
	Action_apStateMgr data;
	IPC_unmarshallData(IPC_msgInstanceFormatter(msgRef), callData, &data, sizeof(Action_apStateMgr));
	setAction_apState(data);
	IPC_freeByteArray(callData);
	/**/
	taskPlanerNamespace::TaskIpc::setReceiveFlag(); 
}

void result_apState_message_handler(MSG_INSTANCE msgRef, BYTE_ARRAY callData, void *clientData)
{
	Result_apStateMgr data;
	IPC_unmarshallData(IPC_msgInstanceFormatter(msgRef), callData, &data, sizeof(Result_apStateMgr));
	setResult_apState(data);
	IPC_freeByteArray(callData);
	/**/
	taskPlanerNamespace::TaskIpc::setReceiveFlag(); 
}

//--------------------------------------------------//
// IPC client
//--------------------------------------------------//
static ClientThread listenThread;

void register_messages();
void define_message(const char *msgName, const char *formatString);

void connect_to_server(const char* server_name)
{
	ostringstream ipc_name;
	#ifdef WIN32
	ipc_name << "taskPlane" << _getpid();
	#else
	ipc_name << "Client" << getpid();
	#endif

	IPC_connectModule(ipc_name.str().c_str(), server_name);
	IPC_setVerbosity(IPC_Print_Errors);
	IPC_setVerbosity(IPC_Print_Warnings);

	register_messages();
}

void disconnect_to_server()
{
	listenThread.stop();
	listenThread.join();
	
	IPC_disconnect();
}

void subscribe(MessageType first, ...)
{
	MessageType msg_type = first;
	va_list arg_list;
	va_start( arg_list, first );

	while( msg_type < TOTAL_MSG_NUM ){
		const char* name = msg_info[msg_type].msg_name.c_str();
		const char* format = msg_info[msg_type].msg_format.c_str();
		HANDLER_TYPE handler = msg_info[msg_type].msg_handler;
		printf( "subscribe %s\n", name );
		define_message( name, format );
		IPC_subscribe( name, handler, NULL);
		msg_type = (MessageType)va_arg( arg_list, int );
	}

	va_end( arg_list );
}

void publish(MessageType first, ...)
{
	MessageType msg_type = first;
	va_list arg_list;
	va_start( arg_list, first );

	while( msg_type < TOTAL_MSG_NUM ){
		const char* name = msg_info[msg_type].msg_name.c_str();
		const char* format = msg_info[msg_type].msg_format.c_str();
		printf( "publish %s\n", name );
		define_message( name, format );
		msg_type = (MessageType)va_arg( arg_list, int );
	}

	va_end( arg_list );
}


void listen()
{
	if( !listenThread.isRunning() )
		listenThread.start();
}

// register messages
void register_messages()
{
	msg_info[LASERPOSE]  = MsgInfo( LASERPOSE_NAME, LASERPOSE_FORMAT, laserpose_message_handler );
	msg_info[SLASER]     = MsgInfo( SLASER_NAME, SLASER_FORMAT, slaser_message_handler );
	msg_info[URG]        = MsgInfo( URGLASER_NAME, URGLASER_FORMAT, urglaser_message_handler );
	msg_info[VSLASER]    = MsgInfo( VSLASER_NAME, VSLASER_FORMAT, vslaser_message_handler );
	msg_info[SUBGOAL]    = MsgInfo( SUBGOAL_NAME, SUBGOAL_FORMAT, subgoal_message_handler );
	msg_info[ODOMETRY]   = MsgInfo( ODOMETRY_NAME, ODOMETRY_FORMAT, odometry_message_handler );
	msg_info[MOTOR]      = MsgInfo( MOTOR_NAME, MOTOR_FORMAT, motor_message_handler );
	msg_info[SPEED_MODE] = MsgInfo( SPEEDMODE_NAME, SPEEDMODE_FORMAT, SpeedMode_message_handler );
	msg_info[HEAD_MOTOR] = MsgInfo( HEADMOTOR_NAME, HEADMOTOR_FORMAT, HeadMotor_message_handler );
	msg_info[HAND_POSE]  = MsgInfo( HANDPOS_NAME, HANDPOS_FORMAT, handpos_message_handler );
	msg_info[FACIAL_EXP] = MsgInfo( FACIAlEXP_NAME, FACIAlEXP_FORMAT, facialexp_message_handler );
	msg_info[STATE]      = MsgInfo( STATE_NAME, STATE_FORMAT, state_message_handler );
	msg_info[GOAL]       = MsgInfo( GOAL_NAME, GOAL_FORMAT, goal_message_handler );
	msg_info[PEOPLE]     = MsgInfo( PEOPLE_NAME, PEOPLE_FORMAT, people_message_handler );
	msg_info[KEYWORD]       = MsgInfo( WORD_NAME, WORD_FORMAT, word_message_handler );
	msg_info[DETECT]     = MsgInfo( DETECT_NAME, DETECT_FORMAT, detect_message_handler );
	msg_info[LOC_STATE]  = MsgInfo( LOCSTATE_NAME, LOCSTATE_FORMAT, locstate_message_handler );
	msg_info[SPEAK]      = MsgInfo( SPEAK_NAME, SPEAK_FORMAT, speak_message_handler );
	msg_info[RESULT_NAVI]   = MsgInfo( RESULT_NAVI_NAME, RESULT_NAVI_FORMAT, resultnavi_message_handler );
	msg_info[ACTION_NAVI]   = MsgInfo( ACTION_NAVI_NAME, ACTION_NAVI_FORMAT, actionnavi_message_handler );
	msg_info[SERVER_VEL]    = MsgInfo( SERVER_VEL_NAME, SERVER_VEL_FORMAT, servervel_message_handler );
	msg_info[POSE_MODE]     = MsgInfo( POSE_MODE_NAME, POSE_MODE_FORMAT, posemode_message_handler );
	msg_info[ACTION_APSTATE]       = MsgInfo(ACTION_APSTATE_NAME,ACTION_APSTATE_FORMAT,action_apState_message_handler);
	msg_info[RESULT_APSTATE]       = MsgInfo(RESULT_APSTATE_NAME,RESULT_APSTATE_FORMAT,result_apState_message_handler);
}

void define_message(const char *msgName, const char *formatString)
{
	if(!IPC_isMsgDefined(msgName)){
		printf("defining message(%s)!\n", msgName);
		IPC_defineMsg(msgName, IPC_VARIABLE_LENGTH, formatString);
	}
}

//--------------------------------------------------//
// send messages
//--------------------------------------------------//
int sendLaserPose(LaserPoseMgr& mgr){
	return (int)IPC_publishData(LASERPOSE_NAME, &mgr);
}

int sendSLaser(SLaserMgr& mgr){
	return (int)IPC_publishData(SLASER_NAME, &mgr);
}

int sendURGLaser(URGLaser& mgr){
	return (int)IPC_publishData(URGLASER_NAME, &mgr);
}


int sendVSLaser(VSLaserMgr& mgr){
	return (int)IPC_publishData(VSLASER_NAME, &mgr);
}

int sendSubgoal(SubgoalMgr& mgr){
	return (int)IPC_publishData(SUBGOAL_NAME, &mgr);
}

int sendOdometry(OdometryMgr& mgr){
	return (int)IPC_publishData(ODOMETRY_NAME, &mgr);
}

int sendMotor(MotorMgr& mgr){
	return (int)IPC_publishData(MOTOR_NAME, &mgr);
}

int sendSpeedMode(SpeedModeMgr& mgr){
	return (int)IPC_publishData(SPEEDMODE_NAME, &mgr);
}

int sendHeadMotor(HeadMotorMgr& mgr){;
	return (int)IPC_publishData(HEADMOTOR_NAME, &mgr);
}

int sendHandPose(HandPoseMgr& mgr){
	return (int)IPC_publishData(HANDPOS_NAME, &mgr);
}

int sendFacialExp(FacialExpMgr& mgr){
	return (int)IPC_publishData(FACIAlEXP_NAME, &mgr);
}

int sendState(StateMgr& mgr){
	return (int)IPC_publishData(STATE_NAME, &mgr);
}

int sendGoal(GoalMgr& mgr){
	return (int)IPC_publishData(GOAL_NAME, &mgr);
}

int sendPeople(PeopleMgr& mgr){
	return (int)IPC_publishData(PEOPLE_NAME, &mgr);
}

int sendWord(WordMgr& mgr){
	return (int)IPC_publishData(WORD_NAME, &mgr);
}

int sendDetect(Detect& mgr){
	return (int)IPC_publishData(DETECT_NAME, &mgr);
}

int sendLocState(LocState& mgr){
	return (int)IPC_publishData(LOCSTATE_NAME, &mgr);
}

int sendSpeak(SpeakMgr& mgr){
	return (int)IPC_publishData(SPEAK_NAME, &mgr);
}

int sendResultNavi(Result_Navi&msg){
	return (int)IPC_publishData(RESULT_NAVI_NAME, &msg);
}

int sendActionNavi(Action_Navi& msg){
	return (int)IPC_publishData(ACTION_NAVI_NAME, &msg);
}

int sendServerVel(ServerVelMgr & msg){
	return (int)IPC_publishData(SERVER_VEL_NAME, &msg);
}

int sendPoseMode(PoseModeMgr & msg){
	return (int)IPC_publishData(POSE_MODE_NAME, &msg);
}

int sendAction_apState(Action_apStateMgr & mgr){
	return (int)IPC_publishData(ACTION_APSTATE_NAME, &mgr);
}
int sendResult_apState(Result_apStateMgr & mgr){
	return (int)IPC_publishData(RESULT_APSTATE_NAME, &mgr);
}
