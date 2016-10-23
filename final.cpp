#include <graphics.h>
#include "menu.h"
#include "myfunctions.h"
#include "curves.h"
#include "io.h"
#include <math.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include "final.h"

using namespace std;

int r = 60, r3 = 3 * r, r2 = rnd(pow(r, 2));
int xr = rnd((sqrt(3)/2) * r), yr = rnd((r/2.0));

//triangle

int rt = 20, bt = 70, b2t = bt/2, ct = rnd(sqrt((rt*rt) + ((bt*bt) / 4)));

vector<Point2D> vals;

void myfloodfill(int x, int y, int c) {
    if (getpixel(x, y) != c) {
        if(getpixel(x,y) == WHITE) {
            Point2D t(x,y);
            vals.push_back(t);
        }
        myfloodfill(x+1, y, c);
        myfloodfill(x-1, y, c);
        myfloodfill(x, y+1, c);
        myfloodfill(x, y-1, c);
    }
}

bool insidec(int x, int y, int r, Point2D p) {
    int x2 = rnd(pow((p.x - x), 2));
    int y2 = rnd(pow((p.y - y), 2));
    int r2 = rnd(pow(r, 2));

    if(x2 + y2 - r2 <= 0)
        return true;
    return false;
}

void mycircle4(int x, int y, int r) {
    mycircle(x, y, r);

    if (insidec(mx, my, r3, Point2D(x+xr, y-yr)))
        mycircle(x+xr, y-yr, r);

    if (insidec(mx, my, r3, Point2D(x+xr, y+yr)))
        mycircle(x+xr, y+yr, r);

    if (insidec(mx, my, r3, Point2D(x-xr, y-yr)))
        mycircle(x-xr, y-yr, r);

    if (insidec(mx, my, r3, Point2D(x-xr, y+yr)))
        mycircle(x-xr, y+yr, r);
}

void triangle(int x, int y) {
    Point2D a(x + b2t, y + rt), b(x - b2t, y + rt), c(x, y - ct);

    setcolor(BLUE);
    myline(a, b);
    myline(b, c);
    myline(c, a);

    vals.clear();
    //myfloodfill(x, y, BLUE);
    Point2D t3;

    for (int i = y - b2t - 1; i <= y + b2t + 1; i ++) {
        for (int j = x - b2t - 1; j <= x + b2t + 1; j++) {
            if (getpixel(j, i) == WHITE) {
                    t3=Point2D(j,i);
                    vals.push_back(t3);
            }
        }
    }

    floodfill(x, y, BLUE);
    mycircle(x, y, rt);

    for (auto i = vals.begin(); i != vals.end(); i++) {
        if (insidec(x, y, rt, *i))
            putpixel(i->x, i->y, WHITE);
    }
}

void finalp() {
    setcolor(RED);
    mycircle(mx, my, r3);

    setcolor(WHITE);
    for (int i = 0; i <= 6; i++)
        mycircle4(mx, my - r3 + r*i, r);

    for (int i = 0; i <= 5; i++) {
        mycircle4(mx + xr, my + yr - r3 + r*i, r);
        mycircle4(mx - xr, my + yr - r3 + r*i, r);

        mycircle4(mx + 2*xr, my + 2*yr - r3 + r*i, r);
        mycircle4(mx - 2*xr, my + 2*yr - r3 + r*i, r);
    }

    setcolor(RED);
    mycircle(mx, my, r3);

    setfillstyle(EMPTY_FILL, BLACK);
    floodfill(0, 0, RED);

    setcolor(WHITE);
    mycircle(mx, my, r3);
    int xt, yt;
    while(!ismouseclick(WM_RBUTTONDOWN)) {
        int xd = mousex();
        int yd = mousey();

        if (xt != xd && yt != yd) {
            Point2D a(xt + b2t, yt + rt), b(xt - b2t, yt + rt), c(xt, yt - ct);
            setcolor(BLACK);
            myline(a, b);
            myline(b, c);
            myline(c, a);
            mycircle(xt, yt, rt);
            for (auto i = vals.begin(); i != vals.end(); i++)
                putpixel(i->x, i->y, WHITE);
            triangle(xd, yd);
            xt = xd;
            yt = yd;
        }
    }
}
