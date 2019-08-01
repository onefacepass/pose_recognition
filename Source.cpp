#include "PoseDete.h"

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
	int * rect = NULL;
	//cv::Mat Image_temp;
	while (cap.isOpened()) {
		cap >> frame;
		poseDete.DetectPose(frame, rect);
		//testing rect
		//= frame;


		if (rect != NULL)
		{
			std::cout << * rect << std::endl;
			cv::rectangle(frame, cv::Point2f(*rect, *(rect + 1)), cv::Point2f(*(rect + 2), *(rect + 3)), cv::Scalar(255, 0, 0), 1, 1, 0);
		}
		
		
		//test end 
		cv::imshow("test", frame);
		cv::waitKey(33);
		facescope.clear();
		
	}
	if (rect != NULL)
	{
		std::cout << "delete rect;" << std::endl;
		delete rect;
	}

//poseDete.detec_real_time_camera();
//	poseDete.detec_vedio("C:\\Users\\有对象真好\\Desktop\\openpose-master\\examples\\media\\video.avi");
//	poseDete.detec_images("C:\\Users\\有对象真好\\Desktop\\openpose-master\\examples\\media");
//	poseDete.detec_image("C:\\Users\\有对象真好\\Desktop\\imagedir\\00002.jpg");
	return 0;
}