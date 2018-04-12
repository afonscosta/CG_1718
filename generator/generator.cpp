//
// Created by Marco Silva on 09/04/2018.
//

#include "generator.h"

using std::ofstream;
using std::vector;


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

vector <Point> box_generate_points(vector <Point> points, float x, float y, float z, int divisions) {
    Point p;

    double increment_x = x / divisions;
    double increment_y = y / divisions;
    double increment_z = z / divisions;

    x = x / 2;
    y = y / 2;
    z = z / 2;

    double x_aux;
    double y_aux;
    double z_aux;

    //face frontal
    x_aux = -x;
    y_aux = -y;
    z_aux = z;

    //ciclo de desenho da face frontal
    for (int i = 0; i < divisions; i++){

        for (int j = 0; j < divisions; j++){

            p.setPoint(x_aux, y_aux, z_aux);
            points.push_back(p);
            p.setPoint(x_aux + increment_x, y_aux, z_aux);
            points.push_back(p);
            p.setPoint(x_aux, y_aux + increment_y, z_aux );
            points.push_back(p);

            p.setPoint(x_aux, y_aux + increment_y, z_aux );
            points.push_back(p);
            p.setPoint(x_aux + increment_x, y_aux, z_aux);
            points.push_back(p);
            p.setPoint(x_aux + increment_x, y_aux + increment_y, z_aux );
            points.push_back(p);

            x_aux += increment_x;
        }

        y_aux += increment_y;
        x_aux = -x;
    }

    //face traseira
    x_aux = x;
    y_aux = -y;
    z_aux = -z;

    //ciclo de desenho da face traseira
    for (int i = 0; i < divisions; i++){

        for (int j = 0; j < divisions; j++){

            p.setPoint(x_aux, y_aux, z_aux);
            points.push_back(p);
            p.setPoint(x_aux - increment_x, y_aux, z_aux);
            points.push_back(p);
            p.setPoint(x_aux ,y_aux + increment_y ,z_aux );
            points.push_back(p);

            p.setPoint(x_aux, y_aux + increment_y, z_aux );
            points.push_back(p);
            p.setPoint(x_aux - increment_x, y_aux, z_aux);
            points.push_back(p);
            p.setPoint(x_aux - increment_x, y_aux + increment_y, z_aux );
            points.push_back(p);

            x_aux -= increment_x;
        }

        y_aux += increment_y;
        x_aux = x;
    }

    //face de cima
    x_aux = -x;
    y_aux = y;
    z_aux = z;

    //ciclo de desenho da face de cima
    for (int i = 0; i < divisions; i++){

        for (int j = 0; j < divisions; j++){

            p.setPoint(x_aux, y_aux, z_aux);
            points.push_back(p);
            p.setPoint(x_aux + increment_x, y_aux, z_aux);
            points.push_back(p);
            p.setPoint(x_aux, y_aux, z_aux - increment_z );
            points.push_back(p);

            p.setPoint(x_aux, y_aux, z_aux - increment_z );
            points.push_back(p);
            p.setPoint(x_aux + increment_x, y_aux, z_aux);
            points.push_back(p);
            p.setPoint(x_aux + increment_x, y_aux, z_aux - increment_z );
            points.push_back(p);

            x_aux += increment_x;
        }

        z_aux -= increment_z;
        x_aux = -x;
    }

    //face de baixo
    x_aux = -x;
    y_aux = -y;
    z_aux = -z;

    //ciclo de desenho da face de baixo
    for (int i = 0; i < divisions; i++){

        for (int j = 0; j < divisions; j++){

            p.setPoint(x_aux, y_aux, z_aux);
            points.push_back(p);
            p.setPoint(x_aux + increment_x, y_aux, z_aux);
            points.push_back(p);
            p.setPoint(x_aux, y_aux, z_aux + increment_z );
            points.push_back(p);

            p.setPoint(x_aux, y_aux, z_aux + increment_z );
            points.push_back(p);
            p.setPoint(x_aux + increment_x, y_aux, z_aux);
            points.push_back(p);
            p.setPoint(x_aux + increment_x, y_aux, z_aux + increment_z );
            points.push_back(p);

            x_aux += increment_x;
        }

        z_aux += increment_z;
        x_aux = -x;
    }

    //face da direita
    x_aux = x;
    y_aux = -y;
    z_aux = z;

    //ciclo de desenho da face da direita
    for (int i = 0; i < divisions; i++){

        for (int j = 0; j < divisions; j++){

            p.setPoint(x_aux, y_aux, z_aux);
            points.push_back(p);
            p.setPoint(x_aux, y_aux, z_aux - increment_z);
            points.push_back(p);
            p.setPoint(x_aux, y_aux + increment_y, z_aux );
            points.push_back(p);

            p.setPoint(x_aux, y_aux + increment_y, z_aux );
            points.push_back(p);
            p.setPoint(x_aux, y_aux, z_aux - increment_z);
            points.push_back(p);
            p.setPoint(x_aux, y_aux + increment_y, z_aux - increment_z );
            points.push_back(p);

            z_aux -= increment_z;
        }

        y_aux += increment_y;
        z_aux = z;
    }

    //face da esquerda
    x_aux = -x;
    y_aux = -y;
    z_aux = -z;

    //ciclo de desenho da face da esquerda
    for (int i = 0; i < divisions; i++){

        for (int j = 0; j < divisions; j++){

            p.setPoint(x_aux, y_aux, z_aux);
            points.push_back(p);
            p.setPoint(x_aux, y_aux, z_aux + increment_z);
            points.push_back(p);
            p.setPoint(x_aux, y_aux + increment_y, z_aux );
            points.push_back(p);

            p.setPoint(x_aux, y_aux + increment_y, z_aux );
            points.push_back(p);
            p.setPoint(x_aux, y_aux, z_aux + increment_z);
            points.push_back(p);
            p.setPoint(x_aux, y_aux + increment_y, z_aux + increment_z );
            points.push_back(p);

            z_aux += increment_z;
        }

        y_aux += increment_y;
        z_aux = -z;
    }

    return points;
}

