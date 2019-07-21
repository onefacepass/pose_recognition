#include "PoseDete.h"
#include <openpose/flags.hpp>
PoseDete::PoseDete()
{
}

PoseDete::~PoseDete()
{
}
void PoseDete::Init() {
	//ËÄºÅµãÅÐ¶Ï·¶Î§µÄ³õÊ¼»¯
	temp.leftup = cv::Point2f(10, 50);
	temp.rightdown = cv::Point2f(100, 200);
	
	op::log("Starting OpenPose demo...", op::Priority::High);
	// Configuring OpenPose
	op::log("Configuring OpenPose...", op::Priority::High);
	configureWrapper(opWrapper);

	// Starting OpenPose
	op::log("Starting thread(s)...", op::Priority::High);
	opWrapper.start();
}

int PoseDete::GetFace(cv::Mat& frame, std::vector<float> &facescope, bool &facescopeIsEmpty) {//Ì½²âµ¥ÕÅÍ¼Ïñ ·µ»ØÁ³²¿ÂÖÀª
	std::vector<Pose2d> poseRes;

	DetePose(frame, poseRes);
	DrawPoint(frame, poseRes);

	//show temp in picture
	cv::putText(frame,":(" + std::to_string(temp.leftup.x) + "," + std::to_string(temp.leftup.y) + ")", temp.leftup, cv::FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 255));
	cv::putText(frame, ":(" + std::to_string(temp.rightdown.x) + "," + std::to_string(temp.rightdown.y) + ")", temp.rightdown, cv::FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 255));
	//ShowZuoBiao(poseRes);
	int zuobiao4_id = PanDuanTaiShou(frame, poseRes);
	std::cout << "zuobiao4_id" << zuobiao4_id<<"size:"<< poseRes.size() << std::endl;
	  //¸³ÖµÊý×é
	if (zuobiao4_id % 4 == 0)//不够完善 无法摒弃10位长的乱码，
	{
		facescopeIsEmpty = false;//Êý×é·Ç¿Õ
		std::vector<float> facescope_temp;
		GetFaceScope(zuobiao4_id, poseRes, facescope_temp, frame);
		facescope = facescope_temp;
	}
	else
	{
		facescopeIsEmpty = true;//Êý×é¿Õ
	}

	poseRes.clear();//Çå¿ÕÊý×é
	return 0;
}

