
#include "Patch.h"

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

            for (int i = 0; i < 16; i++){
                indices.push_back(stoi(aux[i]));
            }

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

        printf("NUM PATCHES -> %d\nNUM CTRL PTS -> %d\n", num_patches, num_ctrl_pt);

        for (int i = 0; i < num_patches * 16; i++)
            printf("indices %d -> %d \n",i,indices[i]);

        for (int i = 0; i < num_ctrl_pt; i++)
            printf("control point nº%d -> %f %f %f\n",i, control_points[i].getX(), control_points[i].getY(), control_points[i].getZ());

        fs.close();
    }
}
