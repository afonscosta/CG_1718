
#ifndef ENGINE_LIGHT_H
#define ENGINE_LIGHT_H


#include "Point.h"

class Light {

private:
    Point pos;
    char *type;

public:
    char *getType() const;

    void setType(char *type);

    const Point &getPos() const;

    void setPos(const Point &pos);

    void turnOnLight(int numLight);
};


#endif //ENGINE_LIGHT_H
