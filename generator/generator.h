//
// Created by Marco Silva on 09/04/2018.
//

#ifndef GENERATOR_GENERATOR_H
#define GENERATOR_GENERATOR_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <stdio.h>

#import "point.h"

using std::vector;

vector<Point> plane_generate_points(vector <Point> points, float a);
vector <Point> box_generate_points(vector <Point> points, float x, float y, float z, int divisions);
vector <Point> cone_generate_points(vector <Point> points, float radius, float height, float slices, float stacks);
vector <Point> sphere_generate_points(vector <Point> points,float radius, int slices, int stacks);
vector <Point> orbit_generate_points(vector <Point> points, float radius);
vector <Point> belt_generate_points(vector <Point> points, float radius_in, float radius_out);




#endif //GENERATOR_GENERATOR_H