#include "targetdetector.h"
#include "desktop_capture.h"
#include "winmouse.h"
#include "cv_keycode.h"
#include <fstream>
int main(int argc,char* argv[]){
	desktop_capture cap;
	targetDetector det;
	winmouse mouse;
	cap.capture();
	cv::Mat img = cap.getimg();
	cvtColor(img,img,CV_BGRA2BGR);
	det.gameDetect(img);
	det.targetDetect(img);
	det.showimg_notclose();
	int code = 0;
	cv::TickMeter t;
	t.start();
	cv::String filename = "shooting";
	cv::String extension = ".jpg";
	std::ofstream ofs("value.csv");
	while(1){
		cout <<det.getTargetCenter() << endl;
		mouse.leftclick(det.getTargetCenter());
		det.showimg_running();
		cv::waitKey(320);
		cap.capture();
		img = cap.getimg();
		cvtColor(img,img,CV_BGRA2BGR);
		det.targetDetect(img);
		t.stop();
		img = det.getimg();
		//cv::String f = filename + tostr(t.getTimeSec()) + extension;
		//imwrite(f,img);
		ofs << t.getTimeSec() << "," << det.gettargetvalue() << endl;
		if(t.getTimeSec() > 31.0)
			break;
		t.start();
	}
	ofs.close();
	return 0;

}
