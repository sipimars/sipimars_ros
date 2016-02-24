#include <iostream>
#include <cstdlib>
#include <fstream>
#include "raspicam_cv.h"
#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/CompressedImage.h>

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main ( int argc,char **argv ) {

	ros::init(argc,argv,"raspicam");
	ros::NodeHandle n;
	ros::Publisher image_pub = n.advertise<sensor_msgs::CompressedImage>(
		"imageJpg",1000);
	ros::Rate loop_rate(1);

	raspicam::RaspiCam_Cv Camera;
	cout<<"Connecting to camera"<<endl;
	if ( !Camera.open() ) {
		cerr<<"Error opening camera"<<endl;
		return -1;
	}
	cout<<"Connected to camera ="<<Camera.getId() <<endl;
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
		cv::imencode(".jpg",cv_image.image, image_msg.data, 
				compression_params);
		image_pub.publish(image_msg);

		ros::spinOnce();
		loop_rate.sleep();
	}
	Camera.release();
	return 0;
}
