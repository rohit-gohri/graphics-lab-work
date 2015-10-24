#include "myfunctions.h"
#include <vector>

#ifndef __IO_H_INCLUDED__
#define __IO_H_INCLUDED__

void mouseInput(int &x1, int &y1, int &x2, int &y2);

void mouseLine(Point2D &a, Point2D &b);

Point2D mousePoint();

void outP(Point2D a);

float kbf();

std::vector<Point2D> mk_poly();

#endif // __IO_H_INCLUDED__
