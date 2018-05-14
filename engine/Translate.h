
#ifndef ENGINE_TRANSLATE_H
#define ENGINE_TRANSLATE_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <vector>
#include "Point.h"

using std::vector;



class Translate {

    vector<Point> points;
    float time;

public:
    void setTranslate(float time, vector<Point> points);
    void doTranslate(int curveOff);
    void getGlobalCatmullRomPoint(float gt, float *pos, float *deriv);
    void getCatmullRomPoint(float t, float *p0, float *p1, float *p2, float *p3, float *pos, float *deriv);
    void renderCatmullRomCurve();
    void multMatrixVector(float *m, float *v, float *res);
    void cross(float*, float*, float*);

    void normalize(float *a);

    void buildRotMatrix(float *x, float *y, float *z, float *m);

};


#endif //ENGINE_TRANSLATE_H
