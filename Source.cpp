#include "PoseDete.h"

int main(int argc, char *argv[])
{
	PoseDete poseDete;
	poseDete.Init();

	cv::VideoCapture cap(0);
	if (!cap.isOpened()) {
		return -1;
	}
	cv::Mat frame;
	std::vector<Pose2d> poseRes;

	while (cap.isOpened()) {
		cap >> frame;
		poseDete.DetePose(frame, poseRes);
		poseDete.DrawPoint(frame, poseRes);

		cv::imshow("test", frame);
		cv::waitKey(33);
		poseRes.clear();
	}
	return 0;
}