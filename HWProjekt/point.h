#pragma once
#include <GL/glut.h>

typedef struct Point4D { double x, y, z, h; }POINT4D;
typedef struct Point3D { double x, y, z; }POINT3D;

class Point
{
public:
	Point();
	Point(double, double);
	Point(double, double, double);
	Point(double, double, double, double);
	friend Point operator-(const Point&, const Point&);
	friend Point operator+(const Point&, const Point&);
	friend Point operator*(const Point&, const Point&);

	friend Point operator*(const Point&, double);
	friend Point operator/(const Point&, double);
	Point& operator=(const int);

	double getX();
	double getY();
	double getZ();
	double getH();

	void setX(double);
	void setY(double);
	void setZ(double);
	void setH(double);
	double x, y, z, h;

private:

	//double x, y, z, h;

};