
#ifndef ENGINE_GROUP_H
#define ENGINE_GROUP_H


#include "Point.h"
#include "Model.h"
#include "Translate.h"
#include "Light.h"
#include <vector>
using std::vector;

class Group {
    vector<char> order;
    Translate translate;
    int tipoRotate;
    float paramRotate;
    Point rotate;
    Point scale;
    vector<Model> models;
    vector<Group *> groups;
    vector<Light> lights;
public:
    void setLights(const vector<Light> &lights);

private:
    void doTranslate(int i);
    void doRotate();
    void doScale();
    void drawModels();

public:
    void addOrder(char);
    void setTranslate (Translate t); //Null = 0, 0, 0
    void setRotate(float t, Point p, int tipo);
    void setScale (Point); //Null = 0, 0, 0
    void setModels (vector<Model>); //Null = vector vazio
    void addGroup (Group*); //Null = vector vazio
    void drawGroup(int curveOff);

};


#endif //ENGINE_GROUP_H
