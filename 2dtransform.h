#include "myfunctions.h"
#include <graphics.h>
#include <vector>
#include <math.h>

#ifndef __2DT_H_INCLUDED__
#define __2DT_H_INCLUDED__

void trf_menu(std::vector<Point2D> &poly, char d);

void trf( std::vector<Point2D> &p, std::vector<std::vector <float> > mat);

void trans(std::vector<Point2D> &p, Point2D t);

void scale(std::vector<Point2D> &p, float sx, float sy);

void rot(std::vector<Point2D> &p, float ang);

//void rot(std::vector<int> &p, int ang, int x, int y);

#endif // __2DT_H_INCLUDED__
