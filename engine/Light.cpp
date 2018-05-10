
#include <GL/glew.h>
#include <cstring>
#include <cstdio>
#include "Light.h"

char *Light::getType() const {
    return type;
}

void Light::setType(char *type) {
    Light::type = type;
}

const Point &Light::getPos() const {
    return pos;
}

void Light::setPos(const Point &pos) {
    Light::pos = pos;
}

void Light::turnOnLight(int numLight) {


    GLfloat amb[4] = {0.1, 0.1, 0.1, 1};
    GLfloat diff[4] = {1.0, 1.0, 1.0, 0.0};
    GLfloat posL[4] = { pos.getX(), pos.getY(), pos.getZ() };

    if (strcmp(type, "DIRECTIONAL") == 0) {
        posL[3] = 0.0f;
    }


    switch(numLight) {
        case 0 : glLightfv(GL_LIGHT0, GL_POSITION, posL);
                 glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
                 glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
                 break;
        case 1 : glLightfv(GL_LIGHT1, GL_POSITION, posL);
                 glLightfv(GL_LIGHT1, GL_AMBIENT, amb);
                 glLightfv(GL_LIGHT1, GL_DIFFUSE, diff);
                 break;
        case 2 : glLightfv(GL_LIGHT2, GL_POSITION, posL);
                 glLightfv(GL_LIGHT2, GL_AMBIENT, amb);
                 glLightfv(GL_LIGHT2, GL_DIFFUSE, diff);
                 break;
    }
}
