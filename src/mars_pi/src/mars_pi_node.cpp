#include "ros/ros.h"
#include "geometry_msgs/PoseWithCovarianceStamped.h"

int count = 0;
int main(int argc, char** argv)
{
	int counter=0;
	ros::init(argc, argv, "mars_pi_node");
	ros::NodeHandle n;
	ros::Publisher status_pub = n.advertise<geometry_msgs::PoseWithCovarianceStamped>("status",1000);
	ros::Rate loop_rate(1);
	while(ros::ok()) {
		geometry_msgs::PoseWithCovarianceStamped pose_msg;
		// TODO this is just a hack to publish something
		pose_msg.pose.pose.position.x = counter++;
		status_pub.publish(pose_msg);	
		ros::spinOnce();
		loop_rate.sleep();
	}
	return 0;
}

