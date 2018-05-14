
#ifndef ENGINE_LIGHT_H
#define ENGINE_LIGHT_H


#include "Point.h"

class Light {

private:
    Point pos;

public:
    char *type;

    char *getType() const;

    void setType(char *type);

    const Point &getPos() const;

    void setPos(const Point &pos);

    int turnOnLight(int numLight);
};


#endif //ENGINE_LIGHT_H
