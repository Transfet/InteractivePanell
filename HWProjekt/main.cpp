#define _USE_MATH_DEFINES
#include <cmath>
#include <GL/glut.h>
#include "line.h"
#include "circle.h"
#include <vector>
#include "Utils.h"
#include <iostream>
#include "ColorDetection.h"
#include <algorithm>
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

const int winWidth = 800;
const int winHeight = 600;
int blackPointsIndex = 0;
int greenPointsIndex = 0;
int blackPointsCounter = 0;
int greenPointsCounter = 0;

bool pushBlackLine = false;
bool pushGreenLine = false;

//határvonalak
Line rightSideLine = Line(Point(winWidth, 0), Point(winWidth, winHeight));
Line leftSideLine = Line(Point(0, 0), Point(0, winHeight));
Line topSideLine = Line(Point(0, winHeight), Point(winWidth, winHeight));
Line botSideLine = Line(Point(0, 0), Point(winWidth, 0));

//egy labda készítése
Circle ball;

std::vector<Line> lines;
std::vector<Point> points;
std::vector<Point> blackPoints;
std::vector<Point> basketPoints;

cv::VideoCapture cap;
cv::Mat original, copy;

ColorDetection colorDetection;

void createBasket() {

	float x = Utils::randomGenerator(1, winWidth - 100);
	float y = 100;
	Point p1 = Point(x, y);
	Point p2 = Point(p1.x, p1.y - 50);
	Point p3 = Point(p2.x + 100, p2.y);
	Point p4 = Point(p3.x, p1.y);

	basketPoints.push_back(p1);
	basketPoints.push_back(p2);
	basketPoints.push_back(p3);
	basketPoints.push_back(p4);

}

//Kamera adatok
void detect(int value) {
	colorDetection.detection(cap);



	glutTimerFunc(10, detect, 0);
	glutPostRedisplay();
}

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);		// Set display-window color to white
	glMatrixMode(GL_PROJECTION);			// Set projection parameters.
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	gluOrtho2D(0.0, winWidth, 0.0, winHeight);

	cap = cv::VideoCapture(1);
	//colorDetection.createTask();
	createBasket();
}

void drawCircle(Point p, double r)
{

	glColor3d(1.0, 0.0, 0.3);
	glBegin(GL_TRIANGLE_FAN);

	for (double i = 0; i <= 2 * M_PI; i += 0.01) {
		glVertex2d(p.x + r*cos(i), p.y + r*sin(i));
	}

	glEnd();

}

bool isPointOnLine(Point a, Line line)
{
	float t = (line.b.x - line.a.x) * (a.y - line.a.y) - (line.b.y - line.a.y) * (a.x - line.a.x);
	if (t > -1 && t < 1)
		return true;

	else
		return false;
}

void drawBakset() {

	glLineWidth(2.0);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	for (auto it = basketPoints.begin(); it != basketPoints.end(); it++) {
		glVertex2d(it->x, it->y);
	}
	glEnd();
}

Point vectorize(Point P1, Point P2)
{
	Point V;
	V.x = P2.x - P1.x;
	V.y = P2.y - P1.y;

	return V;
}

float distanceOfPointsFromLine(Line l, Point p)
{

	float abyDiff = l.a.y - l.b.y;
	float baxDiff = l.b.x - l.a.x;

	return fabs(((abyDiff)*l.a.x + (baxDiff)*l.a.y - (abyDiff)*p.x - (baxDiff)*p.y) / sqrt((abyDiff)*(abyDiff)+(baxDiff)*(baxDiff)));


	//return fabs((l.b.x-l.a.x)*(l.a.y - p.y) - (l.a.x- p.x)*(l.b.y-l.a.y) / sqrt(((l.b.x - l.a.x) * (l.b.x - l.a.x)) + ((l.a.y - l.b.y) * (l.a.y - l.b.y))));


}

