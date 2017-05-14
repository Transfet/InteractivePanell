#include "Utils.h"

double Utils::randomGenerator(double min, double max) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(min, max);
	return dis(gen);
}

Point Utils::mirroring(Point hasToBeMirror, Point mirror)
{
	float t = (hasToBeMirror.x*mirror.x + hasToBeMirror.y*mirror.y) / (mirror.x*mirror.x + mirror.y*mirror.y);
	Point c = Point(mirror.x*t, mirror.y*t);
	Point ac = Point(c.x - hasToBeMirror.x, c.y - hasToBeMirror.y);
	Point mirrored = Point(hasToBeMirror.x + 2 * ac.x, hasToBeMirror.y + 2 * ac.y);
	return mirrored;
}

Line Utils::calculateNormalVector(Line line, Point o) {

	Point n;

		n.x = line.b.y - line.a.y;
		n.y = line.a.x - line.b.x;

	Point ON = o - n;
	Line normalVectorLine = Line(o, ON);

	return normalVectorLine;

}