#include <graphics.h>
#include "menu.h"
#include "myfunctions.h"
#include "curves.h"
#include "io.h"
#include "final.h"
#include <math.h>
#include <iostream>
#include <algorithm>
#include <vector>

/*int main() {
char c;

    do {
        cleardevice();
        settextstyle(8, HORIZ_DIR, 4);
        outtextxy(getmaxx()/2 - 200, 5, (char*)"Computer Graphics Lab");
        settextstyle(8, HORIZ_DIR, 2);
        outtextxy(10, 55,  (char*)"Choose Experiment to Display:");
        outtextxy(10, 85,  (char*)"1. Pendulum");
        outtextxy(10, 105, (char*)"2. Arrow Shit");
        outtextxy(10, 125, (char*)"3. MyFunctions - Line and Circle");
        outtextxy(10, 145, (char*)"4. Line Clipping in Rectangular Window - Cohen Sutherland");
        outtextxy(10, 165, (char*)"5. Line Clipping in Polygon Window - Cyrus Beck");
        outtextxy(10, 185, (char*)"6. Polygon Clipping in Polygon Window");
        outtextxy(10, 205, (char*)"7. 2D Transformations");
        outtextxy(10, 225, (char*)"8. skip");
        outtextxy(10, 245, (char*)"9. para");
        outtextxy(10, 265, (char*)"Esc - EXIT");

        c = getch();
        switch(c) {
            case '1': pendulum_menu(); break;
            case '2': rot_tri_menu(); break;
            case '3': myfunc_menu(); break;
            case '4': clip_cs_menu(); break;
            case '5': clip_lp_menu(); break;
            case '6': clip_poly_menu(); break;
            case '7': trans_2d_menu(); break;
            case '8': skipping(); break;
            case '9': paratraverse(20); break;
            case 27 : break;
            default : outtextxy(10, 285, (char*)"Try again with a valid option");
        }
    }while(c != 27);

    return 0;
}
*/

int main() {
    initwindow(1080, 720, "Practical");

    finalp();

    getch();
    closegraph();
    return 0;
}
