#include "animations.h"
#include "myfunctions.h"
#include <math.h>
#include <vector>

void rot_t(Point2D c, int r) {
    cleardevice();

    mycircle(c, r + 25);
    mycircle(c, r - 25);
    floodfill(c.x + r, c.y, WHITE);

    float ang, phi, theta = 0, d = 3.14159 / 180.0;
    Point2D p;
    std::vector<Point2D> tri(3, Point2D());
    int l = 100, rl = rnd(sqrt(pow(r,2) + 0.75*(pow(l,2))));

    ang = atan((sqrt(3)*l)/(2*r));
    phi = ang - d;

    while (theta <= d * 360) {
        setcolor(WHITE);
        tri[0].x = c.x + rnd(rl * cos(theta));
        tri[0].y = c.y + rnd(rl * sin(theta));

        float rc = cos(theta - ang), rs = sin(theta - ang);
        float fc = cos(theta - phi), fs = sin(theta - phi);

        tri[1].x = c.x  + rnd((r - l/2) * rc);
        tri[1].y = c.y  + rnd((r - l/2) * rs);
        tri[2].x = c.x  + rnd((r + l/2) * rc);
        tri[2].y = c.y  + rnd((r + l/2) * rs);

        mypoly(tri);

        setfillstyle(SOLID_FILL, WHITE);

        p.x = c.x + rnd((r + 26) * fc);
        p.y = c.y + rnd((r + 26) * fs);
        floodfill(p, WHITE);

        p.x = c.x + rnd((r - 26) * fc);
        p.y = c.y + rnd((r - 26) * fs);
        floodfill(p, WHITE);

        theta += 2 * d;
       // delay(10);

        setcolor(BLACK);
        mycircle(c, r + 26);
        mycircle(c, r - 26);

        setfillstyle(SOLID_FILL, BLACK);
        floodfill(tri[1], BLACK);
        floodfill(tri[2], BLACK);
    }
    getch();
}
