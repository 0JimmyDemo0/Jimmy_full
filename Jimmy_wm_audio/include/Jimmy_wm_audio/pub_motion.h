#pragma once

#include <ros/ros.h>
#define cmd_len 3

namespace intel_jimmy {

class WM_motion {

public:

	WM_motion();
	virtual ~WM_motion() { }

	int UpdateHead(double& x, double& y, double& z);
	int PostHeadCMD(double& x, double& y, double& z);
	int UpdateHand(double tar);
	int UpdateTrunc(double tar);

	int CurHead();
	int CurHand();

private:

	double m_scale_pr, m_scale_ya;
	double m_rotate_x, m_rotate_y, m_rotate_z;
	double m_bnd_pr, m_bnd_ya;

	double cs_cmd[cmd_len];

	enum MT_DIM {
		MT_D_X = 0,
		MT_D_Y,
		MT_D_Z
	};
};

}

