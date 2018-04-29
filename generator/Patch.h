#ifndef GENERATOR_PATCH_H
#define GENERATOR_PATCH_H


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
    void setCurve_points(vector<Point> curve_points);

    vector<Point> getCurve_points() const;

    void parse_patch(char* file_name);

    void generateBezier();

    void setTesselation(int i);

    void multMatrixVector(float *m, float *v, float *res);

    void calcBezierPoints(Point *p0, Point *p1, Point *p2, Point *p3);

    float calcBezierPoint(float *P, float *M, float U[4], float V[4]);

    void calcPointsSurface(float *M, float *P, float *curvePoints, float *pDouble);

    void multVectorMatrix(float *v, float *m, float *res);

    void multVectorPoints(float *v, float *points, float *res);

    void multPointsVector(float *points, float *v, float *res);
};


#endif //GENERATOR_PATCH_H
