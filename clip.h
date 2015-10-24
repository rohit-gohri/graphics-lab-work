#include "myfunctions.h"

#ifndef __CLIP_H_INCLUDED__
#define __CLIP_H_INCLUDED__

struct Point2Df {
    float x, y;

    Point2Df() {x = 0; y = 0;}
    Point2Df(const Point2D&a) {
        x = a.x;
        y = a.y;
    }
    Point2Df(const Point2Df&a) {
        x = a.x;
        y = a.y;
    }
};

struct CB_obj {
    Point2D norm;
    float tVal, nVal;
};

struct WA_obj {
    Point2D itrsc;
    char type;
    WA_obj *nxt;

    WA_obj(Point2D a, char g, WA_obj *n) {
        itrsc = a;
        type = g;
        nxt = n;
    }
};

void clip_line_cs(Point2D winMin, Point2D winMAx, Point2D p1, Point2D p2);

void clip_line_poly(std::vector<Point2D> poly, Point2D a, Point2D b, WA_obj *res);

void clip_poly(std::vector<Point2D> p1, std::vector<Point2D> p2);

#endif // __CLIP_H_INCLUDED__
