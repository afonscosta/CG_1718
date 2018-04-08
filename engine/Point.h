//
// Created by afonscosta on 08-04-2018.
//

#ifndef ENGINE_POINT_H
#define ENGINE_POINT_H


class Point {
    float x, y, z;
public:
    void setPoint (float, float, float);
    float getX() { return x; }
    float getY() { return y; }
    float getZ() { return z; }
};


#endif //ENGINE_POINT_H
