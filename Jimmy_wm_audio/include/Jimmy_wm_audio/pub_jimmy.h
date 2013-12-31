#pragma once

#define UPBND 73
#define SPDIM 173

namespace intel_jimmy {

class WM_script {

private:

	int capac;
	int count;
	int wm_vail[];

	static const char* cur_user;

	static const char* video_full_path;
	static const char* video_full_sufx;
	static const char* video_stop_cmmd;

	int cnt_p;

	static const char* pic_full_path;
	static const char* pic_full_sufx;

	static const char* twi_batch_cmd;
	static const char* twi_tran_path;

	static const char* exit_clc;

	char contect[UPBND][SPDIM];

public:

	WM_script();
	virtual ~WM_script() {}

	inline int WM_report() { return count; }
	int WM_init();

	void WM_update(int idx);
	int WM_add(int idx);
	int WM_del(int idx);
	const char* WM_clc();
	const char* WM_end_audnm(char* target);
	const char* WM_get_audnm(char* target, int idx);
	const char* WM_get_txtnm(char* target, int idx);
	const char* WM_post_twip(char* target);
	const char* WM_get_vidnm(char* target);

};

}

