/***
Node to handle incoming commands from the rosbridge and interpret
them into messages for the robot's ros topics.
This is basically glue logic so that the cmd topic can be generic 
and the webserver/websocket client can just pass strings without 
knowing their contents.
*/
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Point.h"
#include <vector>
#include <sstream>

class Cmars_pi_cmd {
public:
	Cmars_pi_cmd(void);
	void cmdCallback(const std_msgs::String::ConstPtr& msg);
private:
	ros::NodeHandle n;
	ros::Publisher motor_pub;
	ros::Publisher grip_pub;
	ros::Subscriber sub;
};

Cmars_pi_cmd::Cmars_pi_cmd(void) 
{
	motor_pub = n.advertise<geometry_msgs::Point>("motor_cmd",1000);
	grip_pub = n.advertise<geometry_msgs::Point>("grip_cmd",1000);
	sub = n.subscribe("cmd",1000,&Cmars_pi_cmd::cmdCallback, this);
	printf("Constructor\n");
}

/* called when a String is published to this topic */
void Cmars_pi_cmd::cmdCallback(const std_msgs::String::ConstPtr& msg)
{
	ROS_INFO("mars_pi_cmd: %s", msg->data.c_str());
	/* parse the string into tokens sep by whitespace */
	std::istringstream s(msg->data);
	std::string tmp;
	std::vector<std::string> tokens;
	while(s >> tmp) {
		tokens.push_back(tmp);
	}
	printf("Got %i tokens\n",tokens.size());
	if(tokens[0] == "MT") {
		ROS_INFO("Move for a Time cmd");
		geometry_msgs::Point msg;
		float effort, time;
		sscanf(tokens[1].c_str(), "%f", &effort);
		sscanf(tokens[2].c_str(), "%f", &time);
		msg.x = msg.y = effort;
		msg.z = time;
		motor_pub.publish(msg);
		
	} else if(tokens[0] == "TT") {
		ROS_INFO("Turn for a Time cmd");
		geometry_msgs::Point msg;
		float effort, time;
		sscanf(tokens[1].c_str(), "%f", &effort);
		sscanf(tokens[2].c_str(), "%f", &time);
		msg.x = effort;
		msg.y = -effort;
		msg.z = time;
		motor_pub.publish(msg);
	} else if(tokens[0] == "GP") {
		ROS_INFO("Gripper command");
		geometry_msgs::Point msg;
		float grip, wrist;
		sscanf(tokens[1].c_str(), "%f", &grip);
		sscanf(tokens[2].c_str(), "%f", &wrist);
		msg.x = grip;
		msg.y = wrist;
		msg.z = 0.0;
		grip_pub.publish(msg);
	}
};

/* main does nothing but subscribe and wait for callbacks */
int main(int argc, char **argv)
{
	ros::init(argc,argv,"mars_pi_cmd");
	Cmars_pi_cmd c;
	ros::spin();
	return 0;
}
