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
	

	/*
	   @����ֵ ������
	   ������ͨ�� ���� ����ֵ
	   1.frame ����ͼ��
	   2.facescope ����ֵ��������
		   facescope[0] = leftup.x
		   facescope[1] = leftup.y
		   facescope[2] = rightdown.x
		   facescope[3] = rightdown.y
	   3.facescopeIsEmpty facescope�����Ƿ�Ϊ��
	   true ��
	   false �ǿ�
	   4.Attention �ڲ�������ʾ�ж���������Ĳ��Ժ���

	*/
	int GetFace(cv::Mat &frame, std::vector<float> &facescope, bool &facescopeIsEmpty);

		
public:
	/*�߳�*/
	op::Wrapper opWrapper{ op::ThreadManagerMode::Asynchronous };
	/*
	��ʼ������
	1.�жϷ�Χ�Ķ���
	2.Openpose����̵߳ȳ�ʼ��
	*/
	void Init();
	/*
	��datumsPtr�еĵ�ת�浽poseKeypoints,����������ת�������׽��ܵĸ�ʽ
	poseKeypoints ���������˵Ĺ�����Ϣ 25��Ϊһ����
	[0]-[24] ��һ����
	[25]-[49]�ڶ�����
	...
	*/
	void TransKeypoints(const std::shared_ptr<std::vector<std::shared_ptr<op::Datum>>>& datumsPtr, std::vector<Pose2d>& poseKeypoints);
	/*
	Openposeȫ�ֺ�ĵ�ʹ�ã�����ȫ�ֺ�Ķ��������غ���
	*/
	void configureWrapper(op::Wrapper& opWrapper);
	/*
	@����ֵ �ж�̧��ture��4�ŵ����������±�
	�������� �ж�̧�ֶ��� 
	image ����ͼ�� ����
	poseKeypoints ���������˵Ĺ�����Ϣ 25��Ϊһ����
	[0]-[24] ��һ����
	[25]-[49]�ڶ�����
	...

	Attention �ڲ����л���4�ŵ㽵�䷶Χ�ĵĺ���
	*/
	int PanDuanTaiShou(cv::Mat & image, std::vector<Pose2d>& poseKeypoints);
	/*�ж������Ƿ�Ϊ��
	ture ��
	false �ǿ�
	*/
	bool Pose2dIsEmpty(Pose2d poseKeypoint);
	/*
	��ӵ�֮������߹���
	1.�������зǿյ�
	2.��һ�����򻭳���֮������� ������֮�䲻����
	image ����ͼ��
	poseKeypoints ���������˵Ĺ�����Ϣ 25��Ϊһ����
	[0]-[24] ��һ����
	[25]-[49]�ڶ�����
	...
	*/
	void DrawPoint(cv::Mat & image, std::vector<Pose2d>& poseKeypoints);
	/*
	�������λ������
	zuobiao4_id ����ֵ��PanDuanTaiShou��������ֵ���ж�̧��true��4�ŵ����������±�
	poseKeypoints ���������˵Ĺ�����Ϣ 25��Ϊһ�����
	facescope ���ص���������
	facescope[0] = 17�ŵ㣨�������x
	facescope[1] = 17y + (17y-1y) 1Ϊ������
	facescope[2] = 18x 18Ϊ�Ҷ�
	facescope[3] = 18y + (18y-1y) 1Ϊ������
	Attention ��������Ҷ�������������ȫ������ʱ�����ܻ�ȡ����
	*/
	void GetFaceScope(int& zuobiao4_id, std::vector<Pose2d>& poseKeypoints, std::vector<float> &facescope, cv::Mat  test_image);
	/*
	��ͼ���Ϲ���λ�ô���� index:x,y ����Ϣ��indexΪ���
	*/
	void ShowPointIndexInImage(cv::Mat & image, std::vector<Pose2d>& poseKeypoints);
	/*
	�����ֱ�4�Źؼ�������Ļ�ϵ���Ч���䷶Χ
	leftup ��������Ϸ��ĵ�
	rightdown ��������·��ĵ�
	*/
	void SetElbow4PointScope(cv::Point2f leftup, cv::Point2f rightdown);
	/*
	̽�ⵥ��ͼ�������Ϣ������������ͼ���ϣ����������Ļ
	imagepath ͼ��·�� ʹ��˫б��
	*/
	void DetecImage(std::string imagepath);
	/*
	̽���ļ����¶��ͼ�������Ϣ,����������ͼ���ϣ����������Ļ
	imagepath ͼ��·�� ʹ��˫б��
	*/
	void DetecImages(std::string imagepath);
	/*
	̽����Ƶ������Ϣ,����������ͼ���ϣ����������Ļ
	imagepath ͼ��·�� ʹ��˫б��
	*/
	void DetecVedio(std::string vediopath);
	/*
	̽������ͷʵʱ������Ϣ,����������ͼ���ϣ����������Ļ
	*/
	void DetecRealTimeCamera();
	/*
	����ͼ�񣬷��ع�������
	frame ����ͼ�� ����
	poseKeypoints ���صĹ������� ����
	*/
	int DetePose(cv::Mat &frame, std::vector<Pose2d>& poseKeypoints);
	/*
	���������갴 index��x,y����������д���
	*/
	void ShowZuoBiao(std::vector<Pose2d> poseKeypoints);
	/*
	�ж�������Ƿ�λ�������ڣ�temp��
	ture λ��
	false ��λ��
	*/
	bool InScope(Pose2d Point);

	struct elbow4pointscope //�ֱ�4�Źؼ�������Ļ�ϵ���Ч���䷶Χ
	{
		cv::Point2f leftup;//���ϵ� 
		cv::Point2f rightdown;//���µ�
	}temp;


	};

