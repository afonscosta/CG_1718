#ifndef GENERATOR_PATCH_H
#define GENERATOR_PATCH_H

#include <string>
#include "Point.h"
#include "generator.h"
#include <math.h>
using std::vector;

class Patch {
    int tess;
    int num_patches;
    int num_ctrl_pt;
    vector<int> indices;
    vector<Point> control_points;
    vector<Point> curve_points;

private:
    void split(const std::string& s, char delim,vector<std::string>& v);

public:
    vector<Point> getCurve_points() const;

    void parse_patch(char* file_name);

    void generateBezier();

    void setTesselation(int i);

    void multMatrixVector(float *m, float *v, float *res);

    void calcBezierPoints(Point *p0, Point *p1, Point *p2, Point *p3);

    float calcBezierPoint(float *P, float *M, float U[4], float V[4]);

    void calcPointsSurface(float *M, float *Px, float *Py, float *Pz);
};


#endif //GENERATOR_PATCH_H
