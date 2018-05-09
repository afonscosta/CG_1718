
#include "generator.h"
#include "Patch.h"


int writeFile (vector<Point> points, std::string file_name)
{
    ofstream myfile;
    myfile.open(file_name);
    if (myfile.is_open()) {
        for (int i = 0; i < points.size() - 1; i += 2) {
            myfile << points[i].getX() << " " << points[i].getY() << " " << points[i].getZ() << "\n";   // Vértices
            myfile << points[i+1].getX() << " " << points[i+1].getY() << "\n";                              // Textura
        }
        myfile.close();
    }
    return 0;
}

int main(int argc, char **argv) {
    vector<Point> points;
    if (argc == 4) {
        if (strcmp(argv[1], "plane") == 0) {
            points = plane_generate_points(points, strtof(argv[2], NULL) / 2);
            writeFile(points, argv[3]);
        } else {
            Patch patch;
            patch.parse_patch(argv[1]);
            patch.setTesselation(atoi(argv[2]));
            patch.generateBezier();
            writeFile(patch.getCurve_points(), argv[3]);
        }
    } else if (argc == 6) {
        if (strcmp(argv[1], "sphere") == 0) {
            points = sphere_generate_points(points, strtof(argv[2], NULL), strtof(argv[3], NULL),
                                            strtof(argv[4], NULL));
            writeFile(points, argv[5]);
        } else if (strcmp(argv[1], "box") == 0) {
            points = box_generate_points(points, strtof(argv[2], NULL) / 2, strtof(argv[3], NULL) / 2,
                                         strtof(argv[4], NULL) / 2, 1);
            writeFile(points, argv[5]);
        }
    } else if (argc == 7) {
        if (strcmp(argv[1], "cone") == 0) {
            points = cone_generate_points(points, strtof(argv[2], NULL), strtof(argv[3], NULL) / 2,
                                          strtof(argv[4], NULL), strtof(argv[5], NULL));
            writeFile(points, argv[6]);
        } else if (strcmp(argv[1], "box") == 0) {
            points = box_generate_points(points, strtof(argv[2], NULL) / 2, strtof(argv[3], NULL) / 2,
                                         strtof(argv[4], NULL) / 2, strtof(argv[5], NULL));
            writeFile(points, argv[6]);
        } else if (strcmp(argv[1], "torus") == 0) {
            points = torus_generate_points(points, strtof(argv[2], NULL), strtof(argv[3], NULL), strtof(argv[4], NULL),
                                           strtof(argv[5], NULL));
            writeFile(points, argv[6]);
        }
    }

    return 0;
}