void PoseDete::DrawPoint(cv::Mat& image, std::vector<Pose2d>& poseKeypoints) {
	for (size_t i = 0; i < poseKeypoints.size(); ++i) {
		if (!Pose2dIsEmpty(poseKeypoints[i]))//µã·Ç¿Õ
		{
			circle(image, cv::Point2d(poseKeypoints[i].x, poseKeypoints[i].y), 3, cv::Scalar(255, 0, 0), -1);//»­³öµã
		}
		
	}
	for (size_t i = 0; i < poseKeypoints.size(); i += 25)
	{
		    //0-1
		if (!Pose2dIsEmpty(poseKeypoints[i]) && !Pose2dIsEmpty(poseKeypoints[i + 1]))/*µ±Á½¸öµã¶¼´æÔÚÊ±,»­³öÖ®¼äµÄÁ¬Ïß*/ {
			cv::line(image, cv::Point2d(poseKeypoints[i].x, poseKeypoints[i].y), cv::Point2d(poseKeypoints[i + 1].x, poseKeypoints[i + 1].y), cv::Scalar(0, 255, 255), 3, 8, 0);
		}
		
			//0-15
		if (!Pose2dIsEmpty(poseKeypoints[i]) && !Pose2dIsEmpty(poseKeypoints[i + 15]))/*µ±Á½¸öµã¶¼´æÔÚÊ±,»­³öÖ®¼äµÄÁ¬Ïß*/ {
			cv::line(image, cv::Point2d(poseKeypoints[i].x, poseKeypoints[i].y), cv::Point2d(poseKeypoints[i + 15].x, poseKeypoints[i + 15].y), cv::Scalar(0, 255, 255), 3, 8, 0);
		}
		//0-16
		if (!Pose2dIsEmpty(poseKeypoints[i]) && !Pose2dIsEmpty(poseKeypoints[i + 15]))/*µ±Á½¸öµã¶¼´æÔÚÊ±,»­³öÖ®¼äµÄÁ¬Ïß*/ {
			cv::line(image, cv::Point2d(poseKeypoints[i].x, poseKeypoints[i].y), cv::Point2d(poseKeypoints[i + 16].x, poseKeypoints[i + 16].y), cv::Scalar(0, 255, 255), 3, 8, 0);
		}
			//14-13
		if (!Pose2dIsEmpty(poseKeypoints[i+14]) && !Pose2dIsEmpty(poseKeypoints[i + 13]))/*µ±Á½¸öµã¶¼´æÔÚÊ±,»­³öÖ®¼äµÄÁ¬Ïß*/ {
			cv::line(image, cv::Point2d(poseKeypoints[i + 14].x, poseKeypoints[i + 14].y), cv::Point2d(poseKeypoints[i + 13].x, poseKeypoints[i + 13].y), cv::Scalar(0, 255, 255), 3, 8, 0);
		}
			//15-17
		if (!Pose2dIsEmpty(poseKeypoints[i+15]) && !Pose2dIsEmpty(poseKeypoints[i + 17]))/*µ±Á½¸öµã¶¼´æÔÚÊ±,»­³öÖ®¼äµÄÁ¬Ïß*/ {
			cv::line(image, cv::Point2d(poseKeypoints[i + 15].x, poseKeypoints[i + 15].y), cv::Point2d(poseKeypoints[i + 17].x, poseKeypoints[i + 17].y), cv::Scalar(0, 255, 255), 3, 8, 0);
		}
		//16-18
		if (!Pose2dIsEmpty(poseKeypoints[i + 16]) && !Pose2dIsEmpty(poseKeypoints[i + 18]))/*µ±Á½¸öµã¶¼´æÔÚÊ±,»­³öÖ®¼äµÄÁ¬Ïß*/ {
			cv::line(image, cv::Point2d(poseKeypoints[i + 16].x, poseKeypoints[i + 16].y), cv::Point2d(poseKeypoints[i + 18].x, poseKeypoints[i + 18].y), cv::Scalar(0, 255, 255), 3, 8, 0);
		}
			//1-2
		if (!Pose2dIsEmpty(poseKeypoints[i+1]) && !Pose2dIsEmpty(poseKeypoints[i + 2]))/*µ±Á½¸öµã¶¼´æÔÚÊ±,»­³öÖ®¼äµÄÁ¬Ïß*/ {
			cv::line(image, cv::Point2d(poseKeypoints[i+1].x, poseKeypoints[i+1].y), cv::Point2d(poseKeypoints[i + 2].x, poseKeypoints[i + 2].y), cv::Scalar(0, 255, 255), 3, 8, 0);
		}
			//1-5
		if (!Pose2dIsEmpty(poseKeypoints[i+1]) && !Pose2dIsEmpty(poseKeypoints[i + 5]))/*µ±Á½¸öµã¶¼´æÔÚÊ±,»­³öÖ®¼äµÄÁ¬Ïß*/ {
			cv::line(image, cv::Point2d(poseKeypoints[i+1].x, poseKeypoints[i+1].y), cv::Point2d(poseKeypoints[i + 5].x, poseKeypoints[i + 5].y), cv::Scalar(0, 255, 255), 3, 8, 0);
		}
			//2-3
		if (!Pose2dIsEmpty(poseKeypoints[i+2]) && !Pose2dIsEmpty(poseKeypoints[i + 3]))/*µ±Á½¸öµã¶¼´æÔÚÊ±,»­³öÖ®¼äµÄÁ¬Ïß*/ {
			cv::line(image, cv::Point2d(poseKeypoints[i+2].x, poseKeypoints[i+2].y), cv::Point2d(poseKeypoints[i + 3].x, poseKeypoints[i + 3].y), cv::Scalar(0, 255, 255), 3, 8, 0);
		}
			//3-4
		if (!Pose2dIsEmpty(poseKeypoints[i+3]) && !Pose2dIsEmpty(poseKeypoints[i + 4]))/*µ±Á½¸öµã¶¼´æÔÚÊ±,»­³öÖ®¼äµÄÁ¬Ïß*/ {
			cv::line(image, cv::Point2d(poseKeypoints[i+3].x, poseKeypoints[i+3].y), cv::Point2d(poseKeypoints[i + 4].x, poseKeypoints[i + 4].y), cv::Scalar(0, 255, 255), 3, 8, 0);
		}
			//5-6
		if (!Pose2dIsEmpty(poseKeypoints[i+5]) && !Pose2dIsEmpty(poseKeypoints[i + 6]))/*µ±Á½¸öµã¶¼´æÔÚÊ±,»­³öÖ®¼äµÄÁ¬Ïß*/ {
			cv::line(image, cv::Point2d(poseKeypoints[i+5].x, poseKeypoints[i+5].y), cv::Point2d(poseKeypoints[i + 6].x, poseKeypoints[i + 6].y), cv::Scalar(0, 255, 255), 3, 8, 0);
		}
			//6-7
		if (!Pose2dIsEmpty(poseKeypoints[i+6]) && !Pose2dIsEmpty(poseKeypoints[i + 7]))/*µ±Á½¸öµã¶¼´æÔÚÊ±,»­³öÖ®¼äµÄÁ¬Ïß*/ {
			cv::line(image, cv::Point2d(poseKeypoints[i + 6].x, poseKeypoints[i + 6].y), cv::Point2d(poseKeypoints[i + 7].x, poseKeypoints[i + 7].y), cv::Scalar(0, 255, 255), 3, 8, 0);
		}
			//1-8
		if (!Pose2dIsEmpty(poseKeypoints[i+1]) && !Pose2dIsEmpty(poseKeypoints[i + 8]))/*µ±Á½¸öµã¶¼´æÔÚÊ±,»­³öÖ®¼äµÄÁ¬Ïß*/ {
			cv::line(image, cv::Point2d(poseKeypoints[i + 1].x, poseKeypoints[i + 1].y), cv::Point2d(poseKeypoints[i + 8].x, poseKeypoints[i + 8].y), cv::Scalar(0, 255, 255), 3, 8, 0);
		}
			//10-11
		if (!Pose2dIsEmpty(poseKeypoints[i + 10]) && !Pose2dIsEmpty(poseKeypoints[i + 11]))/*µ±Á½¸öµã¶¼´æÔÚÊ±,»­³öÖ®¼äµÄÁ¬Ïß*/ {
			cv::line(image, cv::Point2d(poseKeypoints[i + 10].x, poseKeypoints[i + 10].y), cv::Point2d(poseKeypoints[i + 11].x, poseKeypoints[i + 11].y), cv::Scalar(0, 255, 255), 3, 8, 0);
		}
			//8-9
		if (!Pose2dIsEmpty(poseKeypoints[i+8]) && !Pose2dIsEmpty(poseKeypoints[i + 9]))/*µ±Á½¸öµã¶¼´æÔÚÊ±,»­³öÖ®¼äµÄÁ¬Ïß*/ {
			cv::line(image, cv::Point2d(poseKeypoints[i + 8].x, poseKeypoints[i + 8].y), cv::Point2d(poseKeypoints[i + 9].x, poseKeypoints[i + 9].y), cv::Scalar(0, 255, 255), 3, 8, 0);
		}
		//8-12
		if (!Pose2dIsEmpty(poseKeypoints[i + 8]) && !Pose2dIsEmpty(poseKeypoints[i + 12]))/*µ±Á½¸öµã¶¼´æÔÚÊ±,»­³öÖ®¼äµÄÁ¬Ïß*/ {
			cv::line(image, cv::Point2d(poseKeypoints[i + 8].x, poseKeypoints[i + 8].y), cv::Point2d(poseKeypoints[i + 12].x, poseKeypoints[i + 12].y), cv::Scalar(0, 255, 255), 3, 8, 0);
		}
			//9-10
		if (!Pose2dIsEmpty(poseKeypoints[i+9]) && !Pose2dIsEmpty(poseKeypoints[i + 10]))/*µ±Á½¸öµã¶¼´æÔÚÊ±,»­³öÖ®¼äµÄÁ¬Ïß*/ {
			cv::line(image, cv::Point2d(poseKeypoints[i + 9].x, poseKeypoints[i + 9].y), cv::Point2d(poseKeypoints[i + 10].x, poseKeypoints[i + 10].y), cv::Scalar(0, 255, 255), 3, 8, 0);
		}
			//12-13
		if (!Pose2dIsEmpty(poseKeypoints[i+12]) && !Pose2dIsEmpty(poseKeypoints[i + 13]))/*µ±Á½¸öµã¶¼´æÔÚÊ±,»­³öÖ®¼äµÄÁ¬Ïß*/ {
			cv::line(image, cv::Point2d(poseKeypoints[i + 12].x, poseKeypoints[i + 12].y), cv::Point2d(poseKeypoints[i + 13].x, poseKeypoints[i + 13].y), cv::Scalar(0, 255, 255), 3, 8, 0);
		}

	    //×ó½Å
		//14-21
		if (!Pose2dIsEmpty(poseKeypoints[i + 14]) && !Pose2dIsEmpty(poseKeypoints[i + 21]))/*µ±Á½¸öµã¶¼´æÔÚÊ±,»­³öÖ®¼äµÄÁ¬Ïß*/ {
			cv::line(image, cv::Point2d(poseKeypoints[i + 14].x, poseKeypoints[i + 14].y), cv::Point2d(poseKeypoints[i + 21].x, poseKeypoints[i + 21].y), cv::Scalar(0, 255, 255), 3, 8, 0);
		}
		//21-19
		if (!Pose2dIsEmpty(poseKeypoints[i + 19]) && !Pose2dIsEmpty(poseKeypoints[i + 21]))/*µ±Á½¸öµã¶¼´æÔÚÊ±,»­³öÖ®¼äµÄÁ¬Ïß*/ {
			cv::line(image, cv::Point2d(poseKeypoints[i + 19].x, poseKeypoints[i + 19].y), cv::Point2d(poseKeypoints[i + 21].x, poseKeypoints[i + 21].y), cv::Scalar(0, 255, 255), 3, 8, 0);
		}
		//19-20
		if (!Pose2dIsEmpty(poseKeypoints[i + 19]) && !Pose2dIsEmpty(poseKeypoints[i + 20]))/*µ±Á½¸öµã¶¼´æÔÚÊ±,»­³öÖ®¼äµÄÁ¬Ïß*/ {
			cv::line(image, cv::Point2d(poseKeypoints[i + 19].x, poseKeypoints[i + 19].y), cv::Point2d(poseKeypoints[i + 20].x, poseKeypoints[i + 20].y), cv::Scalar(0, 255, 255), 3, 8, 0);
		}
		//20-14
		if (!Pose2dIsEmpty(poseKeypoints[i + 14]) && !Pose2dIsEmpty(poseKeypoints[i + 20]))/*µ±Á½¸öµã¶¼´æÔÚÊ±,»­³öÖ®¼äµÄÁ¬Ïß*/ {
			cv::line(image, cv::Point2d(poseKeypoints[i + 14].x, poseKeypoints[i + 14].y), cv::Point2d(poseKeypoints[i + 20].x, poseKeypoints[i + 20].y), cv::Scalar(0, 255, 255), 3, 8, 0);
		}
		//ÓÒ½Å
		//11-23
		if (!Pose2dIsEmpty(poseKeypoints[i + 11]) && !Pose2dIsEmpty(poseKeypoints[i + 23]))/*µ±Á½¸öµã¶¼´æÔÚÊ±,»­³öÖ®¼äµÄÁ¬Ïß*/ {
			cv::line(image, cv::Point2d(poseKeypoints[i + 11].x, poseKeypoints[i + 11].y), cv::Point2d(poseKeypoints[i + 23].x, poseKeypoints[i + 23].y), cv::Scalar(0, 255, 255), 3, 8, 0);
		}
		//23-22
		if (!Pose2dIsEmpty(poseKeypoints[i + 22]) && !Pose2dIsEmpty(poseKeypoints[i + 23]))/*µ±Á½¸öµã¶¼´æÔÚÊ±,»­³öÖ®¼äµÄÁ¬Ïß*/ {
			cv::line(image, cv::Point2d(poseKeypoints[i + 22].x, poseKeypoints[i + 22].y), cv::Point2d(poseKeypoints[i + 23].x, poseKeypoints[i + 23].y), cv::Scalar(0, 255, 255), 3, 8, 0);
		}
		//22-24
		if (!Pose2dIsEmpty(poseKeypoints[i + 22]) && !Pose2dIsEmpty(poseKeypoints[i + 24]))/*µ±Á½¸öµã¶¼´æÔÚÊ±,»­³öÖ®¼äµÄÁ¬Ïß*/ {
			cv::line(image, cv::Point2d(poseKeypoints[i + 22].x, poseKeypoints[i + 22].y), cv::Point2d(poseKeypoints[i + 24].x, poseKeypoints[i + 24].y), cv::Scalar(0, 255, 255), 3, 8, 0);
		}
		//24-11
		if (!Pose2dIsEmpty(poseKeypoints[i + 11]) && !Pose2dIsEmpty(poseKeypoints[i + 24]))/*µ±Á½¸öµã¶¼´æÔÚÊ±,»­³öÖ®¼äµÄÁ¬Ïß*/ {
			cv::line(image, cv::Point2d(poseKeypoints[i + 11].x, poseKeypoints[i + 11].y), cv::Point2d(poseKeypoints[i + 24].x, poseKeypoints[i + 24].y), cv::Scalar(0, 255, 255), 3, 8, 0);
		}
	}
	ShowPointIndexInImage(image, poseKeypoints);
}

