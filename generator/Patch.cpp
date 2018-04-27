
#include "Patch.h"
using std::vector;

int Patch::getNum_patches() const {
    return num_patches;
}

int Patch::getNum_ctrl_pt() const {
    return num_ctrl_pt;
}

const vector<Point> &Patch::getIndices() const {
    return indices;
}

const vector<Point> &Patch::getControl_points() const {
    return control_points;
}

void Patch::setNum_patches(int num_patches) {
    Patch::num_patches = num_patches;
}

void Patch::setNum_ctrl_pt(int num_ctrl_pt) {
    Patch::num_ctrl_pt = num_ctrl_pt;
}

void Patch::setIndices(const vector<Point> &indices) {
    Patch::indices = indices;
}

void Patch::setControl_points(const vector<Point> &control_points) {
    Patch::control_points = control_points;
}

void Patch::split(const std::string& s, char delim,vector<std::string>& v) {
    auto i = 0;
    auto pos = s.find(delim);
    while (pos != std::string::npos) {
        v.push_back(s.substr(i, pos-i));
        i = ++pos;
        pos = s.find(delim, pos);

        if (pos == std::string::npos)
            v.push_back(s.substr(i, s.length()));
    }
}

void Patch::parse_patch(char* file_name) {
    float buffer_points[3];
    Point p;

    std::string buffer;
    std::string buffer_aux;
    std::fstream fs;

    fs.open(file_name, std::fstream::in);

    if (fs.is_open()) {
        getline(fs, buffer);
        num_patches = stoi(buffer);

        for (int i = 0; i < num_patches ; i++){

            getline(fs, buffer);

            buffer.erase(std::remove(buffer.begin(), buffer.end(), ','), buffer.end());

            vector<std::string> aux;
            split(buffer,' ', aux);

            p.setPoint(strtof(aux[0].c_str(),0), strtof(aux[1].c_str(),0), strtof(aux[2].c_str(),0));

            indices.push_back(p);

        }

        getline(fs, buffer);
        num_ctrl_pt = stoi(buffer);

        for (int i = 0; i < num_ctrl_pt; i++){
            getline(fs, buffer_aux);

            std::string buffer = buffer_aux.substr(1, buffer_aux.size());
            buffer.erase(std::remove(buffer.begin(), buffer.end(), ','), buffer.end());

            vector<std::string> aux;
            split(buffer,' ', aux);
            p.setPoint(strtof(aux[0].c_str(),0), strtof(aux[1].c_str(),0), strtof(aux[2].c_str(),0));
            //printf("%f %f %f\n", strtof(aux[0].c_str(),0), strtof(aux[1].c_str(),0), strtof(aux[2].c_str(),0));

            control_points.push_back(p);

        }

//        printf("NUM PATCHES -> %d\nNUM CTRL PTS -> %d\n", num_patches, num_ctrl_pt);
//
//        for (int i = 0; i < num_patches; i++)
//            printf("indices %d -> %f %f %f \n",i,indices[i].getX(), indices[i].getY(), indices[i].getZ());
//
//        for (int i = 0; i < num_ctrl_pt; i++)
//            printf("control point nº%d -> %f %f %f\n",i, control_points[i].getX(), control_points[i].getY(), control_points[i].getZ());

        fs.close();
    }
}

vector<Point> Patch::generateBezier() {

    int npatch;
    int narco;
    int p;

    vector<Point> p0;
    vector<Point> p1;
    vector<Point> p2;
    vector<Point> p3;

    for (npatch = 0; npatch < num_patches; npatch++) {

        //Coloca os pontos de controlo no p0, p1, p2 e p3.
        for (narco = 0; narco < 4; narco++) {
            for (p = 0; p < 4 && narco == 0; p++) {
                p0.push_back(control_points[indices[npatch * 16 + narco * 4 + p]]);
            }

            for (p = 0; p < 4 && narco == 1; p++) {
                p1.push_back(control_points[indices[npatch * 16 + narco * 4 + p]]);
            }

            for (p = 0; p < 4 && narco == 2; p++) {
                p2.push_back(control_points[indices[npatch * 16 + narco * 4 + p]]);
            }

            for (p = 0; p < 4 && narco == 3; p++) {
                p3.push_back(control_points[indices[npatch * 16 + narco * 4 + p]]);
            }
        }

        //Um patch pronto para o algoritmo de Casteljau.

    }
}
