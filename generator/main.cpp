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

int writeFile (vector <Point> points, char* fig)
{
    ofstream myfile;
    if (strcmp(fig, "plane") == 0) {
        myfile.open("plane.3d");
        if (myfile.is_open()) {
            for (int i = 0; i < points.size(); i++) {
                myfile << points[i].getX() << " " << points[i].getY() << " " << points[i].getZ() << "\n";
            }
            myfile.close();
        }
    }
    if (strcmp(fig, "box") == 0) {
        myfile.open("box.3d");
        if (myfile.is_open()) {
            for (int i = 0; i < points.size(); i++) {
                myfile << points[i].getX() << " " << points[i].getY() << " " << points[i].getZ() << "\n";
            }
            myfile.close();
        }
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

vector <Point> box_generate_points(vector <Point> points, float x, float y, float z) {
    Point p;

    //Face de baixo
    p.setPoint(-x, -y, z);
    points.push_back(p);
    p.setPoint(-x, -y, -z);
    points.push_back(p);
    p.setPoint(x, -y, z);
    points.push_back(p);
    p.setPoint(x, -y, -z);
    points.push_back(p);
    p.setPoint(-x, -y, z);
    points.push_back(p);
    p.setPoint(-x, -y, -z);
    points.push_back(p);

    //Face de cima
    p.setPoint(-x, y, z);
    points.push_back(p);
    p.setPoint(x, y, z);
    points.push_back(p);
    p.setPoint(x, y, -z);
    points.push_back(p);
    p.setPoint(x, y, -z);
    points.push_back(p);
    p.setPoint(-x, y, -z);
    points.push_back(p);
    p.setPoint(-x, y, z);
    points.push_back(p);

    //Face frontal
    p.setPoint(x, y, z);
    points.push_back(p);
    p.setPoint(-x, -y, z);
    points.push_back(p);
    p.setPoint(x, -y, z);
    points.push_back(p);
    p.setPoint(x, y, z);
    points.push_back(p);
    p.setPoint(-x, y, z);
    points.push_back(p);
    p.setPoint(-x, -y, z);
    points.push_back(p);

    //Face traseira
    p.setPoint(-x, -y, -z);
    points.push_back(p);
    p.setPoint(x, y, -z);
    points.push_back(p);
    p.setPoint(x, -y, -z);
    points.push_back(p);
    p.setPoint(-x, -y, -z);
    points.push_back(p);
    p.setPoint(-x, y, -z);
    points.push_back(p);
    p.setPoint(x, y, -z);
    points.push_back(p);

    //Face lateral direita
    p.setPoint(x, -y, -z);
    points.push_back(p);
    p.setPoint(x, y, z);
    points.push_back(p);
    p.setPoint(x, -y, z);
    points.push_back(p);
    p.setPoint(x, -y, -z);
    points.push_back(p);
    p.setPoint(x, y, -z);
    points.push_back(p);
    p.setPoint(x, y, z);
    points.push_back(p);

    //Face lateral esquerda
    p.setPoint(-x, y, z);
    points.push_back(p);
    p.setPoint(-x, y, -z);
    points.push_back(p);
    p.setPoint(-x, -y, -z);
    points.push_back(p);
    p.setPoint(-x, y, z);
    points.push_back(p);
    p.setPoint(-x, -y, -z);
    points.push_back(p);
    p.setPoint(-x, -y, z);
    points.push_back(p);

    return points;
}

vector <Point> cone_generate_points(vector <Point> points, float bottom_radius, float height, float slices, float stacks) {

}


int main(int argc, char **argv) {
    vector <Point> points;
    if (argc == 3) {
        if (strcmp(argv[1], "plane") == 0) {
            points = plane_generate_points(points, strtof(argv[2],NULL)/2);
            writeFile(points, argv[1]);
        }
    }
    else if (argc == 5) {
        if (strcmp(argv[1], "box") == 0) {
            points = box_generate_points(points, strtof(argv[2], NULL)/2, strtof(argv[3], NULL)/2, strtof(argv[4], NULL)/2);
            writeFile(points, argv[1]);
        }
    }
    //codigo preparado para os argumentos do cone
    /*else if (argc == 6) {
        if (strcmp(argv[1], "cone") == 0) {
            points = cone_generate_points(points, strtof(argv[2], NULL), strtof(argv[3], NULL)/2, strtof(argv[4], NULL), strtof(argv[5], NULL));
            writeFile(points, argv[1]);
        }
    }*/
    return 0;
}
