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
	
		int DetectPose(cv::Mat &frame, int *&  _rect,std::vector<cv::Point2f> &skeleton_points);
		
		void Init();
	
		void SetElbow4PointScope(cv::Point2f leftup, cv::Point2f rightdown);
		
	private:
		
		op::Wrapper opWrapper{ op::ThreadManagerMode::Asynchronous };
	
		
		void TransKeypoints(const std::shared_ptr<std::vector<std::shared_ptr<op::Datum>>>& datumsPtr, std::vector<Pose2d>& poseKeypoints);
		
		void configureWrapper(op::Wrapper& opWrapper);
		
		int PanDuanTaiShou(cv::Mat & image, std::vector<Pose2d>& poseKeypoints);
		
		bool Pose2dIsEmpty(Pose2d poseKeypoint);
		
		void DrawPoint(cv::Mat & image, std::vector<Pose2d>& poseKeypoints);
		
		void GetFaceScope(int& zuobiao4_id, std::vector<Pose2d>& poseKeypoints, std::vector<float> &facescope, cv::Mat  test_image);
		
		void ShowPointIndexInImage(cv::Mat & image, std::vector<Pose2d>& poseKeypoints);
	
		
		void DetecImage(std::string imagepath);
		
		void DetecImages(std::string imagepath);
		
		void DetecVedio(std::string vediopath);
		
		void DetecRealTimeCamera();
		
		int DetePose(cv::Mat &frame, std::vector<Pose2d>& poseKeypoints);
	
		bool InScope(Pose2d Point);

		struct elbow4pointscope 
		{
			cv::Point2f leftup;
			cv::Point2f rightdown;
		}temp;

	};

