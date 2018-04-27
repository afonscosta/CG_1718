//
// Created by Marco Silva on 27/04/2018.
//

#ifndef GENERATOR_PATCH_H
#define GENERATOR_PATCH_H


#include "Point.h"
#include "generator.h"

class Patch {
public:

    void split(const std::string& s, char delim,vector<std::string>& v);

    void parse_patch(char* file_name);

private:

    int num_patches;
    int num_ctrl_pt;
    vector<int>indices;
    vector<Point>control_points;

};


#endif //GENERATOR_PATCH_H
