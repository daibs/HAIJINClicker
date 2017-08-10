#include "targetdetector.h"

targetDetector::targetDetector(void){
	gamepos = cv::Point(0,0);
	targetpos = cv::Point(0,0);
	mode_basis = 0;
	try{
		gamewindow[0] = cv::imread("shoot_menu1.png",1);
		gamewindow[1] = cv::imread("shoot_menu2.png",1);
		gamewindow[2] = cv::imread("shoot_menu1_small.png");
		gamewindow[3] = cv::imread("shoot_menu2_small.png");
		target[0]		  = cv::imread("shoot_target.png",1);
		target[1]		  = cv::imread("shoot_target_blue.png",1);
		target[2]		  = cv::imread("shoot_target_small.png", 1);
		target[3]		  = cv::imread("shoot_target_blue_small.png", 1);
	}catch(cv::Exception& e){
		cout << e.what() << endl;
		terminate();
	}
	return;
}

bool targetDetector::gameDetect(cv::Mat src){
	cv::Mat tmp;
	double minval;
	double gameposvalue_tmp;
	cv::Point minp,gamepos_tmp;
	matchTemplate(src,gamewindow[1],tmp,CV_TM_CCORR_NORMED);
	minMaxLoc(tmp,&minval,&gameposvalue,&minp,&gamepos);
	matchTemplate(src, gamewindow[3], tmp, CV_TM_CCORR_NORMED);
	minMaxLoc(tmp, &minval, &gameposvalue_tmp, &minp, &gamepos_tmp);

	if (gameposvalue < gameposvalue_tmp) {
		mode_basis = 2;
		gamepos = gamepos_tmp;
	}
	cout << "gameposvalue:"<<gameposvalue << endl;
	cout << "gameposvalue_tmp:" << gameposvalue_tmp << endl;
	if(gameposvalue < 0.8)
		return false;

	return true;
}

bool targetDetector::targetDetect(cv::Mat src){
	img = src(cv::Rect(gamepos.x,gamepos.y,gamewindow[0 + mode_basis].cols,gamewindow[0 + mode_basis].rows));
	
	cv::Mat tmp;
	matchTemplate(img,target[0 + mode_basis],tmp,CV_TM_CCORR_NORMED);
	minMaxLoc(tmp,NULL,&targetposvalue,NULL,&targetpos);
	
	if(targetposvalue < 0.75){
		matchTemplate(img,target[1 + mode_basis],tmp,CV_TM_CCORR_NORMED);
		minMaxLoc(tmp,NULL,&targetposvalue,NULL,&targetpos);
	}
	cout << "targetposvalue:"<<targetposvalue << endl;
	if(targetposvalue < 0.5){
		return false;
	}
	rectangle(img,targetpos, cv::Point(targetpos.x+target[0 + mode_basis].cols,targetpos.y+target[0 + mode_basis].rows), cv::Scalar(255,255,0),2);
	targetpos = cv::Point(targetpos.x+gamepos.x,targetpos.y+gamepos.y);
	cout <<"targetpos:"<< targetpos << endl;
	return true;
}

cv::Point targetDetector::getTargetPos(void){
	return targetpos;
}

cv::Point targetDetector::getTargetCenter(void){
	return cv::Point(targetpos.x+target[0 + mode_basis].cols/2,targetpos.y+target[0 + mode_basis].rows/2);
}

void targetDetector::showimg(void){
	cv::imshow("img",img);
	cv::waitKey(0);
	cv::destroyAllWindows();
}

void targetDetector::showimg_notclose(void){
	cv::imshow("img",img);
	cv::waitKey(0);
}
void targetDetector::showimg_running(void){
	cv::imshow("img",img);
}

cv::Mat targetDetector::getimg(void){
	return img;
}

double targetDetector::gettargetvalue(void){
	return targetposvalue;
}
