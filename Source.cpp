﻿#include "PoseDete.h"

int main(int argc, char *argv[])
{
	PoseDete poseDete;
	poseDete.Init();
	/*
	
	int facescope[4];
	bool empty;
	
	auto imageToProcess = cv::imread(imagePath);
	poseDete.GetFace(imageToProcess, facescope, empty);
	cv::imshow("test", imageToProcess);
	cv::waitKey(33);*/




	cv::VideoCapture cap(0);
	if (!cap.isOpened()) {
		return 0;
	}
	cv::Mat frame;
	std::vector<float> facescope;
	bool empty;

	while (cap.isOpened()) {
		cap >> frame;
		poseDete.GetFace(frame, facescope, empty);
		
		cv::imshow("test", frame);
		cv::waitKey(33);
		facescope.clear();
	}
//poseDete.detec_real_time_camera();
//	poseDete.detec_vedio("C:\\Users\\有对象真好\\Desktop\\openpose-master\\examples\\media\\video.avi");
//	poseDete.detec_images("C:\\Users\\有对象真好\\Desktop\\openpose-master\\examples\\media");
//	poseDete.detec_image("C:\\Users\\有对象真好\\Desktop\\imagedir\\00002.jpg");
	return 0;
}