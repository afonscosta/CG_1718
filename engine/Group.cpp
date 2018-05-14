#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#include <math.h>
#include <cstring>
#include "Group.h"


void Group::addOrder(char c) {
    order.push_back(c);
}

void Group::setTranslate(Translate t) {
    this->translate = t;
}

void Group::setRotate(float t, Point p, int tipo) {
    tipoRotate = tipo;
    paramRotate = t;
    rotate.setPoint(p.getX(), p.getY(), p.getZ());
}

void Group::setScale(Point p) {
    scale.setPoint(p.getX(), p.getY(), p.getZ());
}

void Group::setModels(vector<Model> ms) {
    models = ms;
}

void Group::setLights(const vector<Light> &lights) {
    Group::lights = lights;
}

void Group::addGroup(Group* g) {
    groups.push_back(g);
}

void Group::doTranslate(int curveOff) {
    translate.doTranslate(curveOff);
}

void Group::doRotate() {
    if (tipoRotate == 0)
        glRotatef(paramRotate , rotate.getX(), rotate.getY(), rotate.getZ());
    else if (tipoRotate == 1) {
        float t = (glutGet(GLUT_ELAPSED_TIME) % (int) (paramRotate * 1000));
        float gt = 360 * (t / (paramRotate * 1000));
        glRotatef(gt, rotate.getX(), rotate.getY(), rotate.getZ());
    }
}

void Group::doScale() {
    if (scale.getX() != 0 && scale.getY() != 0 && scale.getZ() != 0)
        glScalef(scale.getX(), scale.getY(), scale.getZ());
}

void Group::drawModels() {
    for (auto &it : models) {
        it.drawPrimitive();
    }
}

void Group::drawGroup(int curveOff) {
    glPushMatrix();
    for (auto &it : order) {
        if (it == 't')
            doTranslate(curveOff);
        else if (it == 'r')
            doRotate();
        else if (it == 's')
            doScale();
    }


    int hasPointLight = 0;

    for (int i = 0; i < lights.size(); i++) {
        hasPointLight += lights.at(i).turnOnLight(i);
    }

    drawModels();

    for (auto &it : groups) {
        it->drawGroup(curveOff);
    }

    glPopMatrix();
}

