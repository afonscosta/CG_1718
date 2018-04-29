
#ifndef GENERATOR_GENERATOR_H
#define GENERATOR_GENERATOR_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include "Point.h"

using std::vector;
using std::ofstream;

vector<Point> plane_generate_points(vector <Point> points, float a);
vector <Point> box_generate_points(vector <Point> points, float x, float y, float z, int divisions);
vector <Point> cone_generate_points(vector <Point> points, float radius, float height, float slices, float stacks);
vector <Point> sphere_generate_points(vector <Point> points,float radius, int slices, int stacks);
vector <Point> orbit_generate_points(vector <Point> points, float radius);
vector <Point> belt_generate_points(vector <Point> points, float radius_in, float radius_out);
vector <Point> torus_generate_points(vector <Point> points, float radius, float radius_torus, float stacks, int slices);




#endif //GENERATOR_GENERATOR_H