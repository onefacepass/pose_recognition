#pragma once
#include <openpose/headers.hpp>
#include <vector>

struct Pose2d
{
	float x;
	float y;
	float score;
};

class PoseDete {
public:
	PoseDete();

	~PoseDete();

	void Init();

	int DetePose(cv::Mat &frame, std::vector<Pose2d>& poseKeypoints);

	void DrawPoint(cv::Mat & image, std::vector<Pose2d>& poseKeypoints);//添加点之间的连线功能

	
	void get_face_scope();//获得脸部位置轮廓

	void detec_image(string imagepath);

	void detec_images(string imagepath);

	void detec_vedio(string vediopath);

	void detec_real_time_camera();
private:
	op::Wrapper opWrapper{ op::ThreadManagerMode::Asynchronous };

	void printKeypoints(const std::shared_ptr<std::vector<std::shared_ptr<op::Datum>>>& datumsPtr, std::vector<Pose2d>& poseKeypoints);

	void configureWrapper(op::Wrapper& opWrapper);

	};

