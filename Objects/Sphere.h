//
// Created by muntan on 27/10/22.
//

#ifndef RAYTRACEENGINE_SPHERE_H
#define RAYTRACEENGINE_SPHERE_H


#include "Object.h"
#include "../Ray.h"

using namespace std;

class Sphere : public Object {
    float radius;
public:
    Sphere(float radius, const Coordinate &center, float r, float g, float b, float a, float rotateX, float rotateY, float rotateZ, float scaleX,
           float scaleY, float scaleZ);


    Coordinate hit(Ray ray) override;

    vector<float> getShading(Coordinate hitLocation, Coordinate lightDirection) override;

    Coordinate getNorm(Coordinate hitLocation);
};

#endif //RAYTRACEENGINE_SPHERE_H
