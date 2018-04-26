//
// Created by Marco Silva on 25/04/2018.
//

#include "Translate.h"
#include <math.h>
#define POINT_COUNT 5

void Translate::multMatrixVector(float *m, float *v, float *res) {

    for (int j = 0; j < 4; ++j) {
        res[j] = 0;
        for (int k = 0; k < 4; ++k) {
            res[j] += v[k] * m[j * 4 + k];
        }
    }

}

void Translate::getCatmullRomPoint(float t, float *p0, float *p1, float *p2, float *p3, float *pos, float *deriv) {

    // catmull-rom matrix
    float m[4][4] = {	{-0.5f,  1.5f, -1.5f,  0.5f},
                         { 1.0f, -2.5f,  2.0f, -0.5f},
                         {-0.5f,  0.0f,  0.5f,  0.0f},
                         { 0.0f,  1.0f,  0.0f,  0.0f}};

    float p[4];

    float Ax[4];
    float Ay[4];
    float Az[4];

    // Compute A = M * P
    p[0] = p0[0];
    p[1] = p1[0];
    p[2] = p2[0];
    p[3] = p3[0];
    multMatrixVector((float *)m, p, Ax);

    p[0] = p0[1];
    p[1] = p1[1];
    p[2] = p2[1];
    p[3] = p3[1];
    multMatrixVector((float *)m, p, Ay);

    p[0] = p0[2];
    p[1] = p1[2];
    p[2] = p2[2];
    p[3] = p3[2];
    multMatrixVector((float *)m, p, Az);

    // Compute pos = T * A
    float t_vector[4] = {pow(t,3), pow(t,2), t, 1};
    pos[0] = t_vector[0] * Ax[0] + t_vector[1] * Ax[1] + t_vector[2] * Ax[2] + t_vector[3] * Ax[3];
    pos[1] = t_vector[0] * Ay[0] + t_vector[1] * Ay[1] + t_vector[2] * Ay[2] + t_vector[3] * Ay[3];
    pos[2] = t_vector[0] * Az[0] + t_vector[1] * Az[1] + t_vector[2] * Az[2] + t_vector[3] * Az[3];

    // compute deriv = T' * A
    float t_vector_derivated[4] = {3 * pow(t,2), 2 * t, 1, 0};
    deriv[0] = t_vector_derivated[0] * Ax[0] + t_vector_derivated[1] * Ax[1] + t_vector_derivated[2] * Ax[2] + t_vector_derivated[3] * Ax[3];
    deriv[1] = t_vector_derivated[0] * Ay[0] + t_vector_derivated[1] * Ay[1] + t_vector_derivated[2] * Ay[2] + t_vector_derivated[3] * Ay[3];
    deriv[2] = t_vector_derivated[0] * Az[0] + t_vector_derivated[1] * Az[1] + t_vector_derivated[2] * Az[2] + t_vector_derivated[3] * Az[3];

}

// given  global t, returns the point in the curve
void Translate::getGlobalCatmullRomPoint(float gt, float *pos, float *deriv) {

    float t = gt * points.size(); // this is the real global t
    int index = floor(t);  // which segment
    t = t - index; // where within  the segment

    // indices store the points
    int indices[4];
    indices[0] = (index + points.size()-1) % points.size();
    indices[1] = (indices[0]+1) % points.size();
    indices[2] = (indices[1]+1) % points.size();
    indices[3] = (indices[2]+1) % points.size();

    // Points that make up the loop for catmull-rom interpolation
    float p[points.size()][3];

    for (int i = 0; i < points.size(); i++){
        p[i][0] = points.at(i).getX();
        p[i][1] = points.at(i).getY();
        p[i][2] = points.at(i).getZ();
    }

    getCatmullRomPoint(t, p[indices[0]], p[indices[1]], p[indices[2]], p[indices[3]], pos, deriv);
}

void Translate::renderCatmullRomCurve() {

// desenhar a curva usando segmentos de reta - GL_LINE_LOOP

    float pos[3];
    float deriv[3];

    glBegin(GL_LINE_LOOP);
    for (float i = 0; i < 1; i += 0.01){
        getGlobalCatmullRomPoint(i, pos, deriv);
        glVertex3f(pos[0], pos[1], pos[2]);
    }
    glEnd();
}

void Translate::setTranslate(float time, vector<Point> points) {
    this->time = time;
    this->points = points;
}

void Translate::doTranslate(){

    float pos[3];
    float deriv[3];

    renderCatmullRomCurve();

    //regra de 3 simples para que o tempo dado ao getGlobalCatmullRomPoint seja sempre entre 0 e 1
    float t = glutGet(GLUT_ELAPSED_TIME) / (time * 1000);
    //float gt = t / (time * 1000);

    //movimento do teapot
    getGlobalCatmullRomPoint(t, pos, deriv);
    glTranslatef(pos[0], pos[1], pos[2]);

}
