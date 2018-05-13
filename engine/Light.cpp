
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

int Light::turnOnLight(int numLight) {

    int res = 0;

    float yellow[4] = {255.0 / 255.0, 204.0 / 255.0, 102.0 / 255.0, 1.0f};
    float black[4] = {0.2, 0.2, 0.2, 1.0f};

    GLfloat amb[4] = {0.1, 0.1, 0.1, 1.0};
    GLfloat diff[4] = {5.0, 5.0, 5.0, 1.0};
    GLfloat posL[4] = { pos.getX(), pos.getY(), pos.getZ() };

    glPushAttrib(GL_LIGHTING_BIT);

    if (strcmp(type, "DIRECTIONAL") == 0) {
        posL[3] = 0.0f;
    }
    else if (strcmp(type, "SPOT") == 0) {
        posL[3] = 1.0f;
    }
    else if (strcmp(type, "POINT") == 0) {
        posL[3] = 1.0f;


//        glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
        glMaterialf(GL_FRONT,GL_SHININESS,50.0);
    }

    switch(numLight) {
        case 0 : glLightfv(GL_LIGHT0, GL_POSITION, posL);
                 glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
                 glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
                 glEnable(GL_LIGHT0);
                 break;
        case 1 : glLightfv(GL_LIGHT1, GL_POSITION, posL);
                 glLightfv(GL_LIGHT1, GL_AMBIENT, amb);
                 glLightfv(GL_LIGHT1, GL_DIFFUSE, diff);
                 glEnable(GL_LIGHT1);
                 break;
        case 2 : glLightfv(GL_LIGHT2, GL_POSITION, posL);
                 glLightfv(GL_LIGHT2, GL_AMBIENT, amb);
                 glLightfv(GL_LIGHT2, GL_DIFFUSE, diff);
                 glEnable(GL_LIGHT2);
                 break;
    }

//    if (strcmp(type, "POINT") == 0) {
//        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
        res = 1;
//    }

    return res;
}
