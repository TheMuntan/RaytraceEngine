//
// Created by muntan on 27/10/22.
//

#ifndef RAYTRACEENGINE_OBJECT_H
#define RAYTRACEENGINE_OBJECT_H

#include <iostream>
#include <vector>
#include "../Coordinate.h"
#include "cmath"
#include "../Ray.h"

using namespace std;

class Object {
    Coordinate center;
    float r,g,b,a;
    float rotateX, rotateY, rotateZ;
    float scaleX, scaleY, scaleZ;
    float reflection;
    float transparency;
    float refraction;
    vector<float> rgba;
public:
    float matrix[4][4];
    float invMatrix[4][4];

    Object(const Coordinate &center, float r, float g, float b, float a, float rotateX, float rotateY, float rotateZ, float scaleX,
           float scaleY, float scaleZ, float reflection, float transparency, float refraction);

    float getA() const;

    const Coordinate getCenter() const;

    int getR() const;

    int getG() const;

    int getB() const;

    void setRotateX(float rotateX);

    const vector<float> &getRgba() const;

    void setRotateY(float rotateY);

    void setRotateZ(float rotateZ);

    float getTransparency() const;

    float getReflection() const;

    virtual Coordinate hit(Ray ray);

    virtual vector<float> getShading(Coordinate hitLocation, Coordinate lightDirection) =0;

    virtual Coordinate getNorm(Coordinate hitLocation) =0;

    float getRefraction() const;

    Coordinate reflect(Coordinate hitLocation, Coordinate lookVector);

    Coordinate refract(Coordinate hitLocation, Coordinate lookVector);

    Coordinate invCoordinate(Coordinate coord);

    Coordinate transformCoordinate(Coordinate coord);
};


#endif //RAYTRACEENGINE_OBJECT_H
