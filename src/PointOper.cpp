#include "PointOper.h"

PointOper::PointOper(Point p1, Point p2)
{
	pt1 = p1;
	pt2 = p2;
}

Point PointOper::pointMinus()
{
	double mx = pt1.x - pt2.x;
	double my = pt1.y - pt2.y;
	return Point(mx, my);
}
double PointOper::pointMult()
{
	return pt1.x*pt2.y - pt1.y*pt2.x;
}