Point twoLineIntersection(Line line1, Line line2) {

	Point intersection;

	float x1 = line1.b.x;
	float x2 = line1.a.x;
	float x3 = line2.b.x;
	float x4 = line2.a.x;

	float y1 = line1.b.y;
	float y2 = line1.a.y;
	float y3 = line2.b.y;
	float y4 = line2.a.y;

	float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

	float pre = (x1*y2 - y1*x2);
	float post = (x3*y4 - y3*x4);

	float x = (pre * (x3 - x4) - (x1 - x2) * post) / d;
	float y = (pre * (y3 - y4) - (y1 - y2) * post) / d;

	if (x < std::min(x1, x2) || x > std::max(x1, x2) ||
		x < std::min(x3, x4) || x > std::max(x3, x4)) return Point(0, 0);
	if (y < std::min(y1, y2) || y > std::max(y1, y2) ||
		y < std::min(y3, y4) || y > std::max(y3, y4)) return Point(0, 0);

	intersection.x = x;
	intersection.y = y;

	return intersection;

}

void drawLine() {

	for (int i = 0; i < lines.size(); i++) {

		double red = lines.at(i).getRed();
		double green = lines.at(i).getGreen();
		double blue = lines.at(i).getBlue();
		glLineWidth(6.0);
		glColor3d(red, green, blue);
		glBegin(GL_LINES);

		glVertex2d(lines.at(i).a.x, lines.at(i).a.y);
		glVertex2d(lines.at(i).b.x, lines.at(i).b.y);

		glEnd();
	}


}

double vectorLength(Point &V)
{
	return sqrt(V.x*V.x + V.y*V.y);
}

void doMirroring(Line &line) {

	if (distanceOfPointsFromLine(line, ball.getOrigo()) < ball.getRadius()) {

		Point v = Utils::mirroring(Point(ball.getVelocityX(), ball.getVelocityY()), vectorize(line.a, line.b));
		ball.setVelocityX(v.getX());
		ball.setVelocityY(v.getY());
	}
}

void isInsideBasket() {

	Line line1 = Line(basketPoints.at(0), basketPoints.at(1));
	Line line2 = Line(basketPoints.at(1), basketPoints.at(2));
	Line line3 = Line(basketPoints.at(2), basketPoints.at(3));
	
		Point o = ball.getOrigo();

		Line normalVectorLine1 = Utils::calculateNormalVector(line1,o);
		Line normalVectorLine2 = Utils::calculateNormalVector(line2, o);
		Line normalVectorLine3 = Utils::calculateNormalVector(line3,o);

		Point intersect1 = twoLineIntersection(normalVectorLine1, line1);
		Point intersect2 = twoLineIntersection(normalVectorLine2, line2);
		Point intersect3 = twoLineIntersection(normalVectorLine3, line3);

		glPointSize(4.0);
		glColor3d(1.0, 0.0, 0.0);
		glBegin(GL_POINTS);
		glVertex2d(intersect1.x, intersect1.y);
		glVertex2d(intersect2.x, intersect2.y);
		glVertex2d(intersect3.x, intersect3.y);
		glEnd();

		if (o.x > line1.a.x && o.x < line3.a.x && o.y > line2.a.y && o.y < line1.a.y - ball.getRadius()) {
			ball.setVelocityX(0);
			ball.setVelocityY(0);
		}

		if (distanceOfPointsFromLine(line2, o) < ball.getRadius())
		{
			if (isPointOnLine(intersect2, line2) && o.y < intersect2.y) {
				doMirroring(line2);
			}
		}
		if (distanceOfPointsFromLine(line1, o) < ball.getRadius()) {

			if (isPointOnLine(intersect1, line1) && o.x < intersect1.x) {
				doMirroring(line1);

			}
		}
		if (distanceOfPointsFromLine(line3, o) < ball.getRadius()) {


			if (isPointOnLine(intersect3, line3) && o.x > intersect3.x) {
				doMirroring(line3);
			}
		}
	
}

