#include "myfunctions.h"
#include "animations.h"
#include "io.h"
#include <math.h>

void pendulum(float angle, float l, Point2D p, int r) {
    clearmouseclick(WM_RBUTTONDOWN);
    // Declaring variables
    bool motion = true; // true - right to left, false - left to right

    // Declaring constants
    float d = 3.14159 / 180;
    float theta = angle, ang = angle, a = angle/4;

    // Creating constant shapes
    setcolor(WHITE);
    myline(0, p.y, getmaxx(), p.y);
    bar( p.x - 10, p.y, p.x + 10, p.y + 5 );

    do {
        // Creating pendulum at current position
        setcolor(WHITE);
        setfillstyle(SOLID_FILL, WHITE);
        myline(p.x, p.y + 5, p.x + (l * sin(theta)), p.y + 5 + (l * cos(theta)) );
        mycircle(p.x + ((l + r) * sin(theta)), p.y + 5 + ((l + r) * cos(theta)), r );
        floodfill(p.x + ((l + r) * sin(theta)), p.y + 5 + ((l + r) * cos(theta)), WHITE);

        //Waiting to delete
        delay(30);

        //Deleting current board
        setcolor(BLACK);
        setfillstyle(SOLID_FILL, BLACK);
        myline( p.x, p.y + 5, p.x + (l * sin(theta)), p.y + 5 + (l * cos(theta)) );
        floodfill(p.x + ((l + r) * sin(theta)), p.y + 5 + ((l + r) * cos(theta)), BLACK);

        if (motion) // if true moves from right to left
            theta -= 2*d;
        else
            theta += 2*d; // else from left to right

        if (theta <= -ang) // changes direction of motion
            motion = false;

        if ((theta >= ang - (d * ((int)(ang / a + 1))) || theta >= ang) && (!motion)) { // Damping condition
            ang -= d * ((int)(ang / a) + 1);
            theta = ang;
            motion = true;
        }

        if(ismouseclick(WM_RBUTTONDOWN))
            break;
    } while (ang > 0.0);
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    myline( p.x, p.y + 5, p.x, p.y + 5 + l );
    mycircle(p.x, p.y + 5 + l + r, r );
    floodfill(p.x, p.y + 5 + l + r, WHITE);
}
