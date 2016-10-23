#include <graphics.h>
#include "menu.h"
#include "myfunctions.h"
#include "curves.h"
#include "io.h"
#include <math.h>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void gandhir(int x = 0) {
    //right leg
    hermite(mx - 20, 320, mx - 40 + x, 400, -20, 30, 5, 5);
    hermite(mx, 317, mx - 25 + x, 400, -20, 30, 5, 5);

//    hermite(mx - 40 + x, 400, mx - 25 + x, 400, 5, 5, 5, 5);
}

void gandhil(int y = 0) {
     //left leg
    hermite(mx + 20, 310, mx + 10 + y, 400, -20, 30, 5, 5);
    hermite(mx + 37, 302, mx + 30 + y, 400, -20, 30, 5, 5);

  //  hermite(mx - 40 + y, 400, mx - 25 + y, 400, -200, 20, 50, 20);
}

//int main()
int gandhi()
{
    initwindow(1080, 720, "Computer Graphics Lab - 348/CO/13");
    int i = 0;
    bool back = true;

    //head
    hermite(mx - 30, 28, mx + 30, 60, 25, -80, 0, 150);
    myline(mx + 30, 60, mx + 32, 80);
    myline(mx - 30, 28, mx - 35, 65);

    //nose
    myline(mx - 35, 65, mx - 30, 62);

    hermite(mx - 30, 62, mx, 90, 5, 70, -10, 20);
    mycircle(mx - 30, 50, 5);

    //glasses
    myline(mx - 25, 50, mx, 45);
    hermite(mx, 45, mx + 5, 50, 20, 0, -10, 30);

    //clothes
    myline(mx + 52, 75, mx - 28, 100);
    hermite(mx - 28, 100, mx - 30, 105, 5, 5, 5, 5);
    hermite(mx + 52, 75, mx + 55, 80, 5, 5, 5, 5);

    //left cloth curves
    hermite(mx - 30, 105, mx - 28, 140, -10, 100, 8, 50);
    hermite(mx - 28, 140, mx + 30, 110, 50, 20, 30, -20);
    hermite(mx - 22, 140, mx - 27, 230, 5, 5, 5, 5);

    //right cloth
    hermite(mx + 55, 80, mx + 85, 220, 5, -10, -50, 200);
    hermite(mx + 85, 220, mx - 27, 230, -10, 5, -10, -5);

    //right hand
    myline(mx - 30, 120, mx - 50, 115);
    myline(mx - 31, 130, mx - 52, 125);
    hermite(mx - 50, 115, mx - 58, 105, -20, -50, -10, 0);
    myline(mx - 58, 105, mx - 58, 108);
    myline(mx - 55, 80, mx - 80, 280); // stick
    hermite(mx - 58, 108, mx - 52, 125, -65, -20, 40, -20);

    //clock
    mycircle(mx - 12, 240, 10);
    myline(mx - 12, 240, mx - 13, 235);
    myline(mx - 12, 240, mx - 15, 245);

    //legs cloth
    hermite(mx - 20, 230, mx - 27, 320, -15, 10, -5, 10);
    hermite(mx - 27, 320, mx + 75, 220, 300, -10, 5, -50);
    gandhil(0);
    do {
        setcolor(WHITE);
        gandhir(i);
        delay(100);
        setcolor(BLACK);
        gandhir(i);
        if (i < -40)
            back = false;
        if (back)
            i-= 5;
        else
            i += 5;
    } while (i != 0);
    setcolor(WHITE);
    gandhir(0);
    getch();
    closegraph();
    return 0;
}
