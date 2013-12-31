#include <Jimmy_wm_audio/wim_control.h>
#include <Jimmy_wm_audio/loc_scripts.h>
#include <Jimmy_wm_audio/pub_motion.h>
#include <stdlib.h>

#define _WII_NUC 1

using namespace intel_jimmy;

WM_teleop::WM_teleop() :
		state_pic(0), state_twi(0),
		state_cmdl(0), state_cmdr(0), state_cmd0(0),
		state_id_p(0), state_id_n(0), state_id_0(0),
		state_a(0), state_b(0),
		m_trig(1), m_idx(1), m_cmd(0)
{
  joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("wiimotejoy", 3, &WM_teleop::joyCallback, this);

#ifdef _WII_NUC
  wnc_sub_ = nh_.subscribe<sensor_msgs::Joy>("wiimote/nunchuk", 3, &WM_teleop::wncCallback, this);
}

void WM_teleop::wncCallback(const sensor_msgs::Joy::ConstPtr& joy)
{

	int tmp_c = joy->buttons[WM_BTN_C];
	int tmp_z = joy->buttons[WM_BTN_Z];

	if(state_b && !state_a) {			// head move
		jsp_r = joy->axes[WM_AXES_ROLL];
		jsp_p = joy->axes[WM_AXES_PITCH];
		jsp_y = joy->axes[WM_AXES_YAW];

		m_trig = WM_STA_ACT;
	} else {
		jsp_y = 0.0;
		jsp_p = 0.0;
		jsp_r = 0.0;
	}

	if(state_twi != tmp_z) {	// twitter
		state_twi = tmp_z;
		m_trig = int(WM_STA_TWI * tmp_z);
	}

	if(state_pic != tmp_c) {	// picture
		state_pic = tmp_c;
		m_trig = int(WM_STA_PIC * tmp_c);
	}

}

#else
}
#endif

void WM_teleop::UpdateIndex() {
	if(m_idx >= DIM1)
		m_idx = 1;
	if(m_idx < 1)
		m_idx = DIM1 - 1;

	m_cmd = m_idx + 2;
}

void WM_teleop::AddIndex() {
	m_idx++;
	if(m_idx >= DIM1)
			m_idx = 1;

	m_cmd = m_idx + 2;
}

void WM_teleop::ResetState() {
	m_trig = WM_STA_NONE ;
}

void WM_teleop::DataHeadYPR(double &y, double &p, double &r) {
	r = jsp_r;
	p = jsp_p;
	y = jsp_y;
}

void WM_teleop::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
	int tmp_a = joy->buttons[WM_BTN_A];
	int tmp_b = joy->buttons[WM_BTN_B];
	int tmp_p = joy->buttons[WM_BTN_PP];
	int tmp_n = joy->buttons[WM_BTN_MM];
	int tmp_0 = joy->buttons[WM_BTN_HOME];
	int tmp_E = joy->buttons[WM_BTN_RK_U];
	int tmp_D = joy->buttons[WM_BTN_RK_D];
	int tmp_L = joy->buttons[WM_BTN_RK_L];
	int tmp_R = joy->buttons[WM_BTN_RK_R];

	// update idx
	if(tmp_p != state_id_p) {
		state_id_p = tmp_p;
		m_idx += state_id_p;
		m_trig = state_id_p*2 - 1;
	}

	if(tmp_n != state_id_n) {
		state_id_n = tmp_n;
		m_idx -= state_id_n;
		m_trig = state_id_n*2 - 1;
	}

	if(tmp_0 != state_id_0) {
		state_id_0 = tmp_0;
		m_idx = 1;
		m_trig = state_id_0*2 - 1;
	}

	UpdateIndex();

	// update cmd
	if(state_cmdr != tmp_R) {	// cmd++
		state_cmdr = tmp_R;
		m_cmd += tmp_R;
	}

	if(state_cmdl != tmp_L) {	// cmd--
		state_cmdl = tmp_L;
		m_cmd -= tmp_L;
	}

	if(state_cmd0 != tmp_D) {	// cmd--
		state_cmd0 = tmp_D;
		m_cmd = 0;
	}

	// update B
	if(1 != tmp_a) {
		state_b = tmp_b;
	}

	// update A
	if(1 == state_b) {
		if(state_a != tmp_a) {
			state_a = tmp_a;
			m_trig = int(WM_STA_AUD * tmp_a);
		}
	} else {
		if(tmp_a == 0) {
			state_a == 0;
		}
	}

#ifdef _WII_NOC
	// update pic
	if(state_pic != tmp_D) {
		state_pic = tmp_D;
		m_trig = int(WM_STA_PIC * tmp_D);
	}
#endif

	if(tmp_E == 1) {
		m_trig = WM_STA_EXIT;
	}

}

/*
int WM_teleop::PlayIndex() {

	UpdateIndex();
	int idx = m_idx;
	if(state_a == 1) {
		++m_idx;
		UpdateIndex();
	}
	return idx;
}*/
