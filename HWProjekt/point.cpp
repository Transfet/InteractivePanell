#include "point.h"

Point::Point()
{
	double x, y;
}

Point::Point(double x0, double y0)
{
	x = x0;
	y = y0;
	z = 0;
}

Point::Point(double x0, double y0, double z0) : x(x0), y(y0), z(z0)
{
}

Point::Point(double x0, double y0, double z0, double h0) : x(x0), y(y0), z(z0), h(h0)
{
}

Point & Point::operator=(const int value)
{
	Point p;
	p.x = value;
	p.y = value;
	p.z = value;

	return p;
}


Point operator-(const Point&a, const Point&b)
{

	Point p;
	p.x = a.x - b.x;
	p.y = a.y - b.y;
	p.z = a.z - b.z;

	return p;
}

Point operator+(const Point&a, const Point&b)
{
	Point p;
	p.x = a.x + b.x;
	p.y = a.y + b.y;
	p.z = a.z + b.z;

	return p;
}

Point operator*(const Point &p1, const Point &p2)
{
	Point res;

	res.x = p1.x*p2.x;
	res.y = p1.y*p2.y;

	return res;

}

Point operator*(const Point&a, double i)
{
	Point p;
	p.x = a.x*i;
	p.y = a.y*i;
	p.z = a.z*i;

	return p;
}

Point operator/(const Point&a, double n)
{
	Point p;
	p.x = a.x / n;
	p.y = a.y / n;
	p.z = a.z / n;

	return p;
}

double Point::getX() {
	return x;
}

double Point::getY() {
	return y;
}

double Point::getZ() {
	return z;
}

double Point::getH() {
	return h;
}

void Point::setX(double x) {
	this->x = x;
}

void Point::setY(double y) {
	this->y = y;
}

void Point::setZ(double z) {
	this->z = z;
}

void Point::setH(double h) {
	this->h = h;
}