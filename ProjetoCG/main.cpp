#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <vector>

using std::ofstream;
using std::vector;

class Point {
    float x, y, z;
public:
    void setPoint (float, float, float);
    float getX() { return x; }
    float getY() { return y; }
    float getZ() { return z; }
};

void Point::setPoint (float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

int writeFile (vector <Point> points)
{
    ofstream myfile;
    myfile.open ("plane.txt");
    if (myfile.is_open()) {
        for (int i = 0; i < points.size(); i++) {
            myfile << points[i].getX() << " " << points[i].getY() << " " << points[i].getZ() << "\n";
        }
        myfile.close();
    }
    return 0;
}

vector<Point> plane_generate_points(vector <Point> points, float a) {
    Point p;
    p.setPoint(-a, 0, a);
    points.push_back(p);
    p.setPoint(a, 0, a);
    points.push_back(p);
    p.setPoint(a, 0, -a);
    points.push_back(p);
    p.setPoint(a, 0, -a);
    points.push_back(p);
    p.setPoint(-a, 0, -a);
    points.push_back(p);
    p.setPoint(-a, 0, a);
    points.push_back(p);
    return points;
}

void box_generate_points(Point points[], float x, float y, float z) {

}


int main(int argc, char **argv) {
    if (argc == 3) {
        if (strcmp(argv[1], "plane") == 0) {
            vector <Point> points;
            points = plane_generate_points(points, strtof(argv[2],NULL)/2);
            writeFile(points);
        }
    }
//    else if (argc == 5) {
//        if (strcmp(argv[1], "box") == 0) {
//            Point points[6];
//            box_generate_points(points, atoi(argv[2])/2, atoi(argv[3])/2, atoi(argv[4])/2);
//            writeFile(points);
//        }
//    }
    return 0;
}