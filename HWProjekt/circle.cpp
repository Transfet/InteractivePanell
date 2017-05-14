#include "circle.h"


Circle::Circle():radius(0),origo(Point(0,0)) {

}

Circle::Circle(Point p, double r):radius(r)
{
	origo.setX(p.getX());
	origo.setY(p.getY());

	velocityY = -1.1;
	velocityX = 0;

}

void Circle::setVelocityX(float x) {

	velocityX = x;

}

void Circle::setVelocityY(float y) {
	velocityY = y;
}

float Circle::getVelocityX() {
	return velocityX;
}

float Circle::getVelocityY() {
	return velocityY;
}
void Circle::setColor(double r, double g, double b)
{
	red = r;
	green = g;
	blue = b;
}

void Circle::setRadius(double r)
{

	radius = r;
}

double Circle::getRadius()
{
	return radius;
}

void Circle::blink()
{
		while (1)
		{
			double red = Utils::randomGenerator(0, 1);
			double green = Utils::randomGenerator(0, 1);
			double blue = Utils::randomGenerator(0, 1);

			setColor(red, green, blue);
		}
}

double Circle::getRed()
{
	return red;
}
double Circle::getBlue()
{
	return blue;
}
double Circle::getGreen()
{
	return green;
}

Point Circle::getOrigo() {
	return origo;
}

void Circle::setOrigo(Point o) {
	origo = o;
}