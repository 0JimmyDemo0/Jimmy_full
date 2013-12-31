#pragma once

#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
//#include <sensor_msgs/Imu.h>

namespace intel_jimmy {

class WM_teleop {

public:

	WM_teleop();

	inline int IsReady() { return state_a; }
	inline int CurState() { return m_trig; }
	inline int PlayIndex() { return m_idx; }
	inline int ReportCMD() { return m_cmd; }

	void AddIndex();
	void ResetState();
	void DataHeadYPR(double&, double&, double&);

private:

	void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);
	void wncCallback(const sensor_msgs::Joy::ConstPtr& joy);
	void UpdateIndex();
	void UpdateCMD();

	ros::NodeHandle nh_;
	ros::Subscriber joy_sub_;
	ros::Subscriber wnc_sub_;

	int state_cmdl, state_cmdr, state_cmd0;
	int state_id_p, state_id_n, state_id_0;
	int state_pic, state_twi;
	int m_idx, m_cmd, m_trig;
	int state_a, state_b;

	double jsp_y, jsp_p, jsp_r;

	enum m_WM_BTN {
		WM_BTN_1 = 0,
		WM_BTn_2,
		WM_BTN_A,
		WM_BTN_B,
		WM_BTN_PP,
		WM_BTN_MM,

		WM_BTN_RK_L,
		WM_BTN_RK_R,
		WM_BTN_RK_U,
		WM_BTN_RK_D,

		WM_BTN_HOME,

		WM_BTN_Z = 0,
		WM_BTN_C,
	};

	enum m_WM_AXES {
		WM_AXES_PITCH = 0,	//	y updown
		WM_AXES_YAW,		//	z turn
		WM_AXES_ROLL		//	x rotate
	};

};

}
