//
// Created by Marco Silva on 25/04/2018.
//

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
    void doTranslate();

};


#endif //ENGINE_TRANSLATE_H
