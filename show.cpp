#include <stdio.h>  
#include <opencv/cv.h>  
#include <opencv/highgui.h>  
#include <fstream>
using namespace std;
using namespace cv;

int main()
{
	fstream file1;
	file1.open("C:\\Users\\wangquan\\Documents\\Visual Studio 2015\\Projects\\glut2\\glut2\\2.txt", ios::in);
	Mat img = Mat::zeros(500, 500, CV_32FC1);
	for (int i = 0; i < 500; i++) {
		for (int j = 0; j < 500; j++) {
			file1 >> img.at<float>(i, j);
		}
	}
	IplImage* img1 = &IplImage(img);
	cvNamedWindow("Input", CV_WINDOW_AUTOSIZE);
	cvShowImage("Input", img1);
	cvWaitKey(0);
	return 0;
}