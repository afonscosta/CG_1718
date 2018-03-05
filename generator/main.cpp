#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <stdio.h>

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
    else if (strcmp(fig, "box") == 0) {
        myfile.open("box.3d");
        if (myfile.is_open()) {
            for (int i = 0; i < points.size(); i++) {
                myfile << points[i].getX() << " " << points[i].getY() << " " << points[i].getZ() << "\n";
            }
            myfile.close();
        }
    }
    else if (strcmp(fig, "cone") == 0) {
        myfile.open("cone.3d");
        if (myfile.is_open()) {
            for (int i = 0; i < points.size(); i++) {
                myfile << points[i].getX() << " " << points[i].getY() << " " << points[i].getZ() << "\n";
            }
            myfile.close();
        }
    }
    else if (strcmp(fig, "sphere") == 0) {
        myfile.open("sphere.3d");
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
    p.setPoint(x, -y, z);
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

vector <Point> cone_generate_points(vector <Point> points, float radius, float height, float slices, float stacks) {
    double increment = (2 * M_PI) / slices;

    double angle = 0;

    double height_aux = height / 2;

    Point p;

    for (int i = 0; i < slices; i++){

        //faces
        p.setPoint(0, height_aux, 0);
        points.push_back(p);
        p.setPoint(sin(angle) * radius, -height_aux, cos(angle) * radius);
        points.push_back(p);
        p.setPoint(sin(angle + increment) * radius, -height_aux, cos(angle + increment) * radius);
        points.push_back(p);



        //base
        p.setPoint(0, -height_aux, 0);
        points.push_back(p);
        p.setPoint(sin(angle + increment) * radius, -height_aux, cos(angle + increment) * radius);
        points.push_back(p);
        p.setPoint(sin(angle) * radius, -height_aux, cos(angle) * radius);
        points.push_back(p);


        angle += increment;
    }

    return points;
}


vector <Point> sphere_generate_points(vector <Point> points,float radius, int slices, int stacks) {

    Point p;

// put code to draw cone in here
    double increment1 = (2 * M_PI) / slices;
    double increment2 = M_PI / stacks;

    double BETA = (-M_PI) / 2;
    double ALFA = 0;

    //z = radius * cos(BETA) * cos(ALFA)
    //x = radius * cos(BETA) * sin(ALFA)
    //y = radius * cos(BETA)

    for (int i = 0; i < stacks; i++){

        for (int a = 0; a < slices; a++){

            //triangulo 1
            p.setPoint(radius * cos(BETA) * sin(ALFA + increment1), radius * sin(BETA), radius * cos(BETA) * cos(ALFA + increment1));
            points.push_back(p);
            p.setPoint(radius * cos(BETA + increment2) * sin(ALFA) , radius * sin(BETA + increment2) , radius * cos(BETA + increment2) * cos(ALFA));
            points.push_back(p);
            p.setPoint(radius * cos(BETA) * sin(ALFA) , radius * sin(BETA) , radius * cos(BETA) * cos(ALFA));
            points.push_back(p);

            //triangulo 2
            p.setPoint(radius * cos(BETA + increment2) * sin(ALFA) , radius * sin(BETA + increment2) , radius * cos(BETA + increment2) * cos(ALFA));
            points.push_back(p);
            p.setPoint(radius * cos(BETA) * sin(ALFA + increment1) , radius * sin(BETA) , radius * cos(BETA) * cos(ALFA + increment1));
            points.push_back(p);
            p.setPoint(radius * cos(BETA + increment2) * sin(ALFA + increment1) , radius * sin(BETA + increment2) , radius * cos(BETA + increment2) * cos(ALFA + increment1));
            points.push_back(p);

            ALFA += increment1;
        }
        BETA += increment2;
    }
    return points;
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
        //falta colocar a receber o numero de divisoes
        if (strcmp(argv[1], "box") == 0) {
            points = box_generate_points(points, strtof(argv[2], NULL)/2, strtof(argv[3], NULL)/2, strtof(argv[4], NULL)/2);
            writeFile(points, argv[1]);
        }
        else if (strcmp(argv[1], "sphere") == 0) {
            points = sphere_generate_points(points, strtof(argv[2], NULL), strtof(argv[3], NULL), strtof(argv[4], NULL));
            writeFile(points, argv[1]);
        }
    }
    else if (argc == 6) {
        if (strcmp(argv[1], "cone") == 0) {
            points = cone_generate_points(points, strtof(argv[2], NULL), strtof(argv[3], NULL)/2, strtof(argv[4], NULL), strtof(argv[5], NULL));
            writeFile(points, argv[1]);
        }
    }

    return 0;
}