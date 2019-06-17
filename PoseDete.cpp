#include "PoseDete.h"
#include <openpose/flags.hpp>

PoseDete::PoseDete()
{
}


PoseDete::~PoseDete()
{
}

void PoseDete::Init() {
	op::log("Starting OpenPose demo...", op::Priority::High);
	// Configuring OpenPose
	op::log("Configuring OpenPose...", op::Priority::High);
	configureWrapper(opWrapper);

	// Starting OpenPose
	op::log("Starting thread(s)...", op::Priority::High);
	opWrapper.start();
}

int PoseDete::DetePose(cv::Mat &frame, std::vector<Pose2d>& poseKeypoints) {
	try
	{
		auto datumProcessed = opWrapper.emplaceAndPop(frame);
		if (datumProcessed != nullptr)
		{
			printKeypoints(datumProcessed, poseKeypoints);
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

void PoseDete::DrawPoint(cv::Mat & image, std::vector<Pose2d>& poseKeypoints) {
	for (size_t i = 0; i < poseKeypoints.size(); ++i) {
		circle(image, cv::Point2d(poseKeypoints[i].x, poseKeypoints[i].y), 3, cv::Scalar(255, 0, 0), -1);
	}
}

void PoseDete::printKeypoints(const std::shared_ptr<std::vector<std::shared_ptr<op::Datum>>>& datumsPtr, std::vector<Pose2d>& poseKeypoints)
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
		op::check(0 <= FLAGS_logging_level && FLAGS_logging_level <= 255, "Wrong logging_level value.",
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

void PoseDete::detec_images(string imagepath)
{
	// Read frames on directory
	const auto imagePaths = op::getFilesOnDirectory(imagepath, op::Extensions::Images);

	cv::Mat frame;
	std::vector<Pose2d> poseRes;

	// Process and display images
	for (const auto& imagePath : imagePaths)
	{
		auto imageToProcess = cv::imread(imagePath);
		auto datumProcessed = opWrapper.emplaceAndPop(imageToProcess);
		if (datumProcessed != nullptr)
		{
			printKeypoints(datumProcessed, poseRes);
			DrawPoint(imageToProcess, poseRes);

			cv::imshow("test", imageToProcess);
			cv::waitKey(33);
			poseRes.clear();
		}
		else
			op::log("Image could not be processed.", op::Priority::High);
	}

}

void PoseDete::detec_vedio(string vediopath)
{
	cv::VideoCapture cap;
    cap.open(vediopath); //打开视频,以上两句等价于VideoCapture cap("E://2.avi");

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

void PoseDete::detec_real_time_camera()
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

