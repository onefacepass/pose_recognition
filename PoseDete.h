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
	PoseDete();//��ʼ��4�ŵ��жϷ�Χ�����ο�

	~PoseDete();
	
	int GetFace(cv::Mat &frame, std::vector<float> &facescope, bool &facescopeIsEmpty);

		
public:

	op::Wrapper opWrapper{ op::ThreadManagerMode::Asynchronous };

	void Init();

	void transKeypoints(const std::shared_ptr<std::vector<std::shared_ptr<op::Datum>>>& datumsPtr, std::vector<Pose2d>& poseKeypoints);/*��datumsPtr�еĵ�ת�浽poseKeypoints*/

	void configureWrapper(op::Wrapper& opWrapper);

	int panduantaishou(cv::Mat & image, std::vector<Pose2d>& poseKeypoints);//�ж�̧�ֶ��� ����4�ŵ����������±�

	bool Pose2dIsEmpty(Pose2d poseKeypoint);//�ж������Ƿ�Ϊ��

	void DrawPoint(cv::Mat & image, std::vector<Pose2d>& poseKeypoints);//��ӵ�֮������߹���

	void get_face_scope(int zuobiao4_id, std::vector<Pose2d>& poseKeypoints, std::vector<float> &facescope);//�������λ������  ��17����,����0������18������1�ĸ������head_scope��

	void showPointIndexInImage(cv::Mat & image, std::vector<Pose2d>& poseKeypoints);//��ͼ���ϱ�ע��������

	void SetElbow4PointScope(cv::Point2f leftup, cv::Point2f rightdown);//�����ֱ�4�Źؼ�������Ļ�ϵ���Ч���䷶Χ

	void detec_image(std::string imagepath);//̽�ⵥ��ͼ�������Ϣ

	void detec_images(std::string imagepath);//̽���ļ����¶��ͼ�������Ϣ

	void detec_vedio(std::string vediopath);//̽����Ƶ������Ϣ

	void detec_real_time_camera();//̽������ͷʵʱ������Ϣ

	int DetePose(cv::Mat &frame, std::vector<Pose2d>& poseKeypoints);

	void ShowZuoBiao(std::vector<Pose2d> poseKeypoints);

	bool InScope(Pose2d Point);

	struct elbow4pointscope //�ֱ�4�Źؼ�������Ļ�ϵ���Ч���䷶Χ
	{
		cv::Point2f leftup;//���ϵ� 
		cv::Point2f rightdown;//���µ�
	}temp;


	};

