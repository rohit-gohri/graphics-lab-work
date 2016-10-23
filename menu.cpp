#include "myfunctions.h"
#include "animations.h"
#include "clip.h"
#include "2dtransform.h"
#include "curves.h"
#include "io.h"
#include <math.h>
#include <iostream>
#include <algorithm>
#include <vector>

int x1, x2, y1, y2;

void pendulum_menu() {
    cleardevice();
    outtext((char*)"Click and drag mouse to define anchor point and starting point for pendulum");
    do {
        mouseInput(x1, y1, x2, y2);
        if (y2 < y1)
            outtextxy(0, 20, (char*)"Please choose an anchor point higher than the starting point of pendulum");
    }while(y2 < y1);
    int l = (int) (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)) + 0.5);
    Point2D a(x1, y1);
    float ang = atanf(((float)(x2-x1))/(y2-y1));
    cleardevice();
    pendulum(ang, l, a, 25);
}

void myfunc_menu() {
    cleardevice();
    clearmouseclick(WM_RBUTTONDOWN);
    Point2D a, b;
    outtext((char*)"Click and drag to make a circle and show its radius, RIGHT CLICK TO EXIT");
    do {
        mouseLine(a, b);
        int r = rnd(sqrt(pow((b.x - a.x), 2) + pow((b.y - a.y), 2)));
        myline(a, b);
        mycircle(a, r);
    }while(!ismouseclick(WM_RBUTTONDOWN));
}

void clip_cs_menu() {
    cleardevice();
    outtext((char*)"Click and drag mouse to define rectangular clipping region");

    mouseInput(x1, y1, x2, y2);

    Point2D pMin(std::min(x1,x2), std::min(y1,y2)), pMax(std::max(x1,x2), std::max(y1,y2));
    std::vector<Point2D> rect;
    rect.push_back(pMin); rect.push_back(Point2D(pMin.x, pMax.y));
    rect.push_back(pMax); rect.push_back(Point2D(pMax.x, pMin.y));

    cleardevice();

    mypoly(rect);
    outtext((char*)"Click and drag mouse to make lines to be clipped, right click to EXIT");
    clearmouseclick(WM_RBUTTONDOWN);

    while(!ismouseclick(WM_RBUTTONDOWN)) {
        Point2D p1, p2;
        mouseLine(p1, p2);

        setcolor(RED);
        myline(p1, p2);

        setcolor(WHITE);
        clip_line_cs(pMin, pMax, p1, p2);
    }
}

void clip_lp_menu() {
    cleardevice();
    clearmouseclick(WM_RBUTTONDOWN);

    outtext((char*)"Left click mouse to add points to polygon and right click to finish adding points");
    std::vector<Point2D> poly;
    std::cout<<"\n\nPolygon";

    poly = mk_poly();

    std::cout<<"\n\nLine";
    cleardevice();
    outtext((char*)"Click and drag to define line");
    mypoly(poly);

    Point2D a(100, 100), b(700, 700);
    outP(a);outP(b);
    setcolor(RED);
    myline(a, b);
    getch();

    setcolor(WHITE);
    clip_line_poly(poly, a, b, NULL);
    getch();
}

void clip_poly_menu() {
    cleardevice();
    std::vector<Point2D> p1, p2;

    outtext((char*)"Define the Polygon Window");
    outtextxy(0, 25, (char*)"Left click mouse to add points to polygon and right click to finish adding points");
    std::cout<<"\nPolygon1";
    p1 = mk_poly();

    cleardevice();

    setcolor(RED);
    mypoly(p1);

    outtext((char*)"Define the Polygon to be Clipped");
    std::cout<<"\nPolygon2";
    p2 = mk_poly();

    clip_poly(p1, p2);
}

void trans_2d_menu() {
    char c, d;
    std::vector<Point2D> obj;
    cleardevice();
    do {
        outtextxy(getmaxx()/2 - 50, 0, (char*)"Menu");
        outtextxy(10, 40,  (char*)"1. Define Object");
        outtextxy(10, 60,  (char*)"2. View Object");
        outtextxy(10, 80,  (char*)"3. Transform Object");
        outtextxy(10, 100, (char*)"ESC - Exit");

        c = getch();

        switch(c) {
            case '1': obj = mk_poly(); break;
            case '2': cleardevice(); mypoly(obj); break;
            case '3':
                do {
                    cleardevice();
                    mypoly(obj);
                    outtextxy(getmaxx()/2 - 80, 0, (char*)"Transform Menu");
                    outtextxy(10, 40,  (char*)"1. Translate");
                    outtextxy(10, 60,  (char*)"2. Scale");
                    outtextxy(10, 80,  (char*)"3. Rotate");
                    outtextxy(10, 100, (char*)"4. Scale at point");
                    outtextxy(10, 120, (char*)"ESC - Back");
                    d = getch();
                    trf_menu(obj, d);
                }while(d != 27);
                break;
            case 27 : break;
            default : outtextxy(10, 120, (char*)"Not a valid option");
        }
    }while (c != 27);
}

