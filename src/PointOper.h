#ifndef __VECTOR_H_
#define __VECTOR_H_
#include "point.h"

class PointOper{
	public:
		Point pt1;
		Point pt2;
		PointOper(Point p1, Point p2);
		Point pointMinus();
		double pointMult();
};

#endif
