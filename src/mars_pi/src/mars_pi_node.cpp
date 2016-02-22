#include "ros/ros.h"
#include "mars_pi/status.h"
#include "geometry_msgs/PoseWithCovarianceStamped.h"

int count = 0;
bool cbService(mars_pi::status::Request &req,
		mars_pi::status::Response &res)
{
	res.status = count++;
	return true;
}
int main(int argc, char** argv)
{
	ros::init(argc, argv, "mars_pi_node");
	ros::NodeHandle n;
	ros::ServiceServer service = n.advertiseService("mars_pi_status", cbService);
	ros::Publisher status_pub = n.advertise<geometry_msgs::PoseWithCovarianceStamped>("status",1000);
	ros::Rate loop_rate(1);
	while(ros::ok()) {
		geometry_msgs::PoseWithCovarianceStamped pose_msg;
		status_pub.publish(pose_msg);	
		ros::spinOnce();
		loop_rate.sleep();
	}
	return 0;
}

