
#include "Patch.h"


void Patch::setTesselation(int tess) {
    this->tess = tess;
}

void Patch::setCurve_points(vector<Point> curve_points) {
    Patch::curve_points = curve_points;
}

vector<Point> Patch::getCurve_points() const {
    return curve_points;
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

void multMatrixVector(float *m, float *v, float *res) {

    for (int j = 0; j < 4; ++j) {
        res[j] = 0;
        for (int k = 0; k < 4; ++k) {
            res[j] += v[k] * m[j * 4 + k];
        }
    }

}


void normalize(float *a) {

    float l = sqrt(a[0]*a[0] + a[1] * a[1] + a[2] * a[2]);
    a[0] = a[0]/l;
    a[1] = a[1]/l;
    a[2] = a[2]/l;
}

void calcPointsSurface(float passo, float *U, float *V, float* M, float *Mt, float *P, vector<float> *curvePoints) {

    float res[4];
    float res1[4];
    Point p;
    for (float u = 0; u < 1 - passo; u += passo) {
        for (float v = 0; v < 1 - passo; v += passo) {

            //v, u
            U[0] = (float) pow(u, 3);
            U[1] = (float) pow(u, 2);
            U[2] = u;
            U[3] = 1;

            V[0] = (float) pow(v, 3);
            V[1] = (float) pow(v, 2);
            V[2] = v;
            V[3] = 1;

            multMatrixVector((float *) M, U, res); //U * M
            multMatrixVector(res, (float *) P, res1); //U * M * P
            multMatrixVector(res1, (float *) Mt, res); //U * M * P * Mt
            res1[0] = res[0] * V[0] + res[1] * V[1] + res[2] * V[2] + res[3] * V[3];

            (*curvePoints).push_back(res1[0]);

            //v, u+passo
            U[0] = (float) pow(u + passo, 3);
            U[1] = (float) pow(u + passo, 2);
            U[2] = u + passo;
            U[3] = 1;

            multMatrixVector((float *) M, U, res); //U * M
            multMatrixVector(res, (float *) P, res1); //U * M * P
            multMatrixVector(res1, (float *) Mt, res); //U * M * P * Mt
            res1[0] = res[0] * V[0] + res[1] * V[1] + res[2] * V[2] + res[3] * V[3];

            p.setPoint(res1[0], 0, 0);
            (*curvePoints).push_back(res1[0]);

            //v+passo, u+passo
            V[0] = (float) pow(v + passo, 3);
            V[1] = (float) pow(v + passo, 2);
            V[2] = v + passo;
            V[3] = 1;

            multMatrixVector((float *) M, U, res); //U * M
            multMatrixVector(res, (float *) P, res1); //U * M * P
            multMatrixVector(res1, (float *) Mt, res); //U * M * P * Mt
            res1[0] = res[0] * V[0] + res[1] * V[1] + res[2] * V[2] + res[3] * V[3];

            (*curvePoints).push_back(res1[0]);

            //v, u
            U[0] = (float) pow(u, 3);
            U[1] = (float) pow(u, 2);
            U[2] = u;
            U[3] = 1;

            V[0] = (float) pow(v, 3);
            V[1] = (float) pow(v, 2);
            V[2] = v;
            V[3] = 1;

            multMatrixVector((float *) M, U, res); //U * M
            multMatrixVector(res, (float *) P, res1); //U * M * P
            multMatrixVector(res1, (float *) Mt, res); //U * M * P * Mt
            res1[0] = res[0] * V[0] + res[1] * V[1] + res[2] * V[2] + res[3] * V[3];

            (*curvePoints).push_back(res1[0]);

            //v+passo, u+passo
            U[0] = (float) pow(u + passo, 3);
            U[1] = (float) pow(u + passo, 2);
            U[2] = u + passo;
            U[3] = 1;

            V[0] = (float) pow(v + passo, 3);
            V[1] = (float) pow(v + passo, 2);
            V[2] = v + passo;
            V[3] = 1;

            multMatrixVector((float *) M, U, res); //U * M
            multMatrixVector(res, (float *) P, res1); //U * M * P
            multMatrixVector(res1, (float *) Mt, res); //U * M * P * Mt
            res1[0] = res[0] * V[0] + res[1] * V[1] + res[2] * V[2] + res[3] * V[3];

            (*curvePoints).push_back(res1[0]);

            //v + passo, u
            U[0] = (float) pow(u, 3);
            U[1] = (float) pow(u, 2);
            U[2] = u;
            U[3] = 1;

            multMatrixVector((float *) M, U, res); //U * M
            multMatrixVector(res, (float *) P, res1); //U * M * P
            multMatrixVector(res1, (float *) Mt, res); //U * M * P * Mt
            res1[0] = res[0] * V[0] + res[1] * V[1] + res[2] * V[2] + res[3] * V[3];

            (*curvePoints).push_back(res1[0]);

            V[0] = (float) pow(v, 3);
            V[1] = (float) pow(v, 2);
            V[2] = v;
            V[3] = 1;
        }
    }

}

void Patch::calcBezierPoints(int tess, Point p0[][4], Point p1[][4], Point p2[][4], Point p3[][4]) {
    float passo = 0;
    if (tess)
        passo = 1/tess;
    float u = 0;
    float v = 0;
    float Px[4][4] = { {p0[0]->getX(), p0[0]->getX(), p0[0]->getX(), p0[0]->getX()},
                       {p1[0]->getX(), p1[0]->getX(), p1[0]->getX(), p1[0]->getX()},
                       {p2[0]->getX(), p2[0]->getX(), p2[0]->getX(), p2[0]->getX()},
                       {p3[0]->getX(), p3[0]->getX(), p3[0]->getX(), p3[0]->getX()} };
    float Py[4][4] = { {p0[0]->getY(), p0[0]->getY(), p0[0]->getY(), p0[0]->getY()},
                       {p1[0]->getY(), p1[0]->getY(), p1[0]->getY(), p1[0]->getY()},
                       {p2[0]->getY(), p2[0]->getY(), p2[0]->getY(), p2[0]->getY()},
                       {p3[0]->getY(), p3[0]->getY(), p3[0]->getY(), p3[0]->getY()} };
    float Pz[4][4] = { {p0[0]->getZ(), p0[0]->getZ(), p0[0]->getZ(), p0[0]->getZ()},
                       {p1[0]->getZ(), p1[0]->getZ(), p1[0]->getZ(), p1[0]->getZ()},
                       {p2[0]->getZ(), p2[0]->getZ(), p2[0]->getZ(), p2[0]->getZ()},
                       {p3[0]->getZ(), p3[0]->getZ(), p3[0]->getZ(), p3[0]->getZ()} };
    float U[4] = {(float) pow(u, 3), (float) pow(u, 2), u, 1};
    float V[4] = {(float) pow(v, 3), (float) pow(v, 2), v, 1};
    float T[4] = {(float) pow(tess, 3), (float) pow(tess, 2), tess, 1};
    float M[4][4] = { {-1, 3, -3, 1},
                      {3, -6, 3, 0},
                      {-3, 3, 0, 0},
                      {1, 0, 0, 0} };
    float Mt[4][4] = { {-1, 3, -3, 1},
                       {3, -6, 3, 0},
                       {-3, 3, 0, 0},
                       {1, 0, 0, 0} };

    vector<float> curvePointsX;
    vector<float> curvePointsY;
    vector<float> curvePointsZ;

    calcPointsSurface(passo, U, V, (float *) M, (float *) Mt, (float *) Px, &curvePointsX);

    U[0] = (float) pow(u, 3);
    U[1] = (float) pow(u, 2);
    U[2] = u;
    U[3] = 1;

    V[4] = (float) pow(v, 3);
    V[4] = (float) pow(v, 2);
    V[4] = v;
    V[4] = 1;

    calcPointsSurface(passo, U, V, (float *) M, (float *) Mt, (float *) Py, &curvePointsY);

    U[0] = (float) pow(u, 3);
    U[1] = (float) pow(u, 2);
    U[2] = u;
    U[3] = 1;

    V[4] = (float) pow(v, 3);
    V[4] = (float) pow(v, 2);
    V[4] = v;
    V[4] = 1;

    calcPointsSurface(passo, U, V, (float *) M, (float *) Mt, (float *) Pz, &curvePointsZ);

    Point p;

    for (int i = 0; i < curvePointsX.size(); i++) {
        p.setPoint(curvePointsX[i], curvePointsY[i], curvePointsZ[i]);
        curve_points.push_back(p);
    }
}

void Patch::generateBezier() {

    int npatch;
    int narco;
    int p;

    Point p0[4][4];
    Point p1[4][4];
    Point p2[4][4];
    Point p3[4][4];

    for (npatch = 0; npatch < num_patches; npatch++) {

        //Coloca os pontos de controlo no p0, p1, p2 e p3.
        for (narco = 0; narco < 4; narco++) {
            for (p = 0; p < 4 && narco == 0; p++) {
                p0[narco][p] = control_points[indices[npatch * 16 + narco * 4 + p]];
            }

            for (p = 0; p < 4 && narco == 1; p++) {
                p1[narco][p] = control_points[indices[npatch * 16 + narco * 4 + p]];
            }

            for (p = 0; p < 4 && narco == 2; p++) {
                p2[narco][p] = control_points[indices[npatch * 16 + narco * 4 + p]];
            }

            for (p = 0; p < 4 && narco == 3; p++) {
                p3[narco][p] = control_points[indices[npatch * 16 + narco * 4 + p]];
            }
        }

        //Um patch pronto para o algoritmo de Casteljau.
        calcBezierPoints(tess, p0, p1, p2, p3);
    }
}







