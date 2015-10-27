#include "io.h"
#include <graphics.h>
#include <iostream>
#include <cstdio>
#include <math.h>

void mouseInput(int &x1, int &y1, int &x2, int &y2) {
    clearmouseclick(WM_LBUTTONDOWN);
    clearmouseclick(WM_LBUTTONUP);

    while (!ismouseclick(WM_LBUTTONDOWN)) {}
    getmouseclick(WM_LBUTTONDOWN, x1, y1);

    while (!ismouseclick(WM_LBUTTONUP)) {}
    getmouseclick(WM_LBUTTONUP, x2, y2);
}

void mouseLine(Point2D &a, Point2D &b) {
    int x, y;
    clearmouseclick(WM_LBUTTONDOWN);
    clearmouseclick(WM_LBUTTONUP);

    while (!ismouseclick(WM_LBUTTONDOWN)) {}
    getmouseclick(WM_LBUTTONDOWN, x, y);
    a.x = x; a.y = y;

    while (!ismouseclick(WM_LBUTTONUP)) {}
    getmouseclick(WM_LBUTTONUP, x, y);
    b.x = x; b.y = y;
}

Point2D mousePoint() {
    int x, y;
    clearmouseclick(WM_LBUTTONDOWN);

    while (!ismouseclick(WM_LBUTTONDOWN)) {}
    getmouseclick(WM_LBUTTONDOWN, x, y);
    return Point2D(x,y);
}

void outP(Point2D a) {
    std::cout<<"\nx:"<<a.x<<"\ty:"<<a.y;
}

float kbf() {
    char c, fc[10];
    float a = 0;
    int i = 1;
    do {
        c = getch();
        cleardevice();
        if(c >= 48 && c <= 57) {
            a = a*10 + (c-48);
            snprintf(fc, 10, "%f", a);
            outtext(fc);
        }
    }while(c != 13 && c!= 32 && c!= 46);
    outtext(fc);
    if(c == 46) {
        do {
            c = getch();
            cleardevice();
            if(c >= 48 && c <= 57) {
                a += (c-48)*pow(0.1, i++);
                snprintf(fc, 10, "%f", a);
                outtext(fc);
            }
        }while(c != 13 && c!= 32);
    }
    return a;
}

std::vector<Point2D> mk_poly() {
    int x1, y1, n = 0;
    std::vector<Point2D> p;
    clearmouseclick(WM_LBUTTONDOWN);
    clearmouseclick(WM_RBUTTONDOWN);


    while(!ismouseclick(WM_RBUTTONDOWN) || n < 2) {
        while (!ismouseclick(WM_LBUTTONDOWN)) {}
        getmouseclick(WM_LBUTTONDOWN, x1, y1);

        p.push_back(Point2D(x1, y1));

        n = p.size()-1;
        outP(p[n]);
        if (n > 0)
            myline(p[n], p[n-1]);
    }
    myline(p[n], p[0]);
    return p;
}
