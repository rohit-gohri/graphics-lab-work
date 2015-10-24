#include "myfunctions.h"
#include "animations.h"
#include "clip.h"
#include "2dtransform.h"
#include "io.h"
#include <math.h>
#include <iostream>
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
        int r = (int)(sqrt(pow((b.x - a.x), 2) + pow((b.y - a.y), 2)) + 0.5);
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
    int l = (int)(sqrt(pow(b.x-a.x, 2) + pow(b.y-a.y, 2)) + 0.5);
    rot_t(a, l);
}
