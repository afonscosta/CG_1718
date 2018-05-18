
#ifndef ENGINE_MODEL_H
#define ENGINE_MODEL_H

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include "Point.h"
#include <vector>
using std::vector;


class Model {

private:
    GLuint vertices;
    GLuint normals;
    GLuint texCoord;
    GLuint texIDPrimitive;
    int nvertices;
    float emission[4];
    float diffuse[4];
    float specular[4];

public:
    void setTexIDPrimitive(GLuint texIDPrimitive);
    void setPrimitive(vector<float> v, vector<float> n, vector<float> t, int nvertices);
    void drawPrimitive();
    void setEmission(float emission[4]);
    void setDiffuse(float diffuse[4]);
    void setSpecular(float specular[4]);
};


#endif //ENGINE_MODEL_H