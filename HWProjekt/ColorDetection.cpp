#include "ColorDetection.h"

using namespace OpenCV;

ColorDetection::ColorDetection()
{
}

void ColorDetection::createTask() {


	cv::namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"

												//Create trackbars in "Control" window
	cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
	cvCreateTrackbar("HighH", "Control", &iHighH, 255);

	cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
	cvCreateTrackbar("HighS", "Control", &iHighS, 250);

	cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
	cvCreateTrackbar("HighV", "Control", &iHighV, 255);

}

void ColorDetection::Detection(cv::VideoCapture capture)
{
	cv::Mat src;
	capture >> src;
	
	//cv::Mat src = cv::imread("C://Users//Transfet//Desktop//demo.png");
	cv::imshow("origin", src);
	/*cv::Mat src_gray;
	cv::cvtColor(src, src_gray, cv::COLOR_BGR2GRAY);

	cv::Mat src_thresh;
	cv::threshold(src_gray, src_thresh, 0, 255, cv::THRESH_TRIANGLE | cv::THRESH_BINARY_INV);
	cv::imshow("tresh", src_thresh);*/

	cv::cvtColor(src, imgHSV, cv::COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

	cv::inRange(imgHSV, cv::Scalar(iLowH, iLowS, iLowV), cv::Scalar(iHighH, iHighS, iHighV), imgTresholded); //Threshold the image

																								  //	cv::imshow("green",imgThresholded);
	cv::dilate(imgTresholded, imgTresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
	cv::dilate(imgTresholded, imgTresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));

	//morphological closing (fill small holes in the foreground)
	cv::dilate(imgTresholded, imgTresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
	cv::erode(imgTresholded, imgTresholded, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));

	cv::imshow("tresh", imgTresholded);


	cv::Mat dest;
	dest = cv::Mat::zeros(src.size(), CV_8UC1);

	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;

	cv::findContours(imgTresholded, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_NONE);

	for (int i = 0; i < contours.size(); i++)
	{
		std::vector<cv::Point> contour = contours[i];

		Line line(Point(contour[0].x, contour[0].y), Point(contour[0].x, contour[0].y));

		for (int j = 0; j < contour.size(); j++)
		{
			if (line.a.x > contour[j].x)
			{
				line.a = Point(contour[j].x, contour[j].y);
			}

			if (line.b.x < contour[j].x)
			{
				line.b = Point(contour[j].x, contour[j].y);
			}
		}

		Point a, b;
		if (line.a.getY() < line.b.getY()) {
			a = line.a;
			b = line.b;
		}
		else {
			a = line.b;
			b = line.a;
		}

		Line lines = Line(Point(a.x, a.y), Point(b.x, b.y));
		lines.setColor(0, 1, 0);
		Lines.push_back(lines);
	}

	cv::imshow("dest", dest);
}

std::vector<Line> ColorDetection::GetLines()
{
	return Lines;
}
