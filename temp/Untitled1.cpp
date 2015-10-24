#include<graphics.h>
#include<vector>
#include<utility>

#ifndef __MYFUNC_H_INCLUDED__
#define __MYFUNC_H_INCLUDED__

struct Point
{
    int x, y;
};

std::vector< std::pair<Point, bool> > clipline(std::vector<Point> &l, std::vector<Point> &poly, int n);

void clippoly(std::vector<Point> p, std::vector<Point> poly);

void plotpoints(int x, int y, int x1, int y1);

void mycircle(int x1, int y1, int r);

void mycircle(Point c, int r);

void myline(int x1, int y1, int x2, int y2);

void myline(Point p1,Point p2);

//void mypoly(std::vector<Point> poly);

void mypoly(std::vector<std::vector<int> > poly);

void parabola(int x1, int y1, int a, int x = 0, int y = 0);

void pendulum(float angle, float l, int x, int r);

#endif // __MYFUNC_H_INCLUDED__
