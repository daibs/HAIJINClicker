#include "winmouse.h"

winmouse::winmouse(void){
	x=0;
	y=0;
}
void winmouse::setpos(int sx,int sy){
	x=sx;
	y=sy;
	SetCursorPos(x,y);
}
void winmouse::leftclick(void){
	//マウスの左ボタンを押す　右はMOUSEEVENTF_RIGHTDOWN　中央はMOUSEEVENTF_MIDDLEDOWN
	mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
	//マウスの左ボタンを離す
	mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
	return;
}

void winmouse::leftclick(int x,int y){
	setpos(x,y);
	winmouse::leftclick();
	return;
}

void winmouse::leftclick(cv::Point p){
	winmouse::leftclick(p.x,p.y);
	return;
}
