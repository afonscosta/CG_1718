
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

    GLuint vertices;
    GLuint normals;
    GLuint texCoord;
    GLuint texIDPrimitive;

private:
    int nvertices;

public:
    void setTexIDPrimitive(GLuint texIDPrimitive);
    void setPrimitive(vector<float> v, vector<float> n, vector<float> t, int nvertices);
    void drawPrimitive();
};


#endif //ENGINE_MODEL_H