
#include "Model.h"
#include <stdio.h>
#include <cstring>

void Model::setEmission(char *emission) {
    Model::emission = emission;
}

void Model::setTexIDPrimitive(GLuint texIDPrimitive) {
    Model::texIDPrimitive = texIDPrimitive;
}

void Model::setPrimitive(vector<float> v, vector<float> n, vector<float> t, int nv) {

    nvertices = nv;

    glGenBuffers(1, &vertices);
    glBindBuffer(GL_ARRAY_BUFFER, vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * v.size(), &(v[0]), GL_STATIC_DRAW);

    glGenBuffers(1, &normals);
    glBindBuffer(GL_ARRAY_BUFFER,normals);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * n.size(), &(n[0]), GL_STATIC_DRAW);

    glGenBuffers(1, &texCoord);
    glBindBuffer(GL_ARRAY_BUFFER, texCoord);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * t.size(), &(t[0]), GL_STATIC_DRAW);

}

void Model::drawPrimitive() {

    float yellow[4] = {255.0 / 255.0, 204.0 / 255.0, 102.0 / 255.0, 1.0f};
    float black[4] = {0.2, 0.2, 0.2, 1.0f};
    float white[4] = {0.9, 0.9, 0.9, 1.0f};

//    glPushAttrib(GL_LIGHTING_BIT);

    if (emission != NULL && strcmp(emission, "yellow") == 0) {
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, yellow);
    }
    else if (emission != NULL && strcmp(emission, "white") == 0) {
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, white);
    }
    else {
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
    }

    glBindBuffer(GL_ARRAY_BUFFER, vertices);
    glVertexPointer(3, GL_FLOAT, 0,  0);

    glBindBuffer(GL_ARRAY_BUFFER, normals);
    glNormalPointer(GL_FLOAT, 0, 0);

    glBindTexture(GL_TEXTURE_2D, texIDPrimitive);
    glBindBuffer(GL_ARRAY_BUFFER, texCoord);
    glTexCoordPointer(2, GL_FLOAT, 0, 0);



    glEnable(GL_LIGHTING);
    glDrawArrays(GL_TRIANGLES, 0, nvertices);
    glDisable(GL_LIGHTING);

//    glPopAttrib();

    glBindTexture(GL_TEXTURE_2D, 0);
}


