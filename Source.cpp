#include "PoseDete.h"

int main(int argc, char *argv[])
{
	PoseDete poseDete;
	poseDete.Init();
//	poseDete.detec_real_time_camera();
//	poseDete.detec_vedio("C:\\Users\\�ж������\\Desktop\\openpose\\examples\\media\\video.avi");
	poseDete.detec_images("C:\\Users\\�ж������\\Desktop\\openpose\\examples\\media");
	return 0;
}