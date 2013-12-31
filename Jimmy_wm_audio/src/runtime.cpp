#include <ros/ros.h>

#include <Jimmy_wm_audio/pub_jimmy.h>
#include <Jimmy_wm_audio/pub_motion.h>
#include <Jimmy_wm_audio/wim_control.h>
#include <Jimmy_wm_audio/loc_scripts.h>

#include <jimmy/jimmy_command.h>

using namespace intel_jimmy;

const int VALLEN = 8;

int actor(WM_script &jimmy_script, WM_teleop &jimmy_teleop, WM_motion &jimmy_action, jimmy::jimmy_command &msg);	// **msg
void msgUpdate(jimmy::jimmy_command &msg);	// **msg

int main(int argc, char** argv)
{

	WM_script jimmy_script;
	jimmy_script.WM_init();

	ros::init(argc, argv, "Jimmy_CES2014");

	ros::NodeHandle n_cli;
	ros::Publisher n_pub = n_cli.advertise<jimmy::jimmy_command>("Jimmy_cmd", 1);	// **msg

	jimmy::jimmy_command msg;	// **msg
	msg.param.resize(VALLEN);		// 0:wii-vy 1:wii-vp 2:wii-vr 3:ps3-vf 4:ps3-vl 5:ps3-r 6:pic 7:twi 8:STATE

	ros::Rate r(20);	// freq (Hz)

	WM_teleop jimmy_teleop;
	WM_motion jimmy_action;

	while(ros::ok) {

		msgUpdate(msg);

		if(actor(jimmy_script, jimmy_teleop, jimmy_action, msg) == 1) {
			return -1;
		}

		n_pub.publish(msg);

		ros::spinOnce();
		r.sleep();

	}

	return 0;
}

void msgUpdate(jimmy::jimmy_command &msg) {

	// msg.cmd = 0;

	for(int i = 0; i < VALLEN; ++i) {
		msg.param[i] = 0.0;
	}

}

int actor(WM_script &jimmy_script, WM_teleop &jimmy_teleop, WM_motion &jimmy_action, jimmy::jimmy_command &msg) {
// int actor(WM_script &jimmy_script, WM_teleop &jimmy_teleop, WM_motion &jimmy_action, std_msgs::Int32 &msg) {

	char syscmd[DIMCMD];

	if(jimmy_teleop.CurState() > WM_STA_ACT)	// print banner
		printf("\n===== >>> Current Activate Level: %d\n", jimmy_teleop.CurState());

	switch(jimmy_teleop.CurState()) {

		case WM_STA_EXIT :
			printf("===== <<< Jimmy is going to leave, bye!\n");
			msg.cmd = -1;	// *** TMP ***
			system(jimmy_script.WM_clc());
			return 1;

		case WM_STA_PIC :
			// system(jimmy_script.WM_get_vidnm(cmd));
			// msg.buttons[0] = 1;
			// msg.data = 1;
			msg.param[6] = 1.17;

		case WM_STA_TWI :
			// system(jimmy_script.WM_post_twip(cmd));
			if(!msg.param[0]) {
				msg.param[7] = 1.17;
			}

		case WM_STA_AUD :
			if(jimmy_teleop.IsReady() == 1) {
				msg.cmd = jimmy_teleop.ReportCMD();
				system(jimmy_script.WM_end_audnm(syscmd));
				system(jimmy_script.WM_get_audnm(syscmd, jimmy_teleop.PlayIndex()));
			}

		case WM_STA_INFO :
			system(jimmy_script.WM_get_txtnm(syscmd, jimmy_teleop.PlayIndex()));
			if(jimmy_teleop.IsReady() == 1) {
				jimmy_teleop.AddIndex();
			}

		case WM_STA_ACT :
			jimmy_teleop.DataHeadYPR(msg.param[0], msg.param[1], msg.param[2]);
			// jimmy_action.UpdateHead(jsp_x, jsp_y, jsp_z);
			// jimmy_action.PostHeadCMD(msg.data[0], msg.data[1], msg.data[2]);
			// TODO: add action index here; (msg.param[5], msg.param[6], msg.param[7]);
			jimmy_teleop.ResetState();
			break;

		default :
			return 0;
	}

	if(jimmy_teleop.CurState() > WM_STA_ACT)	// print end
		printf("===== <<< Section End\n");

	return 0;
}
