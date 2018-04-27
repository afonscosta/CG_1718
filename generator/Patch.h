#ifndef GENERATOR_PATCH_H
#define GENERATOR_PATCH_H


#include "Point.h"
#include "generator.h"
using std::vector;

class Patch {
    int num_patches;
    int num_ctrl_pt;
    vector<Point> indices;
    vector<Point> control_points;

private:
    void split(const std::string& s, char delim,vector<std::string>& v);

public:
    void parse_patch(char* file_name);

    int getNum_patches() const;

    int getNum_ctrl_pt() const;

    const vector<Point> &getIndices() const;

    const vector<Point> &getControl_points() const;

    void setNum_patches(int num_patches);

    void setNum_ctrl_pt(int num_ctrl_pt);

    void setIndices(const vector<Point> &indices);

    void setControl_points(const vector<Point> &control_points);

    vector<Point> generateBezier();

};


#endif //GENERATOR_PATCH_H
