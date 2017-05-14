#pragma once
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
class ColorDetection {

public:
	ColorDetection();
	 void detection(cv::VideoCapture);
	 void createTask();
	 cv::Mat getGreenTresholded();
private:

	cv::Mat imgThresholded;
	cv::Mat imgOriginal;
	cv::Mat copy;

	int iLowH = 38;
	int iHighH = 75;

	int iLowS = 56;
	int iHighS = 228;

	int iLowV = 65;
	int iHighV = 255;

};