void move(int value) {

		doMirroring(rightSideLine);
		doMirroring(leftSideLine);
		doMirroring(topSideLine);
		doMirroring(botSideLine);
		isInsideBasket();

		if (lines.size() >= 1) {
			for (int j = 0; j < lines.size(); j++) {

				double red = lines.at(j).getRed();
				double green = lines.at(j).getGreen();
				double blue = lines.at(j).getBlue();

					if (distanceOfPointsFromLine(lines.at(j), ball.getOrigo()) < ball.getRadius())
				{
					Point O = ball.getOrigo();

					Point n;

					if (lines.at(j).a.x < lines.at(j).b.x) {
						n.x = lines.at(j).a.y - lines.at(j).b.y;
						n.y = lines.at(j).b.x - lines.at(j).a.x;
					}
					else {
						n.x = lines.at(j).b.y - lines.at(j).a.y;
						n.y = lines.at(j).a.x - lines.at(j).b.x;
					}

					Point ON = O - n;
					Line normalVectorLine = Line(O, ON);

					Point intersect = twoLineIntersection(normalVectorLine, lines.at(j));

					glPointSize(4.0);
					glColor3d(0.0, 0.0, 0.0);
					glBegin(GL_POINTS);
					glVertex2d(intersect.x, intersect.y);
					glEnd();

					if (isPointOnLine(intersect, lines.at(j))) {
						if (green == 1) {

								if (ball.getOrigo().y > lines.at(j).a.y) {

								//meredekség kiszámítása, ennyivel fog változni a kör középpontja a csúszáshoz
								Point p = lines.at(j).a - lines.at(j).b;
								p = p / 150;


								ball.setVelocityX(p.getX());
								ball.setVelocityY(p.getY());
							}
							else {
								Point v = Utils::mirroring(Point(ball.getVelocityX(), ball.getVelocityY()), vectorize(lines.at(j).a, lines.at(j).b));
								ball.setVelocityX(v.getX());
								ball.setVelocityY(v.getY());
							}
						}

						if (green == 0 && blue == 0 && red == 0) {

							Point v = Utils::mirroring(Point(ball.getVelocityX(), ball.getVelocityY()), vectorize(lines.at(j).a, lines.at(j).b));
							ball.setVelocityX(v.getX());
							ball.setVelocityY(v.getY());

						}
					}

				}

			}
		}

		Point origo = ball.getOrigo();

		float y = ball.getVelocityY();
		float x = ball.getVelocityX();

		if (y < 0) {
			y -= 0.007;
			ball.setVelocityY(y);
		}
		else if (y > 0) {
			y -= 0.009;
			ball.setVelocityY(y);
		}

		if (x > 0) {
			x -= 0.001;
			ball.setVelocityX(x);
		}
		else if (x < 0) {
			x += 0.001;
			ball.setVelocityX(x);
		}

		origo.x += ball.getVelocityX();
		origo.y += ball.getVelocityY();
		ball.setOrigo(origo);

		glutTimerFunc(3, move, 0);
		glutPostRedisplay();
	
}

void controlMouse(int button, int state, int xMouse, int yMouse)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		Circle circle = Circle(Point(xMouse, winHeight - yMouse), 20);
		ball = circle;

	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {

		Point p1 = Point(xMouse, winHeight - yMouse);
		points.push_back(p1);
		greenPointsCounter++;
		if (greenPointsCounter % 2 == 0) {

			Point a, b;
			if (points.at(greenPointsIndex).getY() < points.at(greenPointsIndex + 1).getY()) {
				a = points.at(greenPointsIndex);
				b = points.at(greenPointsIndex + 1);
			}
			else {
				a = points.at(greenPointsIndex + 1);
				b = points.at(greenPointsIndex);
			}

			Line line = Line(a, b);
			line.setColor(0, 1, 0);
			lines.push_back(line);
			greenPointsIndex += 2;
		}

	}

	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {

		Point p1 = Point(xMouse, winHeight - yMouse);
		blackPoints.push_back(p1);
		blackPointsCounter++;
		if (blackPointsCounter % 2 == 0) {
			Point a, b;

			if (blackPoints.at(blackPointsIndex).getY() < blackPoints.at(blackPointsIndex + 1).getY()) {
				a = blackPoints.at(blackPointsIndex);
				b = blackPoints.at(blackPointsIndex + 1);
			}
			else {
				a = blackPoints.at(blackPointsIndex + 1);
				b = blackPoints.at(blackPointsIndex);
			}

			Line line = Line(a, b);
			line.setColor(0, 0, 0);
			lines.push_back(line);
			blackPointsIndex += 2;

		}

	}

}

void display() {


	glClear(GL_COLOR_BUFFER_BIT);
	drawBakset();
	drawCircle(ball.getOrigo(), ball.getRadius());
	drawLine();
	
	glutSwapBuffers();

}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(winWidth, winHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Home Project");

	init();
	glutDisplayFunc(display);
	glutTimerFunc(1000/60, move, 0);
	glutTimerFunc(1000/30, detect, 0);

	glutMouseFunc(controlMouse);
	glutMainLoop();
	return 0;
}