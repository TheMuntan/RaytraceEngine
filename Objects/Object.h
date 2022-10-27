//
// Created by muntan on 27/10/22.
//

#ifndef RAYTRACEENGINE_OBJECT_H
#define RAYTRACEENGINE_OBJECT_H

#include "../Coordinate.h"
#include "cmath"

using namespace std;

class Object {
    Coordinate center;
    int r,g,b;
    float rotateX, rotateY, rotateZ;
    float scaleX, scaleY, scaleZ;
public:
    float matrix[4][4];
    float invMatrix[4][4];

    Object(const Coordinate &center, int r, int g, int b, float rotateX, float rotateY, float rotateZ, float scaleX,
           float scaleY, float scaleZ);

    const Coordinate getCenter() const;

    int getR() const;

    int getG() const;

    int getB() const;

    void setRotateX(float rotateX);

    void setRotateY(float rotateY);

    void setRotateZ(float rotateZ);
};


#endif //RAYTRACEENGINE_OBJECT_H
