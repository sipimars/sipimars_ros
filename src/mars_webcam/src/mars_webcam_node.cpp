/*********************************************************
Ros node to caputer images from the webcam, and
publish them over the rosbridge for the 
webserver to read.
JW
********************************************************/
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/CompressedImage.h>
#include "std_msgs/String.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main ( int argc,char **argv ) {
	ros::init(argc,argv,"webcam");
	ros::NodeHandle n;
	ros::Publisher image_pub = n.advertise<sensor_msgs::CompressedImage>("imageJpg",1000);

	/// this sets the frame rate for the camera topic
	ros::Rate loop_rate(1);
	VideoCapture Camera(0);
	cv_bridge::CvImage cv_image;
	cv_image.encoding = "bgr8";
	sensor_msgs::CompressedImage image_msg;
	image_msg.format = std::string("jpeg");
	int i=0;
	cv::Size cameraResolution(2592,1944);

	int count = 0;
	vector<int> compression_params;
	compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
	compression_params.push_back(50);
	cv::Size sz(324*2,243*2);
	while(ros::ok()) 
	{
		Camera.grab();
		Camera.retrieve ( cv_image.image );
		cv::resize(cv_image.image,cv_image.image,sz);
		// temp for testing
		cv::imencode(".jpg",cv_image.image, image_msg.data, compression_params);
		image_pub.publish(image_msg);

		ros::spinOnce();
		loop_rate.sleep();
	}
	Camera.release();
	return 0;
}
