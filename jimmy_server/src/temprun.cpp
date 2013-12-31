#include <ros/ros.h>
#include <std_msgs/Float32MultiArray.h>

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

int m_flag = 0;
int cnt = 1, cmd = 0;
float m_head[3], m_move[3];

void msgCallback(const std_msgs::Float32MultiArray::ConstPtr& msg) {
	if(msg->data[0] > 0.95) {
		m_flag = 1;
	} else {
		m_flag = 0;
	}

	for(int i = 0; i < 3; ++i) {
		m_head[i] = msg[i+2];
		m_move[i] = msg[i+5];
	}
	cmd = floor(msg[]);
}

int main(int argc, char** argv)
{
	int i = 0;

	ros::init(argc, argv, "test_CES_2014_stl");

	ros::NodeHandle n_slav;
	ros::Publisher n_publ = n_slav.advertise<std_msgs::Float32MultiArray>("Motion_cmd", 1);
	ros::Subscriber n_subl = n_slav.subscribe<std_msgs::Float32MultiArray>("Jimmy_cmd", 1, &msgCallback);

	std_msgs::Float32MultiArray msgo;
	msgo.data.resize(4);

	ros::Rate r(20);	// Hz

	while(ros::ok) {

		if(m_flag) {
			char target[256];
			sprintf(target, "fswebcam -q -d /dev/video0 -r 1024x720 --jpeg 88 -D 1 -F 3 /var/www/uploads/photo.jpg &", cnt++);
			system(target);
			sleep(2);
			system("wget \"http://localhost/post.php?photo.jpg&t=Hello%20%20WOrld\!\" > /dev/null &");
		}
		
		msgo[]

		n_publ.publish(msgo);

		ros::spinOnce();
		r.sleep();
		
	}

	return 0;
}
