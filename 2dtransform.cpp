#include "2dtransform.h"
#include "io.h"
#include <iostream>

void trf_menu(std::vector<Point2D> &poly, char d) {
    float sx, sy, ang;
    int x1, y1, x2, y2;
    Point2D t;

    switch(d) {
        case '1' : trans(poly, mousePoint()); break;
        case '2' :
            cleardevice();
            outtext((char*)"Enter scaling factor");
            sx = kbf(); sy = kbf();
            scale(poly, sx, sy);
            break;
        case '3' :
            cleardevice();
            mypoly(poly);
            outtext((char*)"R");
            mouseInput(x1, y1, x2, y2);
            ang = atanf((y1)/x1) - atanf((y2)/x2);
            rot(poly, ang);
            break;
        case '4' :
            cleardevice();
            outtext((char*)"Click on point relative to which to scale");
            mypoly(poly);
            t = mousePoint();
            t = Point2D(-t.x, -t.y);
            trans(poly, t);

            cleardevice();
            outtext((char*)"Enter scaling factor");
            sx = kbf(); sy = kbf();
            scale(poly, sx, sy);

            t = Point2D(-t.x, -t.y);
            trans(poly, t);
            break;
        default : break;
    }
}

void trf(std::vector<Point2D> &p, std::vector<std::vector <float> > mat) {
    std::vector<int> temp, em;
    for(size_t k = 0; k < p.size(); k++) {
        temp = em;
        temp.push_back(p[k].x); temp.push_back(p[k].y); temp.push_back(1);
        float t = 0;
        for (int i = 0; i < 3; i ++)
        {
            t = 0;
            for (int j = 0; j < 3; j++)
            {
                t += mat[i][j] * temp[j];
            }
            if (i == 0)
                p[k].x = (int)(t+0.5);
            else if (i == 1)
                p[k].y = (int)(t+0.5);
        }
    }
}

void trans(std::vector<Point2D> &p, Point2D t) {
    std::vector<std::vector <float> > mat(3);
    for(int i = 0; i < 3; i++)
    {
        mat[i].resize(3);
        mat[i][i] = 1;
    }
    mat[0][2] = t.x; mat[1][2] = t.y;
    trf(p, mat);
}

void scale(std::vector<Point2D> &p, float sx, float sy) {
    std::vector<std::vector <float> > mat(3);
    for(int i = 0; i < 3; i++)
    {
        mat[i].resize(3);
        mat[i][i] = 1;
    }
    mat[0][0] = sx; mat[1][1] = sy;
    std::cout<<"works";
    trf(p, mat);
}

void rot(std::vector<Point2D> &p, float ang) {
    std::vector<std::vector <float> > mat(3);
    float c, s;
    c = cos(ang);
    s = sin(ang);
    for(int i = 0; i < 3; i++) {
        mat[i].resize(3);
        mat[i][i] = c;
    }
    mat[2][2] = 1;
    mat[0][1] = -s; mat[1][0] = s;
    trf(p, mat);
}

/*void rot(std::vector<int> &p, int ang, int x, int y)
{
    std::vector<std::vector <float> > mat(3);
    float c, s, rx, ry, pi = 3.14159;
    c = cosf((ang * pi) / 180);
    s = sinf((ang * pi) / 180);
    rx = ((1-c) * x) + (s * y);
    ry = ((1-c) * y) + (s * x);
    for(int i = 0; i < 3; i++)
    {
        mat[i].resize(3);
        mat[i][i] = c;
    }
    mat[2][2] = 1;
    mat[0][1] = -s; mat[1][0] = s;
    mat[0][2] = rx;
    mat[1][2] = ry;
    trf(p, mat);
}
*/
