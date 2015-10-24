#include "clip.h"
#include "io.h"
#include <iostream>
#include <math.h>
#include <algorithm>


//Cohen Sutherland Rectangle Clipping

#define LEFT_EDGE 0x1
#define RIGHT_EDGE 0x2
#define BOTTOM_EDGE 0x4
#define TOP_EDGE 0x8

#define INSIDE(a) (!a)
#define REJECT(a,b) (a&b)
#define ACCEPT(a,b) (!(a|b))

Point2D roundP(Point2Df a) {
    return Point2D((int)(a.x + 0.5), (int)(a.y + 0.5));
}

unsigned char encode(Point2Df p, Point2D winMin, Point2D winMax) {
    unsigned char code = 0x00;

    if (p.x < (float)winMin.x)
        code = code | LEFT_EDGE;
    if (p.x > (float)winMax.x)
        code = code | RIGHT_EDGE;
    if (p.y < (float)winMin.y)
        code = code | BOTTOM_EDGE;
    if (p.y > (float)winMax.y)
        code = code | TOP_EDGE;

    return code;
}

void swapPoints(Point2Df &p1, Point2Df &p2) {
    Point2Df t(p1);
    p1 = p2;
    p2 = t;
}

void swapCodes(unsigned char &c1, unsigned char &c2) {
    unsigned char t;
    t = c1;
    c1 = c2;
    c2 = t;
}

void clip_line_cs(Point2D winMin, Point2D winMax, Point2D a, Point2D b) {
    unsigned char code1, code2;
    bool done = false, draw = false;
    float m = 0;
    Point2Df p1(a), p2(b);

    while(!done) {
        code1 = encode(p1, winMin, winMax);
        code2 = encode(p2, winMin, winMax);
        if(ACCEPT(code1, code2)) {
            done = true;
            draw = true;
        }
        else {
            if (REJECT(code1, code2)) {
                done = TRUE;
            }
            else {
                if (INSIDE(code1)) {
                    swapPoints(p1, p2);
                    swapCodes(code1, code2);
                }
                if (p1.x != p2.x)
                    m = (p2.y - p1.y) / (p2.x - p1.x);
                if (code1 & LEFT_EDGE) {
                    p1.y +=(winMin.x - p1.x) * m;
                    p1.x = winMin.x;
                }
                else if (code1 & RIGHT_EDGE) {
                    p1.y += (winMax.x - p1.x) * m;
                    p1.x = winMax.x;
                }
                else if (code1 & BOTTOM_EDGE) {
                    if (p2.x != p1.x)
                        p1.x += (winMin.y - p1.y) / m;
                    p1.y = winMin.y;
                }
                else if (code1 & TOP_EDGE) {
                    if (p2.x != p1.x)
                        p1.x += (winMax.y - p1.y) / m;
                    p1.y = winMax.y;
                }
            }
        }
        if (draw) {
            myline(roundP(p1), roundP(p2));
        }
    }
}

//Cyrus Beck Line Clipping in Polygon Window

bool custSort(CB_obj a, CB_obj b) {
    return a.tVal < b.tVal;
}

float dot(Point2D a, Point2D b) {
    return ((a.x * b.x) + (a.y * b.y));
}

Point2D subtract(Point2D a, Point2D b) {
    return Point2D(b.x - a.x, b.y - a.y);
}

Point2D para(Point2D a, Point2D b, float t) {
    Point2D temp;
    temp.x = a.x + (int)((b.x - a.x) * t + 0.5);
    temp.y = a.y + (int)((b.y - a.y) * t + 0.5);
    return temp;
}

void clip_line_poly(std::vector<Point2D> poly, Point2D a, Point2D b, WA_obj *res) {
    std::vector<CB_obj> data;
    Point2D t, diff = subtract(a, b);
    CB_obj x;
    int n = poly.size();

    for (int i = 0; i < n; i++) {
        t = subtract(poly[i], poly[(i+1)%n]);
        t = Point2D(t.y, -t.x);
        x.norm = t;
        x.nVal = dot(diff, t);
        x.tVal = dot(subtract(poly[i], a), t) / (-x.nVal);
        data.push_back(x);
    }

    std::sort(data.begin(), data.end(), custSort);
    std::cout<<"\n\nNormal \t\ttVal \t  nVal";

    auto i = data.begin();
    while(i != data.end()) {
        if (i->tVal > 1 || i->tVal < 0)
            data.erase(i);
        else {
            outP(i->norm);
            std::cout<<"\t"<<i->tVal<<", "<<i->nVal;
            i++;
        }
    }

    for (int i = 0; i < n - 1; i++) {
        if (data[i].nVal < 0 && data[i+1].nVal > 0) {
            Point2D t1 = para(a, b, data[i].tVal), t2 = para(a, b, data[i+1].tVal);
            myline(t1, t2);
            if (res != NULL) {
                WA_obj *w = new WA_obj(t1, 'i', NULL);
                res->nxt = w;
                res = w;
                w = new WA_obj(t2, 'o', NULL);
                res->nxt = w;
                res = w;
            }
            std::cout<<"\n\nSelected Points tVal";
            outP(t1);
            std::cout<<"\t"<<data[i].tVal;
            outP(t2);
            std::cout<<"\t"<<data[i+1].tVal;
            i++;
        }
    }
}