bool PoseDete::Pose2dIsEmpty(Pose2d poseKeypoint)
{
	if (poseKeypoint.x == 0 && poseKeypoint.y == 0)
		return true;
	else
		return false;
	
}
void PoseDete::GetFaceScope(int& zuobiao4_id, std::vector<Pose2d>& poseKeypoints, std::vector<float> &facescope,cv::Mat  test_image)
{
	
	if (!Pose2dIsEmpty(poseKeypoints[zuobiao4_id + 13]) && !Pose2dIsEmpty(poseKeypoints[zuobiao4_id - 3]) && !Pose2dIsEmpty(poseKeypoints[zuobiao4_id + 14]))
	{
		
		facescope.push_back(poseKeypoints[zuobiao4_id + 13].x);//leftup.x
		facescope.push_back(2 * poseKeypoints[zuobiao4_id + 13].y - poseKeypoints[zuobiao4_id - 3].y);//leftup.y
		facescope.push_back(poseKeypoints[zuobiao4_id + 14].x);//rightdown.x
		facescope.push_back(poseKeypoints[zuobiao4_id - 3].y);//rightdown.y
        //testing draw face scope
		cv::rectangle(test_image, cv::Point2f(facescope[0], facescope[1]), cv::Point2f(facescope[2], facescope[3]), cv::Scalar(255, 0, 0), 1, 1, 0);
		SetElbow4PointScope(cv::Point2f(10,10), cv::Point2f(200, 300));
		////show
		/*int index = 0;
		for each (auto& var in facescope)
		{
			std::cout <<"index :"<<index<< "facescope"<<var << std::endl;
			index = index + 1;
		}*/
		std::cout << "in scope" << std::endl;
		return;
	}
	else
	{
		std::cout << "incomplete coordinate" << std::endl;
		return;
	}
}
int PoseDete::PanDuanTaiShou(cv::Mat & image,std::vector<Pose2d>& poseKeypoints)//ÅÐ¶Ï4ºÅµãÎ»ÓÚÄ³¸öÇøÓò ·µ»Ø4ºÅµãÏÂ±ê
{
	
	//testing start »­³öÖ¸¶¨ÇøÓò
	cv::rectangle(image, temp.leftup,temp.rightdown, cv::Scalar(255, 0, 0), 1, 1, 0);
	//testing end
	for (size_t i = 4; i < poseKeypoints.size(); i = i + 25)//±éÀúÍ¼ÏñÖÐËùÓÐµÄÈË
	{
		if (!Pose2dIsEmpty(poseKeypoints[i]))//4ºÅµã´æÔÚ
		{
			if (InScope(poseKeypoints[i]))//ÅÐ¶Ï4ºÅµãÎ»ÓÚÖ¸¶¨ÇøÓò
			{
				return int(i);//4ºÅµãÎ»ÓÚÖ¸¶¨ÇøÓò
			}
		}
		else if ((25 + i) > poseKeypoints.size())
		{
			return -1;//Ñ°±éÊý×é£¬ËùÓÐÈË¶¼Ã»Ì§ÊÖ
		}
	}
}
/*½«datumsPtrÖÐµÄµã×ª´æµ½poseKeypoints*/
void PoseDete::TransKeypoints(const std::shared_ptr<std::vector<std::shared_ptr<op::Datum>>>& datumsPtr, std::vector<Pose2d>& poseKeypoints)
{
	try
	{
		if (datumsPtr != nullptr && !datumsPtr->empty()) {
			std::vector<float> pointsResult;
			struct Pose2d pose2d;

			for (auto i = 0u; i < datumsPtr->at(0)->poseKeypoints.getVolume(); i++) {
				pointsResult.push_back(datumsPtr->at(0)->poseKeypoints[i]);
			}
			for (size_t i = 0; i < pointsResult.size(); i += 3) {
				pose2d.x = pointsResult[i];
				pose2d.y = pointsResult[i + 1];
				pose2d.score = pointsResult[i + 2];
				poseKeypoints.push_back(pose2d);
			}
			/*Êä³ö×ø±êµãÏà¹ØÐÅÏ¢*/
			/*testing*/
			//std::cout <<"mVolume="<< datumsPtr->at(0)->poseKeypoints.getVolume() << std::endl;
			//std::cout << "NumberDimensions=" << datumsPtr->at(0)->poseKeypoints.getNumberDimensions()<< std::endl;
			//std::cout << "DatumID:" << datumsPtr->at(0)->id << std::endl;//³ÌÐòÔËÐÐÆÚ¼äÒ»Ö±µÝÔö ¿ÉÒÔÀí½âÎªÖ¡Êý£¨Ã¿Ö¡¶ÔÓ¦Ò»¸öDatum£©
			//std::cout << "DatumsubId:" << datumsPtr->at(0)->subId << std::endl;
			//std::cout << "DatumsubIdMax:" << datumsPtr->at(0)->subIdMax << std::endl;
			//cv::imshow("Datum storage 3dMat output:", datumsPtr->at(0)->cvInputData);//´æ´¢ÊäÈëÍ¼ÏñµÄMat
			//cv::imshow("Datum storage Mat output:", datumsPtr->at(0)->cvOutputData);//´æ´¢´øÓÐ¹Ç÷ÀÁ¬ÏßµÄMat
			//panduantaishou(datumsPtr->at(0)->cvInputData, poseKeypoints);
		}
		else
			op::log("Nullptr or empty datumsPtr found.", op::Priority::High);
	}
	catch (const std::exception& e)
	{
		//std::error(e.what(), __LINE__, __FUNCTION__, __FILE__);
		return;
	}
}

