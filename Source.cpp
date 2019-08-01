#include "PoseDete.h"

int main(int argc, char *argv[])
{
	PoseDete poseDete;
	poseDete.Init();
	poseDete.SetElbow4PointScope(cv::Point2f(50, 50), cv::Point2f(150, 150));

	

	cv::VideoCapture cap(0);
	if (!cap.isOpened()) {
		return 0;
	}
	cv::Mat frame;
	std::vector<float> facescope;
	bool empty;
	int * rect = NULL;

	while (cap.isOpened()) {
		cap >> frame;
		poseDete.DetectPose(frame, rect);
		

		if (rect != NULL)
		{
			cv::rectangle(frame, cv::Point2f(*rect, *(rect + 1)), cv::Point2f(*(rect + 2), *(rect + 3)), cv::Scalar(255, 0, 0), 1, 1, 0);
		}
		
		
		//test end 
		cv::imshow("test", frame);
		cv::waitKey(33);
		facescope.clear();
		
	}
	if (rect != NULL)
	{
#ifdef POSEDEBUG
		std::cout << "delete rect;" << std::endl;
#endif // POSEDEBUG

		
		delete rect;
	}

//poseDete.detec_real_time_camera();
//	poseDete.detec_vedio("C:\\Users\\有对象真好\\Desktop\\openpose-master\\examples\\media\\video.avi");
//	poseDete.detec_images("C:\\Users\\有对象真好\\Desktop\\openpose-master\\examples\\media");
//	poseDete.detec_image("C:\\Users\\有对象真好\\Desktop\\imagedir\\00002.jpg");
	return 0;
}