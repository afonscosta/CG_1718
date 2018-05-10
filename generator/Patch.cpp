
#include "Patch.h"

void Patch::setTesselation(int tess) {
    this->tess = tess;
}

vector<Point> Patch::getCurve_points() const {
    return curve_points;
}

void Patch::split(const std::string& s, char delim,vector<std::string>& v) {
    auto i = 0;
    auto pos = s.find(delim);
    while (pos != std::string::npos) {
        v.push_back(s.substr(i, pos-i));
        i = static_cast<int>(++pos);
        pos = s.find(delim, pos);

        if (pos == std::string::npos)
            v.push_back(s.substr(i, s.length()));
    }
}

void Patch::parse_patch(char* file_name) {

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
            p.setPoint(strtof(aux[0].c_str(), nullptr), strtof(aux[1].c_str(), nullptr), strtof(aux[2].c_str(), nullptr));

            control_points.push_back(p);
        }

        fs.close();
    }
}

void Patch::multMatrixVector(float *m, float *v, float *res) {

    for (int j = 0; j < 4; ++j) {
        res[j] = 0;
        for (int k = 0; k < 4; ++k) {
            res[j] += v[k] * m[j * 4 + k];
        }
    }

}

float Patch::calcBezierPoint(float *P, float *M, float U[4], float V[4]) {
    float res0 = 0;
    float res1[4] = {0, 0, 0, 0};
    float res2[4] = {0, 0, 0, 0};
    float res3[4] = {0, 0, 0, 0};


    multMatrixVector(M, U, res1); //U * M
    multMatrixVector(P, res1, res2); //U * M * P
    multMatrixVector(M, res2, res3); //U * M * P * Mt
    res0 = res3[0] * V[0] + res3[1] * V[1] + res3[2] * V[2] + res3[3] * V[3]; //U * M * P * Mt * V

    return res0;
}

void Patch::calcPointsSurface(float *M, float *Px, float *Py, float *Pz) {

    Point p0, p1, p2, p3;

    float U[4];
    float V[4];
    float Up[4];
    float Vp[4];

    float pu, pv, pup, pvp;
    float passo = 1.0f / (float) tess;

    for (int u = 0; u < tess; u++) {
        for (int v = 0; v < tess; v++) {

            pu = u * passo;
            pv = v * passo;

            pup = (u+1) * passo;
            pvp = (v+1) * passo;

            U[0] = pow(pu, 3.0f);
            U[1] = pow(pu, 2.0f);
            U[2] = pu;
            U[3] = 1;

            V[0] = pow(pv, 3.0f);
            V[1] = pow(pv, 2.0f);
            V[2] = pv;
            V[3] = 1;

            Up[0] = pow(pup, 3.0f);
            Up[1] = pow(pup, 2.0f);
            Up[2] = pup;
            Up[3] = 1;

            Vp[0] = pow(pvp, 3.0f);
            Vp[1] = pow(pvp, 2.0f);
            Vp[2] = pvp;
            Vp[3] = 1;

            //v, u
            p0.setPoint(calcBezierPoint(Px, M, U, V), calcBezierPoint(Py, M, U, V), calcBezierPoint(Pz, M, U, V));

            //v + passo, u
            p1.setPoint(calcBezierPoint(Px, M, U, Vp), calcBezierPoint(Py, M, U, Vp), calcBezierPoint(Pz, M, U, Vp));

            //v, u+passo
            p2.setPoint(calcBezierPoint(Px, M, Up, V), calcBezierPoint(Py, M, Up, V), calcBezierPoint(Pz, M, Up, V));

            //v+passo, u+passo
            p3.setPoint(calcBezierPoint(Px, M, Up, Vp), calcBezierPoint(Py, M, Up, Vp), calcBezierPoint(Pz, M, Up, Vp));

            curve_points.push_back(p0);
            curve_points.push_back(p2);
            curve_points.push_back(p3);

            curve_points.push_back(p0);
            curve_points.push_back(p3);
            curve_points.push_back(p1);

        }
    }


}

void Patch::calcBezierPoints(Point p0[], Point p1[], Point p2[], Point p3[]) {

    float Px[4][4] = { {p0[0].getX(), p0[1].getX(), p0[2].getX(), p0[3].getX()},
                       {p1[0].getX(), p1[1].getX(), p1[2].getX(), p1[3].getX()},
                       {p2[0].getX(), p2[1].getX(), p2[2].getX(), p2[3].getX()},
                       {p3[0].getX(), p3[1].getX(), p3[2].getX(), p3[3].getX()} };

    float Py[4][4] = { {p0[0].getY(), p0[1].getY(), p0[2].getY(), p0[3].getY()},
                       {p1[0].getY(), p1[1].getY(), p1[2].getY(), p1[3].getY()},
                       {p2[0].getY(), p2[1].getY(), p2[2].getY(), p2[3].getY()},
                       {p3[0].getY(), p3[1].getY(), p3[2].getY(), p3[3].getY()} };

    float Pz[4][4] = { {p0[0].getZ(), p0[1].getZ(), p0[2].getZ(), p0[3].getZ()},
                       {p1[0].getZ(), p1[1].getZ(), p1[2].getZ(), p1[3].getZ()},
                       {p2[0].getZ(), p2[1].getZ(), p2[2].getZ(), p2[3].getZ()},
                       {p3[0].getZ(), p3[1].getZ(), p3[2].getZ(), p3[3].getZ()} };

    float M[4][4] = { {-1.0f,  3.0f, -3.0f, 1.0f},
                      { 3.0f, -6.0f,  3.0f, 0.0f},
                      {-3.0f,  3.0f,  0.0f, 0.0f},
                      { 1.0f,  0.0f,  0.0f, 0.0f} };

    calcPointsSurface((float *) M, (float *) Px, (float *) Py, (float *) Pz);
}

void Patch::generateBezier() {

    int npatch;
    int narco;
    int p;

    Point p0[4];
    Point p1[4];
    Point p2[4];
    Point p3[4];

    for (npatch = 0; npatch < num_patches; npatch++) {

        //Coloca os pontos de controlo no p0, p1, p2 e p3.
        for (narco = 0; narco < 4; narco++) {
            for (p = 0; p < 4 && narco == 0; p++) {
                p0[p] = control_points[indices[npatch * 16 + narco * 4 + p]];
            }

            for (p = 0; p < 4 && narco == 1; p++) {
                p1[p] = control_points[indices[npatch * 16 + narco * 4 + p]];
            }

            for (p = 0; p < 4 && narco == 2; p++) {
                p2[p] = control_points[indices[npatch * 16 + narco * 4 + p]];
            }

            for (p = 0; p < 4 && narco == 3; p++) {
                p3[p] = control_points[indices[npatch * 16 + narco * 4 + p]];
            }
        }

        //Um patch pronto para o algoritmo de Casteljau.
        calcBezierPoints(p0, p1, p2, p3);
    }
}







