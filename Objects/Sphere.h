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
    Sphere(float radius, const Coordinate &center, int r, int g, int b, float rotateX, float rotateY, float rotateZ, float scaleX,
           float scaleY, float scaleZ);

    float getRadius() const;

    Coordinate hit(Ray ray);

};

#endif //RAYTRACEENGINE_SPHERE_H
