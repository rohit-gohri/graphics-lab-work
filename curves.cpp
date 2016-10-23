#include "myfunctions.h"
#include "curves.h"
#include <math.h>
#include <vector>



std::vector<int> compCoeff(int n) {
    int k, j;
    std::vector<int> c(n, 1);
    for (k = 0; k <= n; k++) {
        for (j = n; j > k + 1; j--)
            c[k] *= j;
        for(j = n - k; j > 2; j--)
            c[k] /= j;
    }
    return c;
}

Point3D compPt(int nCont, float u, std::vector<Point3D> &cntrls, std::vector<int> &c) {
    int k, n = nCont - 1;
    float blend;
    std::vector<int> b(n, 0);
    Point3D t;
    for (k = 0; k < nCont; k++) {
        blend = c[k] * powf(u, k) * powf(1-u, n-k);
        t.x += cntrls[k].x * blend;
        t.y += cntrls[k].y * blend;
        t.z += cntrls[k].z * blend;
    }
    return t;
}

std::vector<Point3D> bezier (std::vector<Point3D> &cntrls, int nCont, int m) {
    std::vector<Point3D> crv;
    int i;

    std::vector<int> c = compCoeff(nCont - 1);

    for(i = 0; i <= m; i++) {
        crv.push_back(compPt(nCont, i / (float)m, cntrls, c));
    }
    return crv;
}

void hermite(int x1, int y1, int x2, int y2, int xt1, int yt1, int xt2, int yt2) {
    float outx, outy, u, u2, u3;
    int tempx[2], tempy[2], c = getcolor();

    int dx = x1 - x2, dy = y1 - y2;

    tempx[0] = 2*dx + xt1 + xt2;
    tempx[1] = -3*dx - 2*xt1 - xt2;

    tempy[0] = 2*dy + yt1 + yt2;
    tempy[1] = -3*dy - 2*yt1 - yt2;

    for(u = 0; u <= 1; u += 0.005) {
        u2 = u*u;
        u3 = u2*u;
        outx = u3*tempx[0] + u2*tempx[1] + u*xt1 + x1;
        outy = u3*tempy[0] + u2*tempy[1] + u*yt1 + y1;
        putpixel(rnd(outx), rnd(outy), c);
    }
}

void myname() {

}
