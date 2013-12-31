#include <ros/ros.h>
#include <std_msgs/Int32.h>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

int m_flag = 0;
int cnt = 1;

void msgCallback(const std_msgs::Int32::ConstPtr& msg) {
	if(msg->data == 1) {
		m_flag = 1;
	} else {
		m_flag = 0;
	}
}

int main(int argc, char** argv)
{

	ros::init(argc, argv, "Jimmy_CES_2014_stl");

	ros::NodeHandle n_slav;
	ros::Subscriber n_pubs = n_slav.subscribe<std_msgs::Int32>("Jimmy_cmd", 10, &msgCallback);

	ros::Rate r(20);	// Hz

	while(ros::ok) {

		if(m_flag) {
			char target[256];
			sprintf(target, "fswebcam -q -d /dev/video0 -r 1024x720 --jpeg 88 -D 1 -F 3 /var/www/Jimmy_%d.jpg &", cnt++);
			system(target);
			sleep(2);
			system("wget http://localhost/post.php > /dev/null &");
		}
		ros::spinOnce();
		r.sleep();
		
	}

	return 0;
}