void PoseDete::configureWrapper(op::Wrapper& opWrapper)
{
	try
	{
		// Configuring OpenPose

		// logging_level
	
		op::check(0 <=  FLAGS_logging_level &&  FLAGS_logging_level <= 255, "Wrong logging_level value.",
			__LINE__, __FUNCTION__, __FILE__);
		op::ConfigureLog::setPriorityThreshold((op::Priority)FLAGS_logging_level);
		op::Profiler::setDefaultX(FLAGS_profile_speed);

		// Applying user defined configuration - GFlags to program variables
		// outputSize
		const auto outputSize = op::flagsToPoint(FLAGS_output_resolution, "-1x-1");
		// netInputSize
		const auto netInputSize = op::flagsToPoint(FLAGS_net_resolution, "-1x368");
		// faceNetInputSize
		const auto faceNetInputSize = op::flagsToPoint(FLAGS_face_net_resolution, "368x368 (multiples of 16)");
		// handNetInputSize
		const auto handNetInputSize = op::flagsToPoint(FLAGS_hand_net_resolution, "368x368 (multiples of 16)");
		// poseMode
		const auto poseMode = op::flagsToPoseMode(FLAGS_body);
		// poseModel
		const auto poseModel = op::flagsToPoseModel(FLAGS_model_pose);
		// JSON saving
		if (!FLAGS_write_keypoint.empty())
			op::log("Flag `write_keypoint` is deprecated and will eventually be removed."
				" Please, use `write_json` instead.", op::Priority::Max);
		// keypointScaleMode
		const auto keypointScaleMode = op::flagsToScaleMode(FLAGS_keypoint_scale);
		// heatmaps to add
		const auto heatMapTypes = op::flagsToHeatMaps(FLAGS_heatmaps_add_parts, FLAGS_heatmaps_add_bkg,
			FLAGS_heatmaps_add_PAFs);
		const auto heatMapScaleMode = op::flagsToHeatMapScaleMode(FLAGS_heatmaps_scale);
		// >1 camera view?
		const auto multipleView = (FLAGS_3d || FLAGS_3d_views > 1);
		// Face and hand detectors
		const auto faceDetector = op::flagsToDetector(FLAGS_face_detector);
		const auto handDetector = op::flagsToDetector(FLAGS_hand_detector);
		// Enabling Google Logging
		const bool enableGoogleLogging = true;

		// Pose configuration (use WrapperStructPose{} for default and recommended configuration)
		const op::WrapperStructPose wrapperStructPose{
			poseMode, netInputSize, outputSize, keypointScaleMode, FLAGS_num_gpu, FLAGS_num_gpu_start,
			FLAGS_scale_number, (float)FLAGS_scale_gap, op::flagsToRenderMode(FLAGS_render_pose, multipleView),
			poseModel, !FLAGS_disable_blending, (float)FLAGS_alpha_pose, (float)FLAGS_alpha_heatmap,
			FLAGS_part_to_show, FLAGS_model_folder, heatMapTypes, heatMapScaleMode, FLAGS_part_candidates,
			(float)FLAGS_render_threshold, FLAGS_number_people_max, FLAGS_maximize_positives, FLAGS_fps_max,
			FLAGS_prototxt_path, FLAGS_caffemodel_path, (float)FLAGS_upsampling_ratio, enableGoogleLogging };
		opWrapper.configure(wrapperStructPose);
		// Face configuration (use op::WrapperStructFace{} to disable it)
		const op::WrapperStructFace wrapperStructFace{
			FLAGS_face, faceDetector, faceNetInputSize,
			op::flagsToRenderMode(FLAGS_face_render, multipleView, FLAGS_render_pose),
			(float)FLAGS_face_alpha_pose, (float)FLAGS_face_alpha_heatmap, (float)FLAGS_face_render_threshold };
		opWrapper.configure(wrapperStructFace);
		// Hand configuration (use op::WrapperStructHand{} to disable it)
		const op::WrapperStructHand wrapperStructHand{
			FLAGS_hand, handDetector, handNetInputSize, FLAGS_hand_scale_number, (float)FLAGS_hand_scale_range,
			op::flagsToRenderMode(FLAGS_hand_render, multipleView, FLAGS_render_pose), (float)FLAGS_hand_alpha_pose,
			(float)FLAGS_hand_alpha_heatmap, (float)FLAGS_hand_render_threshold };
		opWrapper.configure(wrapperStructHand);
		// Extra functionality configuration (use op::WrapperStructExtra{} to disable it)
		const op::WrapperStructExtra wrapperStructExtra{
			FLAGS_3d, FLAGS_3d_min_views, FLAGS_identification, FLAGS_tracking, FLAGS_ik_threads };
		opWrapper.configure(wrapperStructExtra);
		// Output (comment or use default argument to disable any output)
		const op::WrapperStructOutput wrapperStructOutput{
			FLAGS_cli_verbose, FLAGS_write_keypoint, op::stringToDataFormat(FLAGS_write_keypoint_format),
			FLAGS_write_json, FLAGS_write_coco_json, FLAGS_write_coco_json_variants, FLAGS_write_coco_json_variant,
			FLAGS_write_images, FLAGS_write_images_format, FLAGS_write_video, FLAGS_write_video_fps,
			FLAGS_write_video_with_audio, FLAGS_write_heatmaps, FLAGS_write_heatmaps_format, FLAGS_write_video_3d,
			FLAGS_write_video_adam, FLAGS_write_bvh, FLAGS_udp_host, FLAGS_udp_port };
		opWrapper.configure(wrapperStructOutput);
		// No GUI. Equivalent to: opWrapper.configure(op::WrapperStructGui{});
		// Set to single-thread (for sequential processing and/or debugging and/or reducing latency)
		if (FLAGS_disable_multi_thread)
			opWrapper.disableMultiThreading();
	}
	catch (const std::exception& e)
	{
		op::error(e.what(), __LINE__, __FUNCTION__, __FILE__);
	}
}

