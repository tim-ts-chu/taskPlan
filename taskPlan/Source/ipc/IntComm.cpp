/******************************************************
NTU EECS Advanced Control Lab, Intelligent Robot Lab

2010 Kuo-Chen Huang

******************************************************/
#include "Comm.h"

//--------------------------------------------------//
// messages
//--------------------------------------------------//

// laser_pose 
static LaserPoseMgr laserpose_mgr;
static OdometryMgr corr_odometry;
//
static SLaserMgr slaser_mgr;
static URGLaser urglaser_mgr;
static VSLaserMgr vslaser_mgr;
static SubgoalMgr subgoal_mgr;
static OdometryMgr odometry_mgr;
static MotorMgr motor_mgr;
static SpeedModeMgr speed_mode_mgr;
static HeadMotorMgr head_motor_mgr;
static HandPoseMgr handpose_mgr;
static FacialExpMgr facial_exp_mgr;
static StateMgr state_mgr;
static GoalMgr goal_mgr;
static PeopleMgr people_mgr;
static WordMgr word_mgr;
static Detect detect_mgr;
static LocState loc_state_mgr;
static SpeakMgr speak_mgr;
static NaviParMsg navi_par_msg;
static Result_Navi resultnavi_msg;
static Action_Navi actionnavi_msg;
static ServerVelMgr servervel_msg;
static PoseModeMgr posemode_msg;
static Action_apStateMgr action_apStateMgr;
static Result_apStateMgr result_apStateMgr;

#ifdef WIN32

#include "locks.h"

static win32CriticalSection msg_lock[TOTAL_MSG_NUM];
#define RD_LOCK( A ) msg_lock[A].lock()
#define WR_LOCK( A ) msg_lock[A].lock()
#define RD_UNLOCK( A )  msg_lock[A].unlock()
#define WR_UNLOCK( A )  msg_lock[A].unlock()
/*
static RW_LOCK msg_lock[TOTAL_MSG_NUM];
#define RD_LOCK( A ) rwlock_rdlock( &msg_lock[A] )
#define WR_LOCK( A ) rwlock_wrlock( &msg_lock[A] )
#define RD_UNLOCK( A )  rwlock_rdunlock( &msg_lock[A] )
#define WR_UNLOCK( A )  rwlock_wrunlock( &msg_lock[A] )
*/
#else

static pthread_rwlock_t msg_lock[TOTAL_MSG_NUM];
#define RD_LOCK( A ) pthread_rwlock_rdlock( &msg_lock[A] )
#define WR_LOCK( A ) pthread_rwlock_wrlock( &msg_lock[A] )
#define RD_UNLOCK( A )  pthread_rwlock_unlock( &msg_lock[A] )
#define WR_UNLOCK( A )  pthread_rwlock_unlock( &msg_lock[A] )

#endif

#include <cmath>
#define M_PI 3.14159265

void init_comm()
{
#ifdef WIN32
	//for(int i = 0 ; i < TOTAL_MSG_NUM ; ++i){
	//	rwlock_init(&msg_lock[i]);
	//}
#else
	for(int i = 0 ; i < TOTAL_MSG_NUM ; ++i){
		pthread_rwlock_init(&msg_lock[i], NULL);
	}
#endif
}

//--------------------------------------------------//
// get messages
//--------------------------------------------------//

#define Rad2Deg 57.295779513
#define Deg2Rad 0.01745329252

void getLaserPose(LaserPoseMgr& mgr)
{
	//m/m/deg, m/m/rad
	OdometryMgr prev_odo, current_odo;

	RD_LOCK( LASERPOSE );
	mgr = laserpose_mgr;
	mgr.theta *= Deg2Rad;
	prev_odo = corr_odometry;
	prev_odo.theta *= Deg2Rad;
	RD_UNLOCK( LASERPOSE );

	RD_LOCK( ODOMETRY );
	current_odo = odometry_mgr;
	current_odo.theta *= Deg2Rad;
	RD_UNLOCK( ODOMETRY );

	double dx = current_odo.x - prev_odo.x;
	double dy = current_odo.y - prev_odo.y;
	
	if( dx != 0 || dy != 0){
		double dist = sqrt( dx * dx + dy *dy );
		double moving_direction = atan2( dy, dx ) - prev_odo.theta + mgr.theta;
		
		mgr.x += dist * cos( moving_direction );
		mgr.y += dist * sin( moving_direction );
		double theta = current_odo.theta - prev_odo.theta + mgr.theta;

		if (theta < -M_PI || theta > M_PI){
			double multiplier = floor(theta / (2*M_PI));
			theta = theta - multiplier*2*M_PI;
			if (theta > M_PI)
				theta -= 2*M_PI;
			if (theta < -M_PI)
				theta += 2*M_PI;
		}
		mgr.theta = theta;
	}
	mgr.theta *= Rad2Deg;
}

