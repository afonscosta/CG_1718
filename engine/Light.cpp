
#include "Light.h"

char *Light::getType() const {
    return type;
}

void Light::setType(char *type) {
    Light::type = type;
}

void Light::setPos(const Point &pos) {
    Light::pos = pos;
}

void Light::turnOnLight(int numLight) {

    GLfloat amb[4] = {0.1, 0.1, 0.1, 1.0};
    GLfloat diff[4] = {5.0, 5.0, 5.0, 1.0};
    GLfloat posL[4] = { pos.getX(), pos.getY(), pos.getZ() };
    GLfloat spotDir[3] = {0.0, 0.0, -1.0};

    if (strcmp(type, "DIRECTIONAL") == 0) {
        posL[3] = 0.0f;
    }
    else if (strcmp(type, "SPOT") == 0) {
        posL[3] = 1.0f;
    }
    else if (strcmp(type, "POINT") == 0) {
        posL[3] = 1.0f;

    }

    switch(numLight) {
        case 0 : glLightfv(GL_LIGHT0, GL_POSITION, posL);
                 glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
                 glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
                 if (strcmp(type, "SPOT") == 0) {
                     glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDir);
                     glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 2.0);
                     glLightf(GL_LIGHT0,GL_SPOT_EXPONENT, 0.0);
                 }
                 glEnable(GL_LIGHT0);
                 break;
        case 1 : glLightfv(GL_LIGHT1, GL_POSITION, posL);
                 glLightfv(GL_LIGHT1, GL_AMBIENT, amb);
                 glLightfv(GL_LIGHT1, GL_DIFFUSE, diff);
                 if (strcmp(type, "SPOT") == 0) {
                     glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDir);
                     glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 2.0);
                     glLightf(GL_LIGHT1,GL_SPOT_EXPONENT, 0.0);
                 }
                 glEnable(GL_LIGHT1);
                 break;
        case 2 : glLightfv(GL_LIGHT2, GL_POSITION, posL);
                 glLightfv(GL_LIGHT2, GL_AMBIENT, amb);
                 glLightfv(GL_LIGHT2, GL_DIFFUSE, diff);
                 if (strcmp(type, "SPOT") == 0) {
                     glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotDir);
                     glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 2.0);
                     glLightf(GL_LIGHT2,GL_SPOT_EXPONENT, 0.0);
                 }
                 glEnable(GL_LIGHT2);
                 break;
        case 3 : glLightfv(GL_LIGHT3, GL_POSITION, posL);
                 glLightfv(GL_LIGHT3, GL_AMBIENT, amb);
                 glLightfv(GL_LIGHT3, GL_DIFFUSE, diff);
                 if (strcmp(type, "SPOT") == 0) {
                     glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spotDir);
                     glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 2.0);
                     glLightf(GL_LIGHT3,GL_SPOT_EXPONENT, 0.0);
                 }
                 glEnable(GL_LIGHT3);
                 break;
        case 4 : glLightfv(GL_LIGHT4, GL_POSITION, posL);
                 glLightfv(GL_LIGHT4, GL_AMBIENT, amb);
                 glLightfv(GL_LIGHT4, GL_DIFFUSE, diff);
                if (strcmp(type, "SPOT") == 0) {
                    glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, spotDir);
                    glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, 2.0);
                    glLightf(GL_LIGHT4,GL_SPOT_EXPONENT, 0.0);
                }
                 glEnable(GL_LIGHT4);
                 break;
        case 5 : glLightfv(GL_LIGHT5, GL_POSITION, posL);
                 glLightfv(GL_LIGHT5, GL_AMBIENT, amb);
                 glLightfv(GL_LIGHT5, GL_DIFFUSE, diff);
                if (strcmp(type, "SPOT") == 0) {
                    glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, spotDir);
                    glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, 2.0);
                    glLightf(GL_LIGHT5,GL_SPOT_EXPONENT, 0.0);
                }
                 glEnable(GL_LIGHT5);
                 break;
        case 6 : glLightfv(GL_LIGHT6, GL_POSITION, posL);
                 glLightfv(GL_LIGHT6, GL_AMBIENT, amb);
                 glLightfv(GL_LIGHT6, GL_DIFFUSE, diff);
                if (strcmp(type, "SPOT") == 0) {
                    glLightfv(GL_LIGHT6, GL_SPOT_DIRECTION, spotDir);
                    glLightf(GL_LIGHT6, GL_SPOT_CUTOFF, 2.0);
                    glLightf(GL_LIGHT6,GL_SPOT_EXPONENT, 0.0);
                }
                 glEnable(GL_LIGHT6);
                 break;
        case 7 : glLightfv(GL_LIGHT7, GL_POSITION, posL);
                 glLightfv(GL_LIGHT7, GL_AMBIENT, amb);
                 glLightfv(GL_LIGHT7, GL_DIFFUSE, diff);
                if (strcmp(type, "SPOT") == 0) {
                    glLightfv(GL_LIGHT7, GL_SPOT_DIRECTION, spotDir);
                    glLightf(GL_LIGHT7, GL_SPOT_CUTOFF, 2.0);
                    glLightf(GL_LIGHT7,GL_SPOT_EXPONENT, 0.0);
                }
                 glEnable(GL_LIGHT7);
                 break;
    }

}
