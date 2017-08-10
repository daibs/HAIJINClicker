#ifndef __TARGE_TDETECTOR
#define __TARGET_DETECTOR

#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>
#include <sstream>

//using namespace cv;
using namespace std;
template <typename T> std::string tostr(const T& t)
{
    std::ostringstream os; os<<t; return os.str();
}

class targetDetector{
private:
	cv:: Mat img;
	cv::Mat gamewindow[4];
	cv::Mat target[4];
	//Mat targetb;
	cv::Point gamepos;
	cv::Point targetpos;
	double gameposvalue;
	double targetposvalue;
	int mode_basis;
public:
	targetDetector(void);
	bool gameDetect(cv::Mat);
	bool targetDetect(cv::Mat);
	cv::Point getTargetPos(void);
	cv::Point getTargetCenter(void);
	void showimg(void);
	void showimg_notclose(void);
	void showimg_running(void);
	cv::Mat getimg(void);
	double gettargetvalue(void);

};


#endif