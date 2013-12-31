#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Jimmy_wm_audio/pub_jimmy.h>
#include <Jimmy_wm_audio/loc_scripts.h>

using namespace intel_jimmy;

WM_script::WM_script() : capac(UPBND), count(0), cnt_p(0)
{

	wm_vail[UPBND] = {0};

	contect[UPBND][SPDIM] = {};
//	WM_init();

}

const char* WM_script::cur_user = "";

const char* WM_script::video_full_path = "/home/irob/Desktop/Jimmy_";
const char* WM_script::video_full_sufx = ".mp3";
const char* WM_script::video_stop_cmmd = "killall mpg123";

const char* WM_script::pic_full_path = "./Jmdata/pics/";
const char* WM_script::pic_full_sufx = ".jpg";
const char* WM_script::twi_tran_path = "/var/www/jimmytwitter/uploads/photo_trans.jpg";
const char* WM_script::twi_batch_cmd = "./script/ftp.sh";

const char* WM_script::exit_clc = "killall Jimmy_wm_audio wiimote_node.py mpg123 fswebcam";

int WM_script::WM_init() {
	for(int cur = 0; cur < DIM1; ++cur) {
		strncpy(contect[cur], local_script[cur], DIM2);
	}
	count = DIM1;

	//printf("core: %d\n", system("roscore 1> /dev/null 2>&1 &"));
	printf("[Jimmy::Info] Connecting to roscore...\n");
	system("roscore 1> /dev/null 2>&1 &");
	sleep(1);

	//printf("run: %d\n", system("rosrun wiimote wiimote_node.py"));
	printf("[Jimmy::Info] Connecting to wiimote...\n");
	system("rosrun wiimote wiimote_node.py 1> /dev/null 2>&1 &");
	sleep(1);

	return 0;
}



const char* WM_script::WM_clc() {
	return exit_clc;
}

int WM_script::WM_add(int idx) {
	return 0;
}

int WM_script::WM_del(int idx) {
	return 0;
}

void WM_script::WM_update(int idx) {
	/*  */
	count = idx;
}

const char* WM_script::WM_get_audnm(char* target, int idx) {	//	sys

#ifndef _JMY_DUMMY

	char filenm[DIMCMD];
	sprintf(filenm, "%s%s%.02d%s", video_full_path, cur_user, idx, video_full_sufx);
	FILE* file_a = fopen(filenm, "r");
	if(idx < 0 || idx >= count)
		sprintf(target, "echo \"[Jimmy::Scrpit::Audio] #Vital Err# Invalid idx [%d]\"", idx);
	else {
		if (file_a == NULL) {
			sprintf(target, "echo \"[Jimmy::Scrpit::Audio] #Err# Unable to open file <%s>!\"", filenm);
		} else {
			sprintf(target, "mpg123 -q %s > /dev/null &", filenm);
			fclose(file_a);
		}
	}

#else
	sprintf(target, "mpg123 -q %s%s%.02d%s > /dev/null &", video_full_path, cur_user, idx, video_full_sufx);
#endif
	return target;
}

const char* WM_script::WM_get_txtnm(char* target, int idx) { //	text info
	if(idx < 0 || idx >= count)
		sprintf(target, "echo \"[Jimmy::Scrpit::Text] #Err# Invalid idx <%d>!\"", idx);
	else if(idx == 1) {

	} else
		sprintf(target, "echo \"[Jimmy::Scrpit::Text] Current Sentence ===> <%.02d %s>\"", idx, contect[idx]);
	return target;
}

const char* WM_script::WM_end_audnm(char* target) {	//	kill audio
	//*** set cmd[0] -> 0 on jimmy_server
	sprintf(target, "%s > /dev/null", video_stop_cmmd);
	return target;
}

const char* WM_script::WM_post_twip(char* target) {	//	twitter
	sprintf(target, "wget \"http://localhost/jimmytwitter/post.php?p=%s&t=%s\" > /dev/null &", twi_tran_path, local_tweet[cnt_p%DIMT]);
	printf("[Jimmy::Info] Twitter posted!\n");
	return target;
}

const char* WM_script::WM_get_vidnm(char* target) {	//	take picture
	// sprintf(target, "fswebcam -q -d /dev/video0 -r 1280x720 --jpeg 88 -D 1 -F 3 %s%s%.02d%s &", pic_full_path, cur_user, ++cnt_p, pic_full_sufx);
	//*** set cmd[0] -> i+2; cmd[2] -> 1 on jimmy_server
	printf("[Jimmy::Info] Taking Picture!\n");
	sprintf(target, "%s", twi_batch_cmd);
	printf("[Jimmy::Info] Picture Received!\n");
	return target;
}
