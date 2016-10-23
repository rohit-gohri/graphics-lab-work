#include "myfunctions.h"
#include "io.h"
#include <math.h>

void myline(int x1, int y1, int x2, int y2) {
    int X = 1, Y = 1;
    int c = getcolor();
    int dx = x2 - x1, dy = y2 - y1, x = x1, y = y1;
    if (x2 < x1) {
        X = -1;
        dx = -dx;
    }
    if (y2 < y1) {
        Y = -1;
        dy = -dy;
    }
    float m = ((float)dy)/dx;
    if (m <= 1) {
        int p = (2*dy) - dx;
        while (abs(x - x2) > 0 ) {
            putpixel(x, y, c);
            if (p <= 0) {
                p += 2*dy;
            }
            else {
                p += 2 * (dy - dx);
                y += Y;
            }
            x += X;
        }
    }
    else {
        int p = (2*dx) - dy;
        while (abs(y - y2) > 0 ) {
            putpixel(x, y, c);
            if (p <= 0) {
                p += 2*dx;
            }
            else {
                p += 2 * (dx - dy);
                x += X;
            }
            y += Y;
        }
    }
    putpixel(x2, y2, c);
}

void myline(Point2D p1,Point2D p2) {
    myline(p1.x, p1.y, p2.x, p2.y);
}

void plotpoints(int x, int y, int x1, int y1) {
    int c = getcolor();
    putpixel(x1 + x, y1 - y, c);
    putpixel(x1 + y, y1 - x, c);
    putpixel(x1 - y, y1 - x, c);
    putpixel(x1 - x, y1 - y, c);
    putpixel(x1 - x, y1 + y, c);
    putpixel(x1 - y, y1 + x, c);
    putpixel(x1 + y, y1 + x, c);
    putpixel(x1 + x, y1 + y, c);

}

void mycircle(int x1, int y1, int r) {
    int x = 0, y = r, d = 1 - r;
    plotpoints(x, y, x1, y1);
    while (x <= y) {
        if (d <= 0) {
            d += (2 * x) + 3;
        }
        else {
            d += (2 * (x - y)) + 5;
            y--;
        }
        x++;
        plotpoints(x, y, x1, y1);
    }
}

void mycircle(Point2D c, int r) {
    mycircle(c.x, c.y, r);
}

void mypoly(std::vector<Point2D> poly) {
    int n = poly.size();
    for(int i = 0; i <  n; i++) {
        myline(poly[i], poly[(i+1)%n]);
    }
}

void mypoly(std::vector<std::vector<int> > poly) {
    int n = poly.size() - 1;
    for(int i = 0; i <  n; i++) {
        myline(poly[i][0], poly[i][1], poly[i+1][0], poly[i+1][1]);
    }
    myline(poly[n][0], poly[n][1], poly[0][0], poly[0][1]);
}

void wheel(Point2D a, int r, float theta) {
    circle(a.x, a.y, r);
    float d = 3.14159 / 180;
    int s1 = rnd(r * sin(theta * d)), c1 = rnd(r * cos(theta * d)),
        s2 = rnd(r * sin((theta - 45) * d)), c2 = rnd(r * cos((theta - 45) * d));

    myline(Point2D(a.x - c1, a.y - s1), Point2D(a.x + c1, a.y + s1));
    myline(Point2D(a.x + s1, a.y - c1), Point2D(a.x - s1, a.y + c1));
    myline(Point2D(a.x - c2, a.y - s2), Point2D(a.x + c2, a.y + s2));
    myline(Point2D(a.x + s2, a.y - c2), Point2D(a.x - s2, a.y + c2));
}

void parabola(int x1, int y1, int a, std::vector<Point2D> &list, bool t) {
    int x = 0, y = 0, p, c = getcolor();
    p = 1 - (2 * a);
    int a4 = 4 * a;
    do {
        putpixel(x1 + x, y1 - y, c);
        if (t) {
            list.push_back(Point2D(x1+x, y1-y));
            list.push_back(Point2D(x1-x, y1-y));
        }
        putpixel(x1 - x, y1 - y, c);
        if (p > a4) {
            if (p < 0) {
                p += 2 * (1 + x) - a4;
                x++;
            }
            else
                p -= a4;
            y++;
        }
        else {
            if (p >= 0) {
                y++;
                p -= a4;
            }
            p += (2 * x) + 3;
            x++;
        }
    } while ( y1 > y);
}

void myellipse(int x1, int y1, int a, int b) {

}

void floodfill(Point2D c, int b) {
    floodfill(c.x, c.y, b);
}

void mypoly(std::vector<Point3D> poly, int plane) {
    std::vector<Point2D> projection;
    switch(plane) {
        // xy plane
        case 1 :
            for (int i = 0; i < poly.size(); i++) {
                projection.push_back(Point2D(rnd(poly[i].x), rnd(poly[i].y)));
            }
            mypoly(projection);
            break;
        case 2 : // yz plane
            for (int i = 0; i < poly.size(); i++) {
                projection.push_back(Point2D(rnd(poly[i].z), rnd(poly[i].y)));
            }
            mypoly(projection);
            break;
        case 3 : // xz plane
            for (int i = 0; i < poly.size(); i++) {
                projection.push_back(Point2D(rnd(poly[i].x), rnd(poly[i].z)));
            }
            mypoly(projection);
            break;
    }
}
