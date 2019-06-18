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

	bool Pose2dIsEmpty(Pose2d poseKeypoint);//判断坐标是否为空

	void get_face_scope();//获得脸部位置轮廓

	bool panduantaishou(std::vector<Pose2d>& poseKeypoints);//判断抬手动作

	void detec_image(string imagepath);

	void detec_images(string imagepath);

	void detec_vedio(string vediopath);

	void detec_real_time_camera();
private:
	op::Wrapper opWrapper{ op::ThreadManagerMode::Asynchronous };

	void transKeypoints(const std::shared_ptr<std::vector<std::shared_ptr<op::Datum>>>& datumsPtr, std::vector<Pose2d>& poseKeypoints);/*将datumsPtr中的点转存到poseKeypoints*/

	void configureWrapper(op::Wrapper& opWrapper);

	};

