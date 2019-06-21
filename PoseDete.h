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

	void DrawPoint(cv::Mat & image, std::vector<Pose2d>& poseKeypoints);//��ӵ�֮������߹���

	bool Pose2dIsEmpty(Pose2d poseKeypoint);//�ж������Ƿ�Ϊ��

	void get_face_scope();//�������λ������

	bool panduantaishou(std::vector<Pose2d>& poseKeypoints);//�ж�̧�ֶ���
    
	void showPointIndexInImage(cv::Mat & image, std::vector<Pose2d>& poseKeypoints);//��ͼ���ϱ�ע��������

	void detec_image(string imagepath);//̽�ⵥ��ͼ�������Ϣ

	void detec_images(string imagepath);//̽���ļ����¶��ͼ�������Ϣ

	void detec_vedio(string vediopath);//̽����Ƶ������Ϣ

	void detec_real_time_camera();//̽�������Ϣ
private:
	op::Wrapper opWrapper{ op::ThreadManagerMode::Asynchronous };

	void transKeypoints(const std::shared_ptr<std::vector<std::shared_ptr<op::Datum>>>& datumsPtr, std::vector<Pose2d>& poseKeypoints);/*��datumsPtr�еĵ�ת�浽poseKeypoints*/

	void configureWrapper(op::Wrapper& opWrapper);

	};

