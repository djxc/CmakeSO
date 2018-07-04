#include <iostream>
#include "point.h"

using namespace std;

Point::Point(double _x, double _y)
{
	this->x = _x;
	this->y = _y;
}

Point::Point()
{
}

double Point::getX()
{
	return this->x;
}

double Point::getY()
{
	return this->y;
}

