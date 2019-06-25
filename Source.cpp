#include "PoseDete.h"

int main(int argc, char *argv[])
{
	PoseDete poseDete;
	poseDete.Init();
	poseDete.detec_real_time_camera();
//	poseDete.detec_vedio("C:\\Users\\有对象真好\\Desktop\\openpose\\examples\\media\\video.avi");
//	poseDete.detec_images("C:\\Users\\有对象真好\\Desktop\\openpose\\examples\\media");
//	poseDete.detec_image("C:\\Users\\有对象真好\\Desktop\\imagedir\\00002.jpg");
	return 0;
}