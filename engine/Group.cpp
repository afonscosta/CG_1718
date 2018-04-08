//
// Created by afonscosta on 08-04-2018.
//

#include <GL/gl.h>
#include "Group.h"

void Group::addOrder(char c) {
    order.push_back(c);
}

void Group::setTranslate(Point p) {
    translate.setPoint(p.getX(), p.getY(), p.getZ());
}

void Group::setRotate(float a, Point p) {
    angle = a;
    rotate.setPoint(p.getX(), p.getY(), p.getZ());
}

void Group::setScale(Point p) {
    scale.setPoint(p.getX(), p.getY(), p.getZ());
}

void Group::setModels(vector<Model> ms) {
    models = ms; //Assim fica-se com acesso exterior aos models
}

void Group::addGroup(Group* g) {
    groups.push_back(g); //Assim fica-se com acesso exterior aos grupos
}

void Group::doTranslate() {
    glTranslatef(translate.getX(), translate.getY(), translate.getZ());
}

void Group::doRotate() {
    glRotatef(angle, rotate.getX(), rotate.getY(), rotate.getZ());
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

void Group::drawGroup() {
    glPushMatrix();
    for (auto &it : order) {
        if (it == 't')
            doTranslate();
        else if (it == 'r')
            doRotate();
        else if (it == 's')
            doScale();
    }
    drawModels();
    for (auto &it : groups) {
        it->drawGroup();
    }

    glPopMatrix();
}
