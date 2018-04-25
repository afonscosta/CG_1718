//
// Created by afonscosta on 08-04-2018.
//

#include "Model.h"

void Model::setPrimitive(vector<float> points, int nvertices) {

    glGenBuffers(1, &buffers[0]);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * points.size(), &(points[0]), GL_STATIC_DRAW);

}

void Model::drawPrimitive() {

    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);

    glVertexPointer(3,GL_FLOAT,0,0);

    glDrawArrays(GL_TRIANGLES, 0, nvertices);
}