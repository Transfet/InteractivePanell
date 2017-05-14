#pragma once
#include "point.h"
#include "Utils.h"
class Circle
{
public:
	Circle();
	Circle(Point, double);
	void setColor(double, double, double);
	void blink();
	void setOrigo(Point);
	void setRadius(double);
	double getRadius();
	double getRed();
	double getBlue();
	double getGreen();

	Point getOrigo();
	float getVelocityX();
	float getVelocityY();
	void setVelocityX(float);
	void setVelocityY(float);

private:

	Point origo;
	float velocityX;
	float velocityY;
	double radius, red, green, blue;
	
};