void clip_poly(std::vector<Point2D> p1, std::vector<Point2D> p2) {
    WA_obj *sub = NULL, *clip = NULL, *res = NULL, *temp = NULL;

    for(size_t i = 0; i < p2.size(); i++) {
        temp = new WA_obj(p2[i], 'p', NULL);
        if (res == NULL) {
            res = temp;
            sub = res;
        }
        else {
            res->nxt = temp;
            res = temp;
        }
        clip_line_poly(p1, p2[i], p2[(i+1)%p2.size()], res);
    }
    res = NULL;
    for(size_t i = 0; i < p1.size(); i++) {
        temp = new WA_obj(p1[i], 'p', NULL);
        if (res == NULL) {
            res = temp;
            clip = res;
        }
        else {
            res->nxt = temp;
            res = temp;
        }
        clip_line_poly(p2, p1[i], p1[(i+1)%p1.size()], res);
    }


}
/*
void traverse(Point first, std::vector<std::pair<Point, bool> > sList, int i, std::vector<std::pair<Point, bool> > cList, int j)
{

}

std::vector< std::pair<Point, bool> > clipline(std::vector<Point> &l, std::vector<Point> &poly, int n)
{
    std::vector < std::pair<Point, bool> > res;
    Point temp, diff;
    diff.x = l[1].x - l[0].x;
    diff.y = l[1].y - l[0].y;

    std::vector<Point> vect, norm;
    for(int i = 0; i < n - 1; i++)
    {
        temp.x = poly[i+1].x - poly[i].x;
        temp.y = poly[i+1].y - poly[i].y;
        vect.push_back(temp);
        temp.x = vect[i].y;
        temp.y = -vect[i].x;
        norm.push_back(temp);
    }
    temp.x = poly[0].x - poly[n-1].x;
    temp.y = poly[0].y - poly[n-1].y;
    vect.push_back(temp);
    temp.x = vect[n-1].y;
    temp.y = -vect[n-1].x;
    norm.push_back(temp);

    std::vector<float> t, ni;
    float tempf;
    for(int i = 0; i < n; i++)
    {
        tempf = (float)(norm[i].x * diff.x) + (norm[i].y * diff.y);
        ni.push_back(tempf);
        tempf = ( (float)(norm[i].x * (l[0].x - poly[i].x)) + ((float)(norm[i].y * (l[0].y - poly[i].y)))) / (-((float)ni[i]));
        t.push_back(tempf);
    }

    for (int i = 0; i < n - 1; i++) {
        //std::cout << "\nNi " << i << " : " << ni[i] << "\n";
        //std::cout << "T " << i << " : " << t[i] << "\n";
        if (ni[i] > 0 && ni[i+1] < 0) {
            int nxt = 1;
            while ( i+1+nxt < n && ni[i+nxt+1] < 0 && t[i+nxt+1] < t[i+nxt])
                nxt++;
            Point d1, d2;
            d1.x = l[0].x + (int)roundf((l[1].x - l[0].x) * t[i]);
            d1.y = l[0].y + (int)roundf((l[1].y - l[0].y) * t[i]);
            d2.x = l[0].x + (int)roundf((l[1].x - l[0].x) * t[i+nxt]);
            d2.y = l[0].y + (int)roundf((l[1].y - l[0].y) * t[i+nxt]);
            res.push_back(std::make_pair(d1, false));
            res.push_back(std::make_pair(d2, true));
            //std::cout << "Line co-ordinates : \n";
            //std::cout << d1.x << ", " << d1.y << " : " << d2.x << ", " << d2.y << "\n";
            //myline(d1.x, d1.y, d2.x, d2.y);
        }
    }
    return res;
}

void clippoly(std::vector<Point> subject, std::vector<Point> clipped)
{
    std::vector< std::pair<Point, bool> > sList, cList, temp;
    std::vector<Point> line;
    std::vector<bool> sVisit, cVisit;
    bool f = false;

    for (int i = 0; i < subject.size(); i++)
    {
        sList.push_back(std::make_pair(subject[i], false));
        line.push_back(subject[i]);
        if (i+1 == subject.size())
            line.push_back(subject[0]);
        else
            line.push_back(subject[i+1]);
        temp = clipline(line, clipped, 5);
        for(int j = 0; j < temp.size(); j++)
            sList.push_back(temp[j]);
        line.clear();
    }

    for (int i = 0; i < clipped.size(); i++)
    {
        cList.push_back(std::make_pair(clipped[i], false));
        line.push_back(clipped[i]);
        if (i+1 == clipped.size())
            line.push_back(clipped[0]);
        else
            line.push_back(clipped[i+1]);
        temp = clipline(line, subject, 5);
        for(int j = 0; j < temp.size(); j++)
            cList.push_back(temp[j]);
        line.clear();
    }

    std::cout << "Subject List\n";
    for (int i = 0; i < sList.size(); i++)
    {
        std::cout << sList[i].first.x << ", " << sList[i].first.y << "\n";
    }

    std::cout << "Clipped List\n";
    for (int i = 0; i < cList.size(); i++)
    {
        std::cout << cList[i].first.x << ", " << cList[i].first.y << "\n";
    }

    Point t = sList[1].first;
    for (int i = 1; i < sList.size(); i++)
    {

    }
}
*/
