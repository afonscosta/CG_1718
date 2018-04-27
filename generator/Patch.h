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

    void calcBezierPoints(int tess, Point p0[][4], Point p1[][4], Point p2[][4], Point p3[][4]) {
};


#endif //GENERATOR_PATCH_H
