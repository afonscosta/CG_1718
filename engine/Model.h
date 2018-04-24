//
// Created by afonscosta on 08-04-2018.
//

#ifndef ENGINE_MODEL_H
#define ENGINE_MODEL_H


#include "Point.h"
#include <vector>
using std::vector;


class Model {

    GLuint buffers[1];
    int nvertices;

public:
    void setPrimitive(vector<float> points, int nvertices);
    void drawPrimitive();
};


#endif //ENGINE_MODEL_H
