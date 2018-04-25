//
// Created by afonscosta on 08-04-2018.
//

#ifndef ENGINE_GROUP_H
#define ENGINE_GROUP_H


#include "Point.h"
#include "Model.h"
#include "Translate.h"
#include <vector>
using std::vector;

class Group {
    vector<char> order;
    Translate translate;
    float angle;
    Point rotate;
    Point scale;
    vector<Model> models;
    vector<Group *> groups;
private:
    void doTranslate();
    void doRotate();
    void doScale();
    void drawModels();
public:
    void addOrder(char);
    void setTranslate (Translate t); //Null = 0, 0, 0
    void setRotate (float, Point); //Null = 0, 0, 0, 0
    void setScale (Point); //Null = 0, 0, 0
    void setModels (vector<Model>); //Null = vector vazio
    void addGroup (Group*); //Null = vector vazio
    void drawGroup();
};


#endif //ENGINE_GROUP_H
