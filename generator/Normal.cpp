//
// Created by daniel on 14/05/18.
//

#include "Normal.h"

Point cross(Point a, Point b) {

    double x, y, z;

    x = a.getY() * b.getZ() - a.getZ() * b.getY();
    y = a.getZ() * b.getX() - a.getX() * b.getZ();
    z = a.getX() * b.getY() - a.getY() * b.getX();

    Point p;
    p.setPoint(x, y, z);

    return p;
}

Point normalize(Point a) {

    double l = sqrt(pow(a.getX(), 2) + pow(a.getY(), 2) + pow(a.getZ(), 2));
    a.setPoint(a.getX()/l, a.getY()/l, a.getZ()/l);

    return a;
}

Point difference(Point a, Point b){
    Point res;

    res.setPoint(a.getX() - b.getX(), a.getY() - b.getY(), a.getZ() - b.getZ());

    return res;
}