void PoseDete::ShowPointIndexInImage(cv::Mat & image, std::vector<Pose2d>& poseKeypoints)
{
	for (size_t i = 0; i < poseKeypoints.size(); ++i) {
		//if point not empty ,show screen
		if (!Pose2dIsEmpty(poseKeypoints[i]))
		{
			cv::putText(image, std::to_string(i % 25) + ":(" + std::to_string(poseKeypoints[i].x) + "," + std::to_string(poseKeypoints[i].y) + ")", cv::Point2f(poseKeypoints[i].x, poseKeypoints[i].y), cv::FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 255));
		}

	}
}

void PoseDete::DetecImage(std::string imagepath)
{
	std::vector<Pose2d> poseRes;

	cv::Mat imageToProcess = cv::imread(imagepath);
	
	if (!imageToProcess.empty())
	{
		auto datumProcessed = opWrapper.emplaceAndPop(imageToProcess);
		if (datumProcessed != nullptr)
		{
			TransKeypoints(datumProcessed, poseRes);
			DrawPoint(imageToProcess, poseRes);

			cv::imshow("test", imageToProcess); 
			cv::waitKey(3300000);
			poseRes.clear();
		}

	}
	
}

void PoseDete::DetecImages(std::string imagepath)
{
	// Read frames on directory
	const auto imagePaths = op::getFilesOnDirectory(imagepath, op::Extensions::Images);

	std::vector<Pose2d> poseRes;

	// Process and display images
	for (const auto& imagePath : imagePaths)
	{
		auto imageToProcess = cv::imread(imagePath);
		auto datumProcessed = opWrapper.emplaceAndPop(imageToProcess);
		if (datumProcessed != nullptr)
		{
			TransKeypoints(datumProcessed, poseRes);
			DrawPoint(imageToProcess, poseRes);

			cv::imshow("test", imageToProcess);
			cv::waitKey(33);
			poseRes.clear();
		}
		else
			op::log("Image could not be processed.", op::Priority::High);
	}

}

