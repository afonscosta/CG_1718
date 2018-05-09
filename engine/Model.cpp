
#include "Model.h"
#include <stdio.h>

void Model::setTexIDPrimitive(GLuint texIDPrimitive) {
    Model::texIDPrimitive = texIDPrimitive;
}

void Model::setPrimitive(vector<float> v, vector<float> t, int nv) {

    nvertices = nv;

    glGenBuffers(1, &vertices);
    glBindBuffer(GL_ARRAY_BUFFER, vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * v.size(), &(v[0]), GL_STATIC_DRAW);

    glGenBuffers(1, &texCoord);
    glBindBuffer(GL_ARRAY_BUFFER, texCoord);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * t.size(), &(t[0]), GL_STATIC_DRAW);

}

void Model::drawPrimitive() {

    glBindBuffer(GL_ARRAY_BUFFER, vertices);
    glVertexPointer(3,GL_FLOAT,0,0);

    glBindTexture(GL_TEXTURE_2D, texIDPrimitive);
    glBindBuffer(GL_ARRAY_BUFFER, texCoord);
    glTexCoordPointer(2, GL_FLOAT, 0, 0);

    glDrawArrays(GL_TRIANGLES, 0, nvertices);

    glBindTexture(GL_TEXTURE_2D, 0);
}

