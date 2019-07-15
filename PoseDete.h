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
	PoseDete();//初始化4号点判断范围（矩形框）

	~PoseDete();
	
	int GetFace(cv::Mat &frame, std::vector<float> &facescope, bool &facescopeIsEmpty);

		
public:

	op::Wrapper opWrapper{ op::ThreadManagerMode::Asynchronous };

	void Init();

	void transKeypoints(const std::shared_ptr<std::vector<std::shared_ptr<op::Datum>>>& datumsPtr, std::vector<Pose2d>& poseKeypoints);/*将datumsPtr中的点转存到poseKeypoints*/

	void configureWrapper(op::Wrapper& opWrapper);

	int panduantaishou(cv::Mat & image, std::vector<Pose2d>& poseKeypoints);//判断抬手动作 返回4号点在数组中下标

	bool Pose2dIsEmpty(Pose2d poseKeypoint);//判断坐标是否为空

	void DrawPoint(cv::Mat & image, std::vector<Pose2d>& poseKeypoints);//添加点之间的连线功能

	void get_face_scope(int zuobiao4_id, std::vector<Pose2d>& poseKeypoints, std::vector<float> &facescope);//获得脸部位置轮廓  将17右眼,鼻子0，左眼18，脖子1四个点存入head_scope里

	void showPointIndexInImage(cv::Mat & image, std::vector<Pose2d>& poseKeypoints);//在图像上标注坐标的序号

	void SetElbow4PointScope(cv::Point2f leftup, cv::Point2f rightdown);//设置手臂4号关键点在屏幕上的有效降落范围

	void detec_image(std::string imagepath);//探测单张图像骨骼信息

	void detec_images(std::string imagepath);//探测文件夹下多个图像骨骼信息

	void detec_vedio(std::string vediopath);//探测视频骨骼信息

	void detec_real_time_camera();//探测摄像头实时骨骼信息

	int DetePose(cv::Mat &frame, std::vector<Pose2d>& poseKeypoints);

	void ShowZuoBiao(std::vector<Pose2d> poseKeypoints);

	bool InScope(Pose2d Point);

	struct elbow4pointscope //手臂4号关键点在屏幕上的有效降落范围
	{
		cv::Point2f leftup;//左上点 
		cv::Point2f rightdown;//右下点
	}temp;


	};

