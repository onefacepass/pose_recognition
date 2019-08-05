#include "PoseDete.h"

int main(int argc, char *argv[])
{
	PoseDete poseDete;
	//初始化 必须有
	poseDete.Init();
	//修改落点区域  有默认值
	poseDete.SetElbow4PointScope(cv::Point2f(10, 10), cv::Point2f(100, 200));

	cv::VideoCapture cap(0);

	if (!cap.isOpened()) {
		return 0;
	}

	cv::Mat frame;
	int * rect = NULL;
	std::vector<cv::Point2f> skeleton;

	while (cap.isOpened()) {
		cap >> frame;

		
		// 检测
		int i = poseDete.DetectPose(frame, rect, skeleton);//探测
		
		// 若检测成功
		if (i ==0 && rect != NULL)
		{
			cv::rectangle(frame, cv::Point2f(rect[0], rect[1]), cv::Point2f(rect[2], rect[3]), cv::Scalar(255, 0, 0), 1, 1, 0);//画出得到的脸部框
		}

		cv::imshow("test", frame);

		cv::waitKey(33);
	}
	if (rect != NULL)
	{
		std::cout << "delete rect;" << std::endl;
		delete[] rect;
	}

	return 0;
}