void getSLaser(SLaserMgr& mgr)
{
	RD_LOCK( SLASER );
	mgr = slaser_mgr;
	RD_UNLOCK( SLASER );
}

void getURGLaser(URGLaser& mgr)
{
	RD_LOCK( URG );
	mgr = urglaser_mgr;
	RD_UNLOCK( URG );
}

void getVSLaser(VSLaserMgr& mgr)
{
	RD_LOCK( VSLASER );
	mgr = vslaser_mgr;
	RD_UNLOCK( VSLASER );
}

void getSubgoal(SubgoalMgr& mgr)
{
	RD_LOCK( SUBGOAL );
	mgr = subgoal_mgr;
	RD_UNLOCK( SUBGOAL );
}

void getOdometry(OdometryMgr& mgr)
{
	RD_LOCK( ODOMETRY );
	mgr = odometry_mgr;
	RD_UNLOCK( ODOMETRY );
}

void getMotor(MotorMgr& mgr)
{
	RD_LOCK( MOTOR );
	mgr = motor_mgr;
	RD_UNLOCK( MOTOR );
}

void getSpeedMode(SpeedModeMgr& mgr)
{
	RD_LOCK( SPEED_MODE );
	mgr = speed_mode_mgr;
	RD_UNLOCK( SPEED_MODE );
}

void getHeadMotor(HeadMotorMgr& mgr){
	RD_LOCK( HEAD_MOTOR );
	mgr = head_motor_mgr;
	RD_UNLOCK( HEAD_MOTOR );
}

void getHandPose(HandPoseMgr& mgr){
	RD_LOCK( HAND_POSE );
	mgr = handpose_mgr;
	RD_UNLOCK( HAND_POSE );
}

void getFacialExp(FacialExpMgr& mgr)
{
	RD_LOCK( FACIAL_EXP );
	mgr = facial_exp_mgr;
	RD_UNLOCK( FACIAL_EXP );
}

void getState(StateMgr& mgr)
{
	RD_LOCK( STATE );
	mgr = state_mgr;
	RD_UNLOCK( STATE );
}

void getGoal(GoalMgr& mgr)
{
	RD_LOCK( GOAL );
	mgr = goal_mgr;
	RD_UNLOCK( GOAL );
}

void getPeople(PeopleMgr& mgr)
{
	RD_LOCK( PEOPLE );
	mgr = people_mgr;
	RD_UNLOCK( PEOPLE );
}

void getWord(WordMgr& mgr)
{
	// writer lock !!
	WR_LOCK( KEYWORD );	
	mgr = word_mgr;
	//sprintf( word_mgr.keyword, "\0");
	WR_UNLOCK( KEYWORD );
}

void getDetect(Detect& mgr)
{
	RD_LOCK( DETECT );
	mgr = detect_mgr;
	RD_UNLOCK( DETECT );
}

void getLocState(LocState& mgr){
	RD_LOCK( LOC_STATE );
	mgr = loc_state_mgr;
	RD_UNLOCK( LOC_STATE );
}

void getSpeak(SpeakMgr& mgr)
{
	RD_LOCK( SPEAK );
	mgr = speak_mgr;
	RD_UNLOCK( SPEAK );
}

void getNaviParMsg( NaviParMsg& msg )
{
	RD_LOCK( NAVI_PAR );
	msg = navi_par_msg;
	RD_UNLOCK( NAVI_PAR );
}


void getResultNavi( Result_Navi& msg )
{
	RD_LOCK( RESULT_NAVI );
	msg = resultnavi_msg;
	RD_UNLOCK( RESULT_NAVI );
}

void getActionNavi( Action_Navi& msg )
{
	RD_LOCK( ACTION_NAVI );
	msg = actionnavi_msg;
	RD_UNLOCK( ACTION_NAVI );
}

void getServerVel( ServerVelMgr& msg )
{
	RD_LOCK( SERVER_VEL);
	msg = servervel_msg;
	RD_UNLOCK( SERVER_VEL);
}

void getPoseMode( PoseModeMgr& msg )
{
	RD_LOCK( POSE_MODE);
	msg = posemode_msg;
	RD_UNLOCK( POSE_MODE);
}

void getAction_apState(Action_apStateMgr& mgr)
{
	RD_LOCK( ACTION_APSTATE );
	mgr = action_apStateMgr ;
	RD_UNLOCK( ACTION_APSTATE );
}

void getResult_apState(Result_apStateMgr& mgr)
{
	RD_LOCK( RESULT_APSTATE );
	mgr = result_apStateMgr ;
	RD_UNLOCK( RESULT_APSTATE );
}

//--------------------------------------------------//
// set messages
//--------------------------------------------------//
void setLaserPose(LaserPoseMgr& mgr)
{
	WR_LOCK( LASERPOSE );
	laserpose_mgr = mgr;
	WR_UNLOCK( LASERPOSE );
}

