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
	   @返回值
	   0  正常结束
	   -1 image中没有人
	   -2 抬手了，但头部数据不完整
	   -3 没有抬手或抬手了不在指定范围

	   各参数通过 引用 返回值
	   1.frame 输入图像
	   2.facescope 返回值脸部数据
		   facescope[0] = leftup.x
		   facescope[1] = leftup.y
		   facescope[2] = rightdown.x
		   facescope[3] = rightdown.y
	   3.facescopeIsEmpty facescope数组是否为空
	   true 空
	   false 非空
	   4.Attention 内部含有显示判断区域坐标的测试函数

	*/
	int DetectPose(cv::Mat &frame, int *&  rect);
	/*
	初始化函数
	1.判断范围的定义
	2.Openpose相关线程等初始化
	*/
	void Init();
	/*
	设置手臂4号关键点在屏幕上的有效降落范围
	leftup 输入的左上方的点
	rightdown 输入的右下方的点
	若无设置，则为默认值(具体可参见Init())
	*/
	void SetElbow4PointScope(cv::Point2f leftup, cv::Point2f rightdown);
		
private:
	/*线程*/
	op::Wrapper opWrapper{ op::ThreadManagerMode::Asynchronous };
	
	/*
	将datumsPtr中的点转存到poseKeypoints,将坐标数据转换成容易接受的格式
	poseKeypoints 包含所有人的骨骼信息 25个为一个人
	[0]-[24] 第一个人
	[25]-[49]第二个人
	...
	*/
	void TransKeypoints(const std::shared_ptr<std::vector<std::shared_ptr<op::Datum>>>& datumsPtr, std::vector<Pose2d>& poseKeypoints);
	/*
	Openpose全局宏的的使用，根据全局宏的定义调用相关函数
	*/
	void configureWrapper(op::Wrapper& opWrapper);
	/*
	@返回值 判断抬手ture后，4号点在数组中下标
	函数功能 判断抬手动作 
	image 输入图像 引用
	poseKeypoints 包含所有人的骨骼信息 25个为一个人
	[0]-[24] 第一个人
	[25]-[49]第二个人
	...

	Attention 内部含有画出4号点降落范围的的函数
	*/
	int PanDuanTaiShou(cv::Mat & image, std::vector<Pose2d>& poseKeypoints);
	/*判断坐标是否为空
	ture 空
	false 非空
	*/
	bool Pose2dIsEmpty(Pose2d poseKeypoint);
	/*
	添加点之间的连线功能
	1.画出所有非空点
	2.按一定规则画出点之间的连线 人与人之间不互连
	image 输入图像
	poseKeypoints 包含所有人的骨骼信息 25个为一个人
	[0]-[24] 第一个人
	[25]-[49]第二个人
	...
	*/
	void DrawPoint(cv::Mat & image, std::vector<Pose2d>& poseKeypoints);
	/*
	获得脸部位置轮廓
	zuobiao4_id 输入值，PanDuanTaiShou函数返回值，判断抬手true的4号点在数组中下标
	poseKeypoints 包含所有人的骨骼信息 25个为一个间隔
	facescope 返回的脸部轮廓
	facescope[0] = 17号点（左耳）的x
	facescope[1] = 17y + (17y-1y) 1为脖颈部
	facescope[2] = 18x 18为右耳
	facescope[3] = 18y + (18y-1y) 1为脖颈部
	Attention 当左耳，右耳，脖颈三个点全部存在时，才能获取轮廓
	*/
	void GetFaceScope(int& zuobiao4_id, std::vector<Pose2d>& poseKeypoints, std::vector<float> &facescope, cv::Mat  test_image);
	/*
	在图像上骨骼位置处输出 index:x,y 的信息，index为序号
	*/
	void ShowPointIndexInImage(cv::Mat & image, std::vector<Pose2d>& poseKeypoints);
	
	/*
	探测单张图像骨骼信息，将骨骼画与图像上，并输出到屏幕
	imagepath 图像路径 使用双斜杠
	*/
	void DetecImage(std::string imagepath);
	/*
	探测文件夹下多个图像骨骼信息,将骨骼画与图像上，并输出到屏幕
	imagepath 图像路径 使用双斜杠
	*/
	void DetecImages(std::string imagepath);
	/*
	探测视频骨骼信息,将骨骼画与图像上，并输出到屏幕
	imagepath 图像路径 使用双斜杠
	*/
	void DetecVedio(std::string vediopath);
	/*
	探测摄像头实时骨骼信息,将骨骼画与图像上，并输出到屏幕
	*/
	void DetecRealTimeCamera();
	/*
	输入图像，返回骨骼坐标
	frame 输入图像 引用
	poseKeypoints 返回的骨骼坐标 引用
	*/
	int DetePose(cv::Mat &frame, std::vector<Pose2d>& poseKeypoints);
	/*
	将骨骼坐标按 index：x,y输出到命令行窗口
	*/
	void ShowZuoBiao(std::vector<Pose2d> poseKeypoints);
	/*
	判断输入点是否位于区域内，temp内
	ture 位于
	false 不位于
	*/
	bool InScope(Pose2d Point);

	struct elbow4pointscope //手臂4号关键点在屏幕上的有效降落范围
	{
		cv::Point2f leftup;//左上点 
		cv::Point2f rightdown;//右下点
	}temp;


	};

