#include <conio.h>
#include <graphics.h>
#include <math.h>

int GrafInic () {
    int gdriver,gmode;
    gdriver = DETECT;
    //initgraph (&gdriver, &gmode, "");
    initwindow(1080, 640, "Pendulum");
    return graphresult() == grOk;
}

int main () {
    if ( !GrafInic () ) return 1;

    // Declaring variables
    float theta, angle, v = 0, acc = 0;
    int t = 0;
    bool motion = true; // true - right to left, false - left to right

    // Declaring constants
    float mass = 0.5, l = 350.0, pi = 3.141567, r = 30, g = 9.8, k = 1;
    float b = 0.75; // Damping constant < 1, for under damping
    int x = getmaxx(), y = getmaxy();

    theta = pi * (5.0 / 36.0);
    angle = pi * (5.0 / 36.0);
    l = 250;

    // Creating constant shapes
    setcolor(WHITE);
    bar( (x / 2) - 10, 0, (x / 2) + 10, 5 );
    int i = 0;
    do {
        i++;
        // Creating pendulum at current position
        setcolor(WHITE);
        setfillstyle(SOLID_FILL, WHITE);
        line( (x / 2), 5, (x / 2) + (l * sin(theta)), 5 + (l * cos(theta)) );
        circle((x / 2) + ((l + r) * sin(theta)), 5 + ((l + r) * cos(theta)), r );
        floodfill((x / 2) + ((l + r) * sin(theta)), 5 + ((l + r) * cos(theta)), WHITE);

        //Waiting to delete
        delay(30);

        //Deleting current board
        setcolor(BLACK);
        setfillstyle(SOLID_FILL, BLACK);
        line( (x / 2), 5, (x / 2) + (l * sin(theta)), 5 + (l * cos(theta)) );
        floodfill((x / 2) + ((l + r) * sin(theta)), 5 + ((l + r) * cos(theta)), BLACK);
        //circle((x / 2) + ((l + r) * sin(theta)), 5 + ((l + r) * cos(theta)), r );

        if (motion)
            theta -= pi / 180;
        else
            theta += pi / 180;

        if (theta <= -angle)
            motion = false;

        if (theta >= angle) {
            angle -= pi / 180;
            theta = angle;
            motion = true;
        }
    } while (angle > 0.0 );//&& i < 1000);

    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    line( (x / 2), 5, (x / 2), 5 + l );
    circle((x / 2), 5 + l + r, r );
    floodfill((x / 2), 5 + l + r, WHITE);

    getch ();

    closegraph ();
    return 0;
}