vector <Point> cone_generate_points(vector <Point> points, float radius, float height, float slices, float stacks) {

    Point p;

    double increment = (2 * M_PI) / slices;
    double height_aux = height / 2;
    double height_increment = height / stacks;
    double radius_decrement = radius / stacks;
    double height_now = -height_aux;
    double radius_now = radius;
    double radius_next = radius_now - radius_decrement;
    double height_next = height_increment + height_now;

    for (int j = 0; j < stacks; j++){

        for (int i = 0; i < slices; i++) {

            p.setPoint(radius_now * sin(increment * i), height_now, radius_now * cos(increment * i) );
            points.push_back(p);
            p.setPoint(radius_now * sin(increment * (i + 1)), height_now, radius_now * cos(increment * (i + 1)) );
            points.push_back(p);
            p.setPoint(radius_next * sin(increment * i), height_next, radius_next * cos(increment * i ));
            points.push_back(p);

            p.setPoint(radius_next * sin(increment * i), height_next, radius_next * cos(increment * i ));
            points.push_back(p);
            p.setPoint(radius_now * sin(increment * (i + 1)), height_now, radius_now * cos(increment * (i + 1)) );
            points.push_back(p);
            p.setPoint(radius_next * sin(increment * (i + 1)) ,height_next ,radius_next * cos(increment * (i + 1)) );
            points.push_back(p);

        }

        height_now = height_next;
        height_next += height_increment;

        radius_now = radius_next;
        radius_next -= radius_decrement;
    }

    for (int a = 0; a < slices; a++) {

        //face inferior
        p.setPoint(0, -height_aux, 0);
        points.push_back(p);
        p.setPoint(sin(increment * (a + 1)) * radius, -height_aux, cos(increment * (a + 1)) * radius);
        points.push_back(p);
        p.setPoint(sin(increment * a) * radius, -height_aux, cos(increment * a) * radius);
        points.push_back(p);

    }

    return points;
}


vector <Point> sphere_generate_points(vector <Point> points,float radius, int slices, int stacks) {

    Point p;

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
            p.setPoint(radius * cos(BETA + increment2) * sin(ALFA), radius * sin(BETA + increment2), radius * cos(BETA + increment2) * cos(ALFA));
            points.push_back(p);
            p.setPoint(radius * cos(BETA) * sin(ALFA), radius * sin(BETA), radius * cos(BETA) * cos(ALFA));
            points.push_back(p);

            //triangulo 2
            p.setPoint(radius * cos(BETA + increment2) * sin(ALFA), radius * sin(BETA + increment2), radius * cos(BETA + increment2) * cos(ALFA));
            points.push_back(p);
            p.setPoint(radius * cos(BETA) * sin(ALFA + increment1), radius * sin(BETA), radius * cos(BETA) * cos(ALFA + increment1));
            points.push_back(p);
            p.setPoint(radius * cos(BETA + increment2) * sin(ALFA + increment1), radius * sin(BETA + increment2), radius * cos(BETA + increment2) * cos(ALFA + increment1));
            points.push_back(p);

            ALFA += increment1;
        }
        BETA += increment2;
    }
    return points;
}

vector <Point> orbit_generate_points(vector <Point> points, float radius){

    Point p;

    int sides = 300;
    float increment = (2*M_PI) / sides;

    for (int i = 0; i  < sides; i += 2){

        p.setPoint(radius * sin(increment * i), 0, radius * cos(increment * i));
        points.push_back(p);
        p.setPoint(radius * sin(increment * (i + 1)), 0, radius * cos(increment * (i + 1)));
        points.push_back(p);
        p.setPoint(radius * sin(increment * (i + 2)), 0, radius * cos(increment * (i + 2)));
        points.push_back(p);

    }

    return points;
}

vector <Point> belt_generate_points(vector <Point> points, float radius_in, float radius_out){

    Point p;

    int sides = 300;
    float increment = (2*M_PI) / sides;

    for (int i = 0; i  < sides; i++){

        p.setPoint(radius_in * sin(increment * i), 0, radius_in * cos(increment * i));
        points.push_back(p);
        p.setPoint(radius_out * sin(increment * i), 0, radius_out * cos(increment * i));
        points.push_back(p);
        p.setPoint(radius_out * sin(increment * (i + 1)), 0, radius_out * cos(increment * (i + 1)));
        points.push_back(p);

        p.setPoint(radius_in * sin(increment * i), 0, radius_in * cos(increment * i));
        points.push_back(p);
        p.setPoint(radius_out * sin(increment * (i + 1)), 0, radius_out * cos(increment * (i + 1)));
        points.push_back(p);
        p.setPoint(radius_in * sin(increment * (i + 1)), 0, radius_in * cos(increment * (i + 1)));
        points.push_back(p);

    }

    return points;
}