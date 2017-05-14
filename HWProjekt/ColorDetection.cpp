#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "ColorDetection.h"
using namespace cv;
using namespace std;

ColorDetection::ColorDetection(){}

void ColorDetection::createTask() {


	namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"

	//Create trackbars in "Control" window
	cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
	cvCreateTrackbar("HighH", "Control", &iHighH, 255);

	cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
	cvCreateTrackbar("HighS", "Control", &iHighS, 250);

	cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
	cvCreateTrackbar("HighV", "Control", &iHighV, 255);

}

cv::Mat ColorDetection::getGreenTresholded() {
	return imgThresholded;
}

void ColorDetection::detection(VideoCapture cap) {
	

		/*cap >> imgOriginal;
		imgOriginal.copyTo(copy);

		cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

		inRange(imgHSV, Scalar(iLowH, iLowS ,iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image

	//	cv::imshow("green",imgThresholded);
		dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		//morphological closing (fill small holes in the foreground)
		dilate(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

		imshow("Thresholded Image", imgThresholded); //show the thresholded image
		//imshow("Original", imgOriginal); //show the original image*/


	//Kamera feldolgozás


}











																							  //morphological opening (remove small objects from the foreground)




