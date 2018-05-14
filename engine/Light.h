
#ifndef ENGINE_LIGHT_H
#define ENGINE_LIGHT_H


#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <cstring>
#include <cstdio>
#include "Point.h"

class Light {

private:
    Point pos;

public:
    char *type;

    char *getType() const;

    void setType(char *type);

    const Point &getPos() const;

    void setPos(const Point &pos);

    int turnOnLight(int numLight);
};


#endif //ENGINE_LIGHT_H
