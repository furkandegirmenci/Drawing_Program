#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

void mousePoints(int,int,int,int,void*);
void callBackFunc(int,int,int,int,void*);
int mouseX, mouseY, clearFlag, clickFlag;


void mousePoints(int event, int x, int y, int flags, void* param)
{
    if (event == EVENT_LBUTTONDOWN)
    {
    	clickFlag = 1;
    }
    if(clickFlag == 1)
    {
    	mouseX = x;
    	mouseY = y;
    }
    if(event == EVENT_LBUTTONUP)
    {
    	clickFlag = 0;
    }
}
void callBackFunc(int event, int x, int y, int flags, void* param)
{
	if(event == EVENT_LBUTTONDOWN)
	{
		clearFlag = 1;
	}
}

int main()
{
	namedWindow("img", 0);
	namedWindow("buttons", 0);
	namedWindow("Click to Clean", 0);
	Mat img(480, 640, CV_8UC3, Scalar(255, 255, 255));
	Mat imgCopy;
	img.copyTo(imgCopy);
	putText(imgCopy, "Press 'q' to exit", Point(10, 50), FONT_HERSHEY_COMPLEX_SMALL, 1, Scalar(0,0,0), 1);
	putText(img, "Press 'q' to exit", Point(10, 50), FONT_HERSHEY_COMPLEX_SMALL, 1, Scalar(0,0,0), 1);
	int key{0};
	int rVal{0}, gVal{0}, bVal{0}, size{2};
	createTrackbar("red", "buttons", &rVal, 255);
	createTrackbar("green", "buttons", &gVal, 255);
	createTrackbar("blue", "buttons", &bVal, 255);
	createTrackbar("size", "buttons", &size, 15);
	setMouseCallback("img", mousePoints, NULL);
	setMouseCallback("Click to Clean", callBackFunc, NULL);
	while(key != 'q')
	{
		if(clearFlag == 1)
		{
			img.copyTo(imgCopy);
		}
		else if(clickFlag == 1) {
			circle(imgCopy, Point(mouseX, mouseY), size, Scalar(bVal, gVal, rVal), FILLED);
		}
		clearFlag = 0;
		imshow("img", imgCopy);
		key = waitKey(1);
	}
  	return 0;
}
