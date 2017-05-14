#pragma once

#include "opencv2\core.hpp"
#include "opencv2\highgui.hpp"
#include "opencv2\imgproc.hpp"

#include "line.h"
#include "point.h"

namespace OpenCV
{
	class ColorDetection
	{
	public:
		ColorDetection();
		void Detection(cv::VideoCapture);
		std::vector<Line> GetLines();
		void createTask();

	private:
		std::vector<Line> Lines;
		cv::Mat imgHSV;
		cv::Mat imgTresholded;

		int iLowH = 38;
		int iHighH = 75;

		int iLowS = 56;
		int iHighS = 228;

		int iLowV = 65;
		int iHighV = 255;
	};
}

