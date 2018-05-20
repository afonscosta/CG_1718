
#include "Model.h"
#include <stdio.h>
#include <cstring>

void Model::setEmission(float emission[4]) {
    Model::emission[0] = emission[0];
    Model::emission[1] = emission[1];
    Model::emission[2] = emission[2];
    Model::emission[3] = emission[3];
}

void Model::setDiffuse(float diffuse[4]) {
    Model::diffuse[0] = diffuse[0];
    Model::diffuse[1] = diffuse[1];
    Model::diffuse[2] = diffuse[2];
    Model::diffuse[3] = diffuse[3];
}

void Model::setSpecular(float specular[4]) {
    Model::specular[0] = specular[0];
    Model::specular[1] = specular[1];
    Model::specular[2] = specular[2];
    Model::specular[3] = specular[3];
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

    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 100.0);
    glMaterialfv(GL_FRONT, GL_EMISSION, emission);



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



    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
}