void setLaserPose(LaserPoseMgr& lmgr, OdometryMgr& omgr)
{
	WR_LOCK( LASERPOSE );
	laserpose_mgr = lmgr;
	corr_odometry = omgr;
	WR_UNLOCK( LASERPOSE );
}

void setSLaser(SLaserMgr& mgr)
{
	WR_LOCK( SLASER );
	slaser_mgr = mgr;
	WR_UNLOCK( SLASER );
}

void setURGLaser(URGLaser& mgr)
{
	WR_LOCK( URG );
	urglaser_mgr = mgr;
	WR_UNLOCK( URG );
}

void setVSLaser(VSLaserMgr& mgr)
{
	WR_LOCK( VSLASER );
	vslaser_mgr = mgr;
	WR_UNLOCK( VSLASER );
}

void setSubgoal(SubgoalMgr& mgr)
{
	WR_LOCK( SUBGOAL );
	subgoal_mgr = mgr;
	WR_UNLOCK( SUBGOAL );
}

void setOdometry(OdometryMgr& mgr)
{
	WR_LOCK( ODOMETRY );
	odometry_mgr = mgr;
	WR_UNLOCK( ODOMETRY );
}

void setMotor(MotorMgr& mgr)
{
	WR_LOCK( MOTOR );
	motor_mgr = mgr;
	WR_UNLOCK( MOTOR );
}

void setSpeedMode(SpeedModeMgr& mgr)
{
	WR_LOCK( SPEED_MODE );
	speed_mode_mgr = mgr;
	WR_UNLOCK( SPEED_MODE );
}

void setHeadMotor(HeadMotorMgr& mgr)
{
	WR_LOCK( HEAD_MOTOR );
	head_motor_mgr = mgr;
	WR_UNLOCK( HEAD_MOTOR );
}

void setHandPose(HandPoseMgr& mgr)
{
	WR_LOCK( HAND_POSE );
	handpose_mgr = mgr;
	WR_UNLOCK( HAND_POSE );
}

void setFacialExp(FacialExpMgr& mgr)
{
	WR_LOCK( FACIAL_EXP );
	facial_exp_mgr = mgr;
	WR_UNLOCK( FACIAL_EXP );
}

void setState(StateMgr& mgr)
{
	WR_LOCK( STATE );
	state_mgr = mgr;
	WR_UNLOCK( STATE );
}

void setGoal(GoalMgr& mgr)
{
	WR_LOCK( GOAL );
	goal_mgr = mgr;
	WR_UNLOCK( GOAL );
}

void setPeople(PeopleMgr& mgr)
{
	WR_LOCK( PEOPLE );
	people_mgr = mgr;
	WR_UNLOCK( PEOPLE );
}

void setWord(WordMgr& mgr)
{
	WR_LOCK( KEYWORD );
	word_mgr = mgr;
	WR_UNLOCK( KEYWORD );
}

void setDetect(Detect& mgr)
{
	WR_LOCK( DETECT );
	detect_mgr = mgr;
	WR_UNLOCK( DETECT );
}

void setLocState(LocState& mgr)
{
	WR_LOCK( LOC_STATE );
	loc_state_mgr = mgr;
	WR_UNLOCK( LOC_STATE );
}

void setSpeak(SpeakMgr& mgr)
{
	WR_LOCK( SPEAK );
	speak_mgr = mgr;
	WR_UNLOCK( SPEAK );
}

void setNaviParMsg( NaviParMsg& mgr )
{
	WR_LOCK( NAVI_PAR );
	navi_par_msg = mgr;
	WR_UNLOCK( NAVI_PAR );
}

void setResultNavi( Result_Navi& msg )
{
	WR_LOCK( RESULT_NAVI );
	resultnavi_msg = msg;
	WR_UNLOCK( RESULT_NAVI );
}

void setActionNavi( Action_Navi& msg )
{
	WR_LOCK( ACTION_NAVI );
	actionnavi_msg = msg;
	WR_UNLOCK( ACTION_NAVI );
}

void setServerVel( ServerVelMgr& msg )
{
	WR_LOCK( SERVER_VEL);
	servervel_msg = msg;
	WR_UNLOCK( SERVER_VEL);
}

void setPoseMode( PoseModeMgr& msg )
{
	WR_LOCK( POSE_MODE);
	posemode_msg = msg;
	WR_UNLOCK( POSE_MODE);
}

void setAction_apState(Action_apStateMgr& mgr)
{
	WR_LOCK( ACTION_APSTATE );
	action_apStateMgr = mgr;
	WR_UNLOCK( ACTION_APSTATE );
}

void setResult_apState(Result_apStateMgr& mgr)
{
	WR_LOCK( RESULT_APSTATE );
	result_apStateMgr = mgr;
	WR_UNLOCK( RESULT_APSTATE );
}
