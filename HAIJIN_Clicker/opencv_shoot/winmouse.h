#ifndef __WINMOUSE
#define __WINMOUSE

#include <windows.h>
#include "opencv2/core/core.hpp"
class winmouse{
private:
	int x,y;
public:
	winmouse(void);
	void setpos(int,int);
	void leftclick(void);
	void leftclick(int,int);
	void leftclick(cv::Point);
};

#endif
