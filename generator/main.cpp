
#include "generator.h"
#include "Patch.h"

using std::ofstream;
using std::vector;

int writeFile (vector <Point> points, std::string file_name)
{
    ofstream myfile;
    myfile.open(file_name);
    if (myfile.is_open()) {
        for (int i = 0; i < points.size(); i++) {
            myfile << points[i].getX() << " " << points[i].getY() << " " << points[i].getZ() << "\n";
        }
        myfile.close();
    }
    return 0;
}

int main(int argc, char **argv) {
    vector <Point> points;
    if (argc == 4) {
        if (strcmp(argv[1], "plane") == 0) {
            points = plane_generate_points(points, strtof(argv[2],NULL)/2);
            writeFile(points, argv[3]);
        }
        else if (strcmp(argv[1], "orbit") == 0) {
            points = orbit_generate_points(points, strtof(argv[2],NULL) );
            writeFile(points, argv[3]);
        }
        else{
            Patch patch;
            patch.parse_patch(argv[1]);
            //tesselation level é o argv[2]
            //points = bezier_generate_points(points, argv[1]);
            writeFile(points, argv[3]);
        }
    }
    else if (argc == 5){
        if (strcmp(argv[1], "belt") == 0) {
            points = belt_generate_points(points, strtof(argv[2], NULL), strtof(argv[3], NULL));
            writeFile(points, argv[4]);
        }
    }
    else if (argc == 6) {
        if (strcmp(argv[1], "sphere") == 0) {
            points = sphere_generate_points(points, strtof(argv[2], NULL), strtof(argv[3], NULL), strtof(argv[4], NULL));
            writeFile(points, argv[5]);
        }
        else if (strcmp(argv[1], "box") == 0) {
            points = box_generate_points(points, strtof(argv[2], NULL)/2, strtof(argv[3], NULL)/2, strtof(argv[4], NULL)/2, 1);
            writeFile(points, argv[5]);
        }
    }
    else if (argc == 7) {
        if (strcmp(argv[1], "cone") == 0) {
            points = cone_generate_points(points, strtof(argv[2], NULL), strtof(argv[3], NULL)/2, strtof(argv[4], NULL), strtof(argv[5], NULL));
            writeFile(points, argv[6]);
        }
        else if (strcmp(argv[1], "box") == 0) {
            points = box_generate_points(points, strtof(argv[2], NULL)/2, strtof(argv[3], NULL)/2, strtof(argv[4], NULL)/2, strtof(argv[5], NULL));
            writeFile(points, argv[6]);
        }
        else if (strcmp(argv[1], "torus") == 0) {
            points = torus_generate_points(points, strtof(argv[2], NULL), strtof(argv[3], NULL), strtof(argv[4], NULL), strtof(argv[5], NULL));
            writeFile(points, argv[6]);
        }
    }

    return 0;
}
