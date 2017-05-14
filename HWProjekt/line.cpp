#include "line.h"

Line::Line(Point a, Point b)
{
	this->a.setX(a.getX());
	this->a.setY(a.getY());
	this->b.setX(b.getX());
	this->b.setY(b.getY());
}

std::string Line::getColor() {
	return color;
}

void Line::setColor(std::string col) {
	color = col;
}

void Line::setColor(double r, double g, double b)
{
	red = r;
	green = g;
	blue = b;
}

void Line::setWidth(float w)
{
	lineWidth = w;
}

float Line::getLineWidth()
{
	return lineWidth;
}

double Line::getRed()
{
	return red;
}

double Line::getBlue()
{
	return blue;
}

double Line::getGreen()
{

	return green;
}