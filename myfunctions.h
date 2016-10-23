#include<graphics.h>
#include<vector>
#include<utility>

#ifndef __MYFUNC_H_INCLUDED__
#define __MYFUNC_H_INCLUDED__

#define rnd(a) (int)(a + 0.5)


struct Point3D {
    float x, y, z;

    Point3D() {x = 0; y = 0; z = 0;}
    Point3D(float a, float b, float c) {
        x = a;
        y = b;
        z = c;
    }
    Point3D(const Point3D&t) {
        x = t.x;
        y = t.y;
        z = t.z;
    }
};

struct Point2D {
    int x, y;

    Point2D() {x = 0; y = 0;}
    Point2D(int a, int b) {
        x = a;
        y = b;
    }
    Point2D(const Point2D&t) {
        x = t.x;
        y = t.y;
    }
};

void myellipse(int x1, int y1, int a, int b);

void myline(int x1, int y1, int x2, int y2);

void myline(Point2D p1,Point2D p2);

void mypoly(std::vector<Point2D> poly);

void mypoly(std::vector<std::vector<int> > poly);

void plotpoints(int x, int y, int x1, int y1);

void mycircle(int x1, int y1, int r);

void mycircle(Point2D c, int r);

void parabola(int x1, int y1, int a, std::vector<Point2D> &list, bool t = false);

void wheel(Point2D a, int r, float theta);

void floodfill(Point2D c, int b);
#endif // __MYFUNC_H_INCLUDED__
