
#include "generator.h"
#include "Normal.h"

using std::ofstream;
using std::vector;



vector<Point> plane_generate_points(vector <Point> points, float a) {
    Point p, normal;

    normal.setPoint(0, 1, 0);

    //Vertice
    p.setPoint(-a, 0, a);
    points.push_back(p);
    //Normal
    points.push_back(normal);
    //Texture
    p.setPoint(0, 0, 0);
    points.push_back(p);

    p.setPoint(a, 0, a);
    points.push_back(p);
    points.push_back(normal);
    p.setPoint(1, 0, 0);
    points.push_back(p);

    p.setPoint(a, 0, -a);
    points.push_back(p);
    points.push_back(normal);
    p.setPoint(1, 1, 1);
    points.push_back(p);

    p.setPoint(a, 0, -a);
    points.push_back(p);
    points.push_back(normal);
    p.setPoint(1, 1, 0);
    points.push_back(p);

    p.setPoint(-a, 0, -a);
    points.push_back(p);
    points.push_back(normal);
    p.setPoint(0, 1, 0);
    points.push_back(p);

    p.setPoint(-a, 0, a);
    points.push_back(p);
    points.push_back(normal);
    p.setPoint(0, 0, 0);
    points.push_back(p);

    return points;
}

vector <Point> box_generate_points(vector <Point> points, float x, float y, float z, int divisions) {
    Point p, normal;

    double increment_x = x / divisions;
    double increment_y = y / divisions;
    double increment_z = z / divisions;

    double increment_T = 1.0 / divisions;

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
    normal.setPoint(0, 0, 1);

    //ciclo de desenho da face frontal
    for (int i = 0; i < divisions; i++){

        for (int j = 0; j < divisions; j++){

            //Vertice
            p.setPoint(x_aux, y_aux, z_aux);
            points.push_back(p);
            //Normal
            points.push_back(normal);
            //Texture
            p.setPoint(j * increment_T, i * increment_T, 0);
            points.push_back(p);

            p.setPoint(x_aux + increment_x, y_aux, z_aux);
            points.push_back(p);
            points.push_back(normal);
            p.setPoint((j+1) * increment_T, i * increment_T, 0);
            points.push_back(p);

            p.setPoint(x_aux, y_aux + increment_y, z_aux );
            points.push_back(p);
            points.push_back(normal);
            p.setPoint(j * increment_T, (i+1) * increment_T, 0);
            points.push_back(p);


            p.setPoint(x_aux, y_aux + increment_y, z_aux );
            points.push_back(p);
            points.push_back(normal);
            p.setPoint(j * increment_T, (i+1) * increment_T, 0);
            points.push_back(p);

            p.setPoint(x_aux + increment_x, y_aux, z_aux);
            points.push_back(p);
            points.push_back(normal);
            p.setPoint((j+1) * increment_T, i * increment_T, 0);
            points.push_back(p);

            p.setPoint(x_aux + increment_x, y_aux + increment_y, z_aux );
            points.push_back(p);
            points.push_back(normal);
            p.setPoint((j+1) * increment_T, (i+1) * increment_T, 0);
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
    normal.setPoint(0, 0, -1);

    //ciclo de desenho da face traseira
    for (int i = 0; i < divisions; i++){

        for (int j = 0; j < divisions; j++){

            p.setPoint(x_aux, y_aux, z_aux);
            points.push_back(p);
            points.push_back(normal);
            p.setPoint(j * increment_T, i * increment_T, 0);
            points.push_back(p);

            p.setPoint(x_aux - increment_x, y_aux, z_aux);
            points.push_back(p);
            points.push_back(normal);
            p.setPoint((j+1) * increment_T, i * increment_T, 0);
            points.push_back(p);

            p.setPoint(x_aux ,y_aux + increment_y ,z_aux );
            points.push_back(p);
            points.push_back(normal);
            p.setPoint(j * increment_T, (i+1) * increment_T, 0);
            points.push_back(p);


            p.setPoint(x_aux, y_aux + increment_y, z_aux );
            points.push_back(p);
            points.push_back(normal);
            p.setPoint(j * increment_T, (i+1) * increment_T, 0);
            points.push_back(p);

            p.setPoint(x_aux - increment_x, y_aux, z_aux);
            points.push_back(p);
            points.push_back(normal);
            p.setPoint((j+1) * increment_T, i * increment_T, 0);
            points.push_back(p);

            p.setPoint(x_aux - increment_x, y_aux + increment_y, z_aux );
            points.push_back(p);
            points.push_back(normal);
            p.setPoint((j+1) * increment_T, (i+1) * increment_T, 0);
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
    normal.setPoint(0, 1, 0);

    //ciclo de desenho da face de cima
    for (int i = 0; i < divisions; i++){

        for (int j = 0; j < divisions; j++){

            p.setPoint(x_aux, y_aux, z_aux);
            points.push_back(p);
            points.push_back(normal);
            p.setPoint(j * increment_T, i * increment_T, 0);
            points.push_back(p);

            p.setPoint(x_aux + increment_x, y_aux, z_aux);
            points.push_back(p);
            points.push_back(normal);
            p.setPoint((j+1) * increment_T, i * increment_T, 0);
            points.push_back(p);

            p.setPoint(x_aux, y_aux, z_aux - increment_z );
            points.push_back(p);
            points.push_back(normal);
            p.setPoint(j * increment_T, (i+1) * increment_T, 0);
            points.push_back(p);


            p.setPoint(x_aux, y_aux, z_aux - increment_z );
            points.push_back(p);
            points.push_back(normal);
            p.setPoint(j * increment_T, (i+1) * increment_T, 0);
            points.push_back(p);

            p.setPoint(x_aux + increment_x, y_aux, z_aux);
            points.push_back(p);
            points.push_back(normal);
            p.setPoint((j+1) * increment_T, i * increment_T, 0);
            points.push_back(p);

            p.setPoint(x_aux + increment_x, y_aux, z_aux - increment_z );
            points.push_back(p);
            points.push_back(normal);
            p.setPoint((j+1) * increment_T, (i+1) * increment_T, 0);
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
    normal.setPoint(0, -1, 0);

    //ciclo de desenho da face de baixo
    for (int i = 0; i < divisions; i++){

        for (int j = 0; j < divisions; j++){

            p.setPoint(x_aux, y_aux, z_aux);
            points.push_back(p);
            points.push_back(normal);
            p.setPoint(j * increment_T, i * increment_T, 0);
            points.push_back(p);

            p.setPoint(x_aux + increment_x, y_aux, z_aux);
            points.push_back(p);
            points.push_back(normal);
            p.setPoint((j+1) * increment_T, i * increment_T, 0);
            points.push_back(p);

            p.setPoint(x_aux, y_aux, z_aux + increment_z );
            points.push_back(p);
            points.push_back(normal);
            p.setPoint(j * increment_T, (i+1) * increment_T, 0);
            points.push_back(p);


            p.setPoint(x_aux, y_aux, z_aux + increment_z );
            points.push_back(p);
            points.push_back(normal);
            p.setPoint(j * increment_T, (i+1) * increment_T, 0);
            points.push_back(p);

            p.setPoint(x_aux + increment_x, y_aux, z_aux);
            points.push_back(p);
            points.push_back(normal);
            p.setPoint((j+1) * increment_T, i * increment_T, 0);
            points.push_back(p);

            p.setPoint(x_aux + increment_x, y_aux, z_aux + increment_z );
            points.push_back(p);
            points.push_back(normal);
            p.setPoint((j+1) * increment_T, (i+1) * increment_T, 0);
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
    normal.setPoint(1, 0, 0);

    //ciclo de desenho da face da direita
    for (int i = 0; i < divisions; i++){

        for (int j = 0; j < divisions; j++){

            p.setPoint(x_aux, y_aux, z_aux);
            points.push_back(p);
            points.push_back(normal);
            p.setPoint(j * increment_T, i * increment_T, 0);
            points.push_back(p);

            p.setPoint(x_aux, y_aux, z_aux - increment_z);
            points.push_back(p);
            points.push_back(normal);
            p.setPoint((j+1) * increment_T, i * increment_T, 0);
            points.push_back(p);

            p.setPoint(x_aux, y_aux + increment_y, z_aux );
            points.push_back(p);
            points.push_back(normal);
            p.setPoint(j * increment_T, (i+1) * increment_T, 0);
            points.push_back(p);


            p.setPoint(x_aux, y_aux + increment_y, z_aux );
            points.push_back(p);
            points.push_back(normal);
            p.setPoint(j * increment_T, (i+1) * increment_T, 0);
            points.push_back(p);

            p.setPoint(x_aux, y_aux, z_aux - increment_z);
            points.push_back(p);
            points.push_back(normal);
            p.setPoint((j+1) * increment_T, i * increment_T, 0);
            points.push_back(p);

            p.setPoint(x_aux, y_aux + increment_y, z_aux - increment_z );
            points.push_back(p);
            points.push_back(normal);
            p.setPoint((j+1) * increment_T, (i+1) * increment_T, 0);
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
    normal.setPoint(-1, 0, 0);

    //ciclo de desenho da face da esquerda
    for (int i = 0; i < divisions; i++){

        for (int j = 0; j < divisions; j++){

            p.setPoint(x_aux, y_aux, z_aux);
            points.push_back(p);
            points.push_back(normal);
            p.setPoint(j * increment_T, i * increment_T, 0);
            points.push_back(p);

            p.setPoint(x_aux, y_aux, z_aux + increment_z);
            points.push_back(p);
            points.push_back(normal);
            p.setPoint((j+1) * increment_T, i * increment_T, 0);
            points.push_back(p);

            p.setPoint(x_aux, y_aux + increment_y, z_aux );
            points.push_back(p);
            points.push_back(normal);
            p.setPoint(j * increment_T, (i+1) * increment_T, 0);
            points.push_back(p);


            p.setPoint(x_aux, y_aux + increment_y, z_aux );
            points.push_back(p);
            points.push_back(normal);
            p.setPoint(j * increment_T, (i+1) * increment_T, 0);
            points.push_back(p);

            p.setPoint(x_aux, y_aux, z_aux + increment_z);
            points.push_back(p);
            points.push_back(normal);
            p.setPoint((j+1) * increment_T, i * increment_T, 0);
            points.push_back(p);

            p.setPoint(x_aux, y_aux + increment_y, z_aux + increment_z );
            points.push_back(p);
            points.push_back(normal);
            p.setPoint((j+1) * increment_T, (i+1) * increment_T, 0);
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
    double increment_Tx = 1.0 / slices;
    double increment_Ty = 1.0 / stacks;
    double height_aux = height / 2;
    double height_increment = height / stacks;
    double radius_decrement = radius / stacks;
    double height_now = -height_aux;
    double radius_now = radius;
    double radius_next = radius_now - radius_decrement;
    double height_next = height_increment + height_now;

    Point p_aux[3];
    Point v1, v2, normal;

    for (int j = 0; j < stacks; j++){

        for (int i = 0; i < slices; i++) {

            //Vertice
            p_aux[0].setPoint(radius_now * sin(increment * i), height_now, radius_now * cos(increment * i) );
            p_aux[1].setPoint(radius_now * sin(increment * (i + 1)), height_now, radius_now * cos(increment * (i + 1)) );
            p_aux[2].setPoint(radius_next * sin(increment * i), height_next, radius_next * cos(increment * i ));

            //Calcular normal
            v1 = difference(p_aux[1], p_aux[0]);
            v2 = difference(p_aux[2], p_aux[0]);
            normal = normalize( cross(v1, v2) );


            //Push vertice 1, push normal, push textura
            points.push_back(p_aux[0]);
            points.push_back(normal);
            p.setPoint(i * increment_Tx, j * increment_Ty, 0);
            points.push_back(p);

//            Push vertice 2, push normal, push textura
            points.push_back(p_aux[1]);
            points.push_back(normal);
            p.setPoint((i + 1) * increment_Tx, j * increment_Ty, 0);
            points.push_back(p);

//            Push vertice 3, push normal, push textura
            points.push_back(p_aux[2]);
            points.push_back(normal);
            p.setPoint(i * increment_Tx, (j + 1) * increment_Ty, 0);
            points.push_back(p);



            p.setPoint(radius_next * sin(increment * i), height_next, radius_next * cos(increment * i ));
            points.push_back(p);
            points.push_back(normal);
            p.setPoint(i * increment_Tx, (j + 1) * increment_Ty, 0);
            points.push_back(p);

            p.setPoint(radius_now * sin(increment * (i + 1)), height_now, radius_now * cos(increment * (i + 1)) );
            points.push_back(p);
            points.push_back(normal);
            p.setPoint((i + 1) * increment_Tx, j * increment_Ty, 0);
            points.push_back(p);

            p.setPoint(radius_next * sin(increment * (i + 1)) ,height_next ,radius_next * cos(increment * (i + 1)) );
            points.push_back(p);
            points.push_back(normal);
            p.setPoint((i + 1) * increment_Tx, (j + 1) * increment_Ty, 0);
            points.push_back(p);
        }

        height_now = height_next;
        height_next += height_increment;

        radius_now = radius_next;
        radius_next -= radius_decrement;
    }

    normal.setPoint(0, -1, 0);

    for (int a = 0; a < slices; a++) {

        //face inferior
        p.setPoint(0, -height_aux, 0);
        points.push_back(p);
        points.push_back(normal);
        p.setPoint(0.5, 0.5, 0);
        points.push_back(p);

        p.setPoint(sin(increment * (a + 1)) * radius, -height_aux, cos(increment * (a + 1)) * radius);
        points.push_back(p);
        points.push_back(normal);
        p.setPoint(sin(increment * (a + 1)) * 0.5 + 0.5, cos(increment * (a + 1)) * 0.5 + 0.5, 0);
        points.push_back(p);

        p.setPoint(sin(increment * a) * radius, -height_aux, cos(increment * a) * radius);
        points.push_back(p);
        points.push_back(normal);
        p.setPoint(sin(increment * a) * 0.5 + 0.5, cos(increment * a) * 0.5 + 0.5, 0);
        points.push_back(p);
    }

    return points;
}


vector <Point> sphere_generate_points(vector <Point> points,float radius, int slices, int stacks, float center_x, float center_y, float center_z) {

    Point p;

    double increment1 = (2 * M_PI) / slices;
    double increment2 = M_PI / stacks;

    double increment1T = 1.0f / slices;
    double increment2T = 1.0f / stacks;

    //z = radius * cos(BETA) * cos(ALFA)
    //x = radius * cos(BETA) * sin(ALFA)
    //y = radius * cos(BETA)

    //horizontal -> slices -> alpha -> a

    for (int i = 0; i < stacks; i++){

        for (int a = 0; a < slices; a++){

            //triangulo 1
            // Vertice
            p.setPoint(center_x + radius * cos(i * increment2 - M_PI / 2) * sin((a + 1) * increment1), center_y + radius * sin(i * increment2- M_PI / 2), center_z + radius * cos(i * increment2- M_PI / 2) * cos((a + 1) * increment1));
            points.push_back(p);
            // Normal
            p.setPoint(cos(i * increment2- M_PI / 2) * sin((a + 1) * increment1), sin(i * increment2- M_PI / 2), cos(i * increment2- M_PI / 2) * cos((a + 1) * increment1));
            p = normalize(p);
            points.push_back(p);
            // Texture
            p.setPoint((a+1) * increment1T, i * increment2T, 0);
            points.push_back(p);

            p.setPoint(center_x + radius * cos((i + 1) * increment2- M_PI / 2) * sin(a * increment1), center_y + radius * sin((i + 1) * increment2- M_PI / 2), center_z + radius * cos((i + 1) * increment2- M_PI / 2) * cos(a * increment1));
            points.push_back(p);
            p.setPoint(cos((i + 1) * increment2- M_PI / 2) * sin(a * increment1), sin((i + 1) * increment2- M_PI / 2), cos((i + 1) * increment2- M_PI / 2) * cos(a * increment1));
            p = normalize(p);
            points.push_back(p);
            p.setPoint(a * increment1T, (i+1) * increment2T, 0);
            points.push_back(p);

            p.setPoint(center_x + radius * cos(i * increment2- M_PI / 2) * sin(a * increment1), center_y + radius * sin(i * increment2- M_PI / 2), center_z + radius * cos(i * increment2- M_PI / 2) * cos(a * increment1));
            points.push_back(p);
            p.setPoint(cos(i * increment2- M_PI / 2) * sin(a * increment1), sin(i * increment2- M_PI / 2), cos(i * increment2- M_PI / 2) * cos(a * increment1));
            p = normalize(p);
            points.push_back(p);
            p.setPoint(a * increment1T, i * increment2T, 0);
            points.push_back(p);


            //triangulo 2
            p.setPoint(center_x + radius * cos((i + 1) * increment2- M_PI / 2) * sin(a * increment1), center_y + radius * sin((i + 1) * increment2- M_PI / 2), center_z + radius * cos((i + 1) * increment2- M_PI / 2) * cos(a * increment1));
            points.push_back(p);
            p.setPoint(cos((i + 1) * increment2- M_PI / 2) * sin(a * increment1), sin((i + 1) * increment2- M_PI / 2), cos((i + 1) * increment2- M_PI / 2) * cos(a * increment1));
            p = normalize(p);
            points.push_back(p);
            p.setPoint(a * increment1T, (i+1) * increment2T, 0);
            points.push_back(p);

            p.setPoint(center_x + radius * cos(i * increment2- M_PI / 2) * sin((a + 1) * increment1), center_y + radius * sin(i * increment2- M_PI / 2), center_z + radius * cos(i * increment2- M_PI / 2) * cos((a + 1) * increment1));
            points.push_back(p);
            p.setPoint(cos(i * increment2- M_PI / 2) * sin((a + 1) * increment1), sin(i * increment2- M_PI / 2), cos(i * increment2- M_PI / 2) * cos((a + 1) * increment1));
            p = normalize(p);
            points.push_back(p);
            p.setPoint((a+1) * increment1T, i * increment2T, 0);
            points.push_back(p);

            p.setPoint(center_x + radius * cos((i + 1) * increment2- M_PI / 2) * sin((a + 1) * increment1), center_y + radius * sin((i + 1) * increment2- M_PI / 2), center_z + radius * cos((i + 1) * increment2- M_PI / 2) * cos((a + 1) * increment1));
            points.push_back(p);
            p.setPoint(cos((i + 1) * increment2- M_PI / 2) * sin((a + 1) * increment1), sin((i + 1) * increment2- M_PI / 2), cos((i + 1) * increment2- M_PI / 2) * cos((a + 1) * increment1));
            p = normalize(p);
            points.push_back(p);
            p.setPoint((a+1) * increment1T, (i+1) * increment2T, 0);
            points.push_back(p);

        }
    }
    return points;
}

vector <Point> ambient_generate_points(vector <Point> points,float radius, int slices, int stacks) {

    Point p;

    double increment1 = (2 * M_PI) / slices;
    double increment2 = M_PI / stacks;

    double increment1T = 1.0f / slices;
    double increment2T = 1.0f / stacks;

    //z = radius * cos(BETA) * cos(ALFA)
    //x = radius * cos(BETA) * sin(ALFA)
    //y = radius * cos(BETA)

    //horizontal -> slices -> alpha -> a

    for (int i = 0; i < stacks; i++){

        for (int a = 0; a < slices; a++){

            //triangulo 1
            // Vertice
            p.setPoint(radius * cos(i * increment2 - M_PI / 2) * sin((a + 1) * increment1), radius * sin(i * increment2- M_PI / 2), radius * cos(i * increment2- M_PI / 2) * cos((a + 1) * increment1));
            points.push_back(p);
            // Normal
            p.setPoint(- cos(i * increment2- M_PI / 2) * sin((a + 1) * increment1), - sin(i * increment2- M_PI / 2), - cos(i * increment2- M_PI / 2) * cos((a + 1) * increment1));
            points.push_back(p);
            // Texture
            p.setPoint((a+1) * increment1T, i * increment2T, 0);
            points.push_back(p);

            p.setPoint(radius * cos(i * increment2- M_PI / 2) * sin(a * increment1), radius * sin(i * increment2- M_PI / 2), radius * cos(i * increment2- M_PI / 2) * cos(a * increment1));
            points.push_back(p);
            p.setPoint(- cos(i * increment2- M_PI / 2) * sin(a * increment1), - sin(i * increment2- M_PI / 2), - cos(i * increment2- M_PI / 2) * cos(a * increment1));
            points.push_back(p);
            p.setPoint(a * increment1T, i * increment2T, 0);
            points.push_back(p);

            p.setPoint(radius * cos((i + 1) * increment2- M_PI / 2) * sin(a * increment1), radius * sin((i + 1) * increment2- M_PI / 2), radius * cos((i + 1) * increment2- M_PI / 2) * cos(a * increment1));
            points.push_back(p);
            p.setPoint(- cos((i + 1) * increment2- M_PI / 2) * sin(a * increment1), - sin((i + 1) * increment2- M_PI / 2), - cos((i + 1) * increment2- M_PI / 2) * cos(a * increment1));
            points.push_back(p);
            p.setPoint(a * increment1T, (i+1) * increment2T, 0);
            points.push_back(p);


            //triangulo 2
            p.setPoint(radius * cos((i + 1) * increment2- M_PI / 2) * sin(a * increment1), radius * sin((i + 1) * increment2- M_PI / 2), radius * cos((i + 1) * increment2- M_PI / 2) * cos(a * increment1));
            points.push_back(p);
            p.setPoint(- cos((i + 1) * increment2- M_PI / 2) * sin(a * increment1), - sin((i + 1) * increment2- M_PI / 2), - cos((i + 1) * increment2- M_PI / 2) * cos(a * increment1));
            points.push_back(p);
            p.setPoint(a * increment1T, (i+1) * increment2T, 0);
            points.push_back(p);

            p.setPoint(radius * cos((i + 1) * increment2- M_PI / 2) * sin((a + 1) * increment1), radius * sin((i + 1) * increment2- M_PI / 2), radius * cos((i + 1) * increment2- M_PI / 2) * cos((a + 1) * increment1));
            points.push_back(p);
            p.setPoint(- cos((i + 1) * increment2- M_PI / 2) * sin((a + 1) * increment1), - sin((i + 1) * increment2- M_PI / 2), - cos((i + 1) * increment2- M_PI / 2) * cos((a + 1) * increment1));
            points.push_back(p);
            p.setPoint((a+1) * increment1T, (i+1) * increment2T, 0);
            points.push_back(p);

            p.setPoint(radius * cos(i * increment2- M_PI / 2) * sin((a + 1) * increment1), radius * sin(i * increment2- M_PI / 2), radius * cos(i * increment2- M_PI / 2) * cos((a + 1) * increment1));
            points.push_back(p);
            p.setPoint(- cos(i * increment2- M_PI / 2) * sin((a + 1) * increment1), - sin(i * increment2- M_PI / 2), - cos(i * increment2- M_PI / 2) * cos((a + 1) * increment1));
            points.push_back(p);
            p.setPoint((a+1) * increment1T, i * increment2T, 0);
            points.push_back(p);

        }
    }
    return points;
}


vector <Point> torus_generate_points(vector <Point> points, float radius, float radius_torus, float slices, int stacks) {

    Point p;

    double increment = (2 * M_PI) / slices;
    double increment1 = (2 * M_PI) / stacks;

    double incrementT = 1.0f / stacks;

    float torus_center_x = -1;
    float torus_center_z = -1;

    float normal_x = -1;
    float normal_y = -1;
    float normal_z = -1;

    int texture_aux = 0;

    for (int i = 0; i < stacks; i++){
        for (int j = 0; j < slices; j++){

            Point p_aux[3];
            Point v1, v2, normal;

            //Vertice
            p_aux[0].setPoint((radius + (radius_torus * cos(i * increment1))) * cos(j * increment), (radius + (radius_torus * cos(i * increment1))) * sin(j * increment), radius_torus * sin(i * increment1));
            p_aux[1].setPoint((radius + (radius_torus * cos(i * increment1))) * cos((j + 1) * increment), (radius + (radius_torus * cos(i * increment1))) * sin((j + 1) * increment), radius_torus * sin(i * increment1));
            p_aux[2].setPoint((radius + (radius_torus * cos((i + 1) * increment1))) * cos(j * increment), (radius + (radius_torus * cos((i + 1) * increment1))) * sin(j * increment), radius_torus * sin((i + 1) * increment1));

            //Calcular normal
            v1 = difference(p_aux[1], p_aux[0]);
            v2 = difference(p_aux[2], p_aux[0]);
            normal = normalize( cross(v1, v2) );

            //Vertice
            points.push_back(p_aux[0]);
            points.push_back(normal);

            //Textura
            if (i < stacks / 2)
                p.setPoint(2 * i * incrementT, 1, 0);
            else p.setPoint(1 - (2 * texture_aux * incrementT), 1, 0);
            points.push_back(p);

            //Vertice
            points.push_back(p_aux[1]);
            points.push_back(normal);

            //Textura
            if (i < stacks / 2)
                p.setPoint(2 * i * incrementT, 0, 0);
            else p.setPoint(1 - (2 * texture_aux * incrementT), 0, 0);
            points.push_back(p);


            //Vertice
            points.push_back(p_aux[2]);
            points.push_back(normal);

            //Textura
            if (i < stacks / 2)
                p.setPoint(2 * (i + 1) * incrementT, 0, 0);
            else p.setPoint(1 - (2 * (texture_aux + 1) * incrementT), 0, 0);
            points.push_back(p);








            //Vertice
            p.setPoint((radius + (radius_torus * cos(i * increment1))) * cos((j + 1) * increment), (radius + (radius_torus * cos(i * increment1))) * sin((j + 1) * increment), radius_torus * sin(i * increment1));
            points.push_back(p);

            //Normal
            points.push_back(normal);

            //Textura
            if (i < stacks / 2)
                p.setPoint(2 * i * incrementT, 0, 0);
            else p.setPoint(1 - (2 * texture_aux * incrementT), 0, 0);
            points.push_back(p);


            //Vertice
            p.setPoint((radius + (radius_torus * cos((i + 1) * increment1))) * cos((j + 1) * increment), (radius + (radius_torus * cos((i + 1) * increment1))) * sin((j + 1) * increment), radius_torus * sin((i + 1) * increment1));
            points.push_back(p);

            //Normal
            points.push_back(normal);

            //Textura
            if (i < stacks / 2)
                p.setPoint(2 * (i + 1) * incrementT, 0, 0);
            else p.setPoint(1 - (2 * (texture_aux + 1) * incrementT), 0, 0);
            points.push_back(p);


            //Vertice
            p.setPoint((radius + (radius_torus * cos((i + 1) * increment1))) * cos(j * increment), (radius + (radius_torus * cos((i + 1) * increment1))) * sin(j * increment), radius_torus * sin((i + 1) * increment1));
            points.push_back(p);

            //Normal
            points.push_back(normal);

            //Textura
            if (i < stacks / 2)
                p.setPoint(2 * (i + 1) * incrementT, 1, 0);
            else p.setPoint(1 - (2 * (texture_aux + 1) * incrementT), 1, 0);
            points.push_back(p);
        }
        if (i >= stacks / 2)
            texture_aux++;
    }

    return points;
}

vector <Point> generate_belt(vector<Point> points, int nr, int min, int max){

    for (int i = 0; i < nr; i++){

        int raio = rand()%(max-min + 1) + min;
        float alfa = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * (2 * M_PI);

        float x = raio * sin(alfa);
        float y = 0;
        float z = raio * cos(alfa);

        printf("%f - %f \n", x,z );

        points = sphere_generate_points(points, 0.25, 20, 20, x, y, z);

    }

    return points;
}
