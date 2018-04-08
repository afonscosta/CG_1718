//
// Created by afonscosta on 08-04-2018.
//

#include <GL/gl.h>
#include "Model.h"

void Model::setPrimitive(vector<Point> pri) {
    Point p;
    for (auto &it : pri) {
        p.setPoint(it.getX(), it.getY(), it.getZ());
        primitive.push_back(p);
    }
}

void Model::drawPrimitive() {

    int i = 0;
    float buffer_points[9];

    for (auto &it : primitive) {

        buffer_points[i * 3 + 0] = it.getX();
        buffer_points[i * 3 + 1] = it.getY();
        buffer_points[i * 3 + 2] = it.getZ();

        i++;

        if (i == 3) {

            glBegin(GL_TRIANGLES);
            glVertex3f(buffer_points[0], buffer_points[1], buffer_points[2]);
            glVertex3f(buffer_points[3], buffer_points[4], buffer_points[5]);
            glVertex3f(buffer_points[6], buffer_points[7], buffer_points[8]);
            glEnd();

            i = 0;

        }

    }
}
