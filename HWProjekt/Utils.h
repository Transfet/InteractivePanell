#pragma once
#include <random>
#include "point.h"
#include "line.h"
class Utils
{
public:

	static double randomGenerator(double min, double max);
	static Point mirroring(Point, Point);
	static Line calculateNormalVector(Line,Point);


};