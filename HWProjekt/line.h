#pragma once

#include "point.h"
#include <iostream>

class Line
{
public:
	Line(Point , Point);
	void  setColor(double r, double g, double b);
	void  setWidth(float w);
	void setColor(std::string);
	float  getLineWidth();
	double  getRed();
	double  getBlue();
	double  getGreen();
	std::string getColor();


	Point a, b;
private:
	std::string color;
	float lineWidth;
	double red, green, blue;

};