void rot_tri_menu() {
    cleardevice();
    Point2D a, b;
    outtext((char*)"Define center for circle and radius");
    mouseLine(a, b);
    int l = rnd(sqrt(pow(b.x-a.x, 2) + pow(b.y-a.y, 2)));
    rot_t(a, l);
}

void curves() {
    myname();
}

bool compPoint2D(Point2D a, Point2D b) {
    return a.x < b.x;
}

void paratraverse(int r) {
    cleardevice();
    std::vector<Point2D> list;
    parabola(getmaxx()/2, getmaxy(), 16, list, true);
    std::sort(list.begin(), list.end(), compPoint2D);
    setcolor(WHITE);
    float theta = 0;
    for (auto i = list.begin(); i != list.end(); i+=10, theta+=10) {
        Point2D t(*i);
        if (t.y > getmaxy() - r)
            t.y = t.y - r;
        else if(i - list.begin() > list.size()/2)
            t = Point2D(t.x - r, t.y);
        else
            t = Point2D(t.x + r, t.y);
        wheel(t, r, theta);
        parabola(getmaxx()/2, getmaxy(), 16, list);
        setcolor(BLACK);
        delay(100);
        wheel(t, r, theta);
        setcolor(WHITE);
    }
    getch();
}

void skipping(int x) {
    cleardevice();
    std::vector<Point2D> neck, body, h1, h2, a1, a2, l1, l2, f1, f2;

    neck.push_back(Point2D(x-5, 120)); neck.push_back(Point2D(x-5, 130));
    neck.push_back(Point2D(x+5, 130)); neck.push_back(Point2D(x+5, 120));

    body.push_back(Point2D(x-40, 130)); body.push_back(Point2D(x+40, 130));
    body.push_back(Point2D(x+40, 200)); body.push_back(Point2D(x-40, 200));

    h1.push_back(Point2D(x-40, 130)); h1.push_back(Point2D(x-40, 140));
    h1.push_back(Point2D(x-55, 165)); h1.push_back(Point2D(x-55, 155));

    h2.push_back(Point2D(x+40, 130)); h2.push_back(Point2D(x+40, 140));
    h2.push_back(Point2D(x+55, 165)); h2.push_back(Point2D(x+55, 155));

    a1.push_back(Point2D(x-75, 140)); a1.push_back(Point2D(x-75, 150));
    a1.push_back(Point2D(x-55, 165)); a1.push_back(Point2D(x-55, 155));

    a2.push_back(Point2D(x+75, 140)); a2.push_back(Point2D(x+75, 150));
    a2.push_back(Point2D(x+55, 165)); a2.push_back(Point2D(x+55, 155));

    l1.push_back(Point2D(x-30, 200)); l1.push_back(Point2D(x-30, 260));
    l1.push_back(Point2D(x-20, 260)); l1.push_back(Point2D(x-20, 200));

    l2.push_back(Point2D(x+30, 200)); l2.push_back(Point2D(x+30, 260));
    l2.push_back(Point2D(x+20, 260)); l2.push_back(Point2D(x+20, 200));

    f1.push_back(Point2D(x-32, 260)); f1.push_back(Point2D(x-32, 265));
    f1.push_back(Point2D(x-18, 265)); f1.push_back(Point2D(x-18, 260));

    f2.push_back(Point2D(x+32, 260)); f2.push_back(Point2D(x+32, 265));
    f2.push_back(Point2D(x+18, 265)); f2.push_back(Point2D(x+18, 260));

    mycircle(x, 100, 20);
    mypoly(body); mypoly(neck);
    mypoly(h1); mypoly(h2);
    mypoly(a1); mypoly(a2);
    mypoly(l1); mypoly(l2);
    mypoly(f1); mypoly(f2);

    float y1 = a1[0].y, d = 30/50;

    setfillstyle(SOLID_FILL, RED);
    floodfill(x, 150, WHITE);
    int k = 500;
    bool inc = true;
    do {
        setcolor(YELLOW);
        hermite(a1[0].x, a1[0].y + 5, a2[0].x, a1[0].y + 5, 5, -k, -5, k);
        setcolor(WHITE);
        circle(x, 100, 20);
        mypoly(body); mypoly(neck);
        mypoly(h1); mypoly(h2);
        mypoly(a1); mypoly(a2);
        mypoly(l1); mypoly(l2);
        mypoly(f1); mypoly(f2);

        delay(100);

        setcolor(BLACK);
        hermite(a1[0].x, a1[0].y + 5, a2[0].x, a1[0].y + 5, 5, -k, -5, k);
        if(k <= -500)
            inc = false;
        if(inc) {
            k -= 10;
            y1 += d;
            a1[0].y = rnd(y1) ;
            a1[1].y = rnd(y1) + 10;
            a2[0].y = rnd(y1) ;
            a2[1].y = rnd(y1) + 10;
        }
        else {
            k += 10;
            y1 -= d;
            a1[0].y = rnd(y1) ;
            a1[1].y = rnd(y1) + 10;
            a2[0].y = rnd(y1) ;
            a2[1].y = rnd(y1) + 10;
        }
    }while(k != 500);
    getch();
}