void PoseDete::DetecVedio(std::string vediopath)
{
	cv::VideoCapture cap;
    cap.open(vediopath); //´ò¿ªÊÓÆµ,ÒÔÉÏÁ½¾äµÈ¼ÛÓÚVideoCapture cap("E://2.avi");

	if (!cap.isOpened()) {
		return;
	}
	cv::Mat frame;
	std::vector<Pose2d> poseRes;

	while (cap.isOpened()) {
		cap >> frame;
		if (!frame.empty())
		{
			DetePose(frame, poseRes);
			DrawPoint(frame, poseRes);

			cv::imshow("test", frame);
			cv::waitKey(33);
			poseRes.clear();
		}
	}
}

void PoseDete::DetecRealTimeCamera()
{
	cv::VideoCapture cap(0);
	if (!cap.isOpened()) {
		return;
	}
	cv::Mat frame;
	std::vector<Pose2d> poseRes;

	while (cap.isOpened()) {
		cap >> frame;
		DetePose(frame, poseRes);
		DrawPoint(frame, poseRes);

		cv::imshow("test", frame);
		cv::waitKey(33);
		poseRes.clear();
	}
}

void PoseDete::SetElbow4PointScope(cv::Point2f leftup, cv::Point2f rightdown)
{
	temp.leftup = leftup;
	temp.rightdown = rightdown;
}

int PoseDete::DetePose(cv::Mat& frame, std::vector<Pose2d>& poseKeypoints) {
	try
	{
		auto datumProcessed = opWrapper.emplaceAndPop(frame);
		if (datumProcessed != nullptr)
		{
			TransKeypoints(datumProcessed, poseKeypoints);
		}
		else
			op::log("Image could not be processed.", op::Priority::High);
		return 0;
	}
	catch (const std::exception& e)
	{
		return -1;
	}
}

void PoseDete::ShowZuoBiao(std::vector<Pose2d> poseKeypoints)
{
	int index = 0;
	/*for each (auto& var in poseKeypoints)
	{
		std::cout <<"index:"<<index <<"x = "<<var.x << ";y = "<<var.y << std::endl;
		index = index + 1;
	}*/
}

bool PoseDete::InScope(Pose2d Point)
{
	if ((Point.x >= temp.leftup.x && Point.x <= temp.rightdown.x) && (Point.y >= temp.leftup.y && Point.y <= temp.rightdown.y))
	{
		return true;
	}
	else
		return false;
	
}
