#include <Jimmy_wm_audio/pub_motion.h>
#include <stdio.h>
#include <stdlib.h>

using namespace intel_jimmy;

WM_motion::WM_motion() :
		m_rotate_x(0),
		m_rotate_y(0),
		m_rotate_z(0),
		m_scale_pr(0.1),
		m_scale_ya(0.1),
		m_bnd_pr(1),
		m_bnd_ya(1)
{

}

int WM_motion::UpdateHead(double &x, double &y, double &z) {

	m_rotate_x = x*m_scale_pr;
	m_rotate_y = y*m_scale_pr;
	m_rotate_z = z*m_scale_ya;

	cs_cmd[MT_D_X] = m_rotate_x > m_bnd_pr ? m_bnd_pr : (m_rotate_x < -m_bnd_pr ? -m_bnd_pr : m_rotate_x);
	cs_cmd[MT_D_Y] = m_rotate_y > m_bnd_pr ? m_bnd_pr : (m_rotate_y < -m_bnd_pr ? -m_bnd_pr : m_rotate_y);
	cs_cmd[MT_D_Z] = m_rotate_z > m_bnd_ya ? m_bnd_ya : (m_rotate_z < -m_bnd_pr ? -m_bnd_pr : m_rotate_z);

	return 0;
}

int WM_motion::UpdateHand(double tar) {
	return 0;
}

int WM_motion::UpdateTrunc(double tar) {
	return 0;
}

int WM_motion::PostHeadCMD(double& x, double& y, double& z) {
	x = cs_cmd[MT_D_X];
	y = cs_cmd[MT_D_Y];
	z = cs_cmd[MT_D_Z];
}

int WM_motion::CurHead() {
	return 0;
}

int WM_motion::CurHand() {
	return 0;
}
