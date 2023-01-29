//
// Created by muntan on 27/01/23.
//

#ifndef RAYTRACEENGINE_CYLINDER_H
#define RAYTRACEENGINE_CYLINDER_H


#include "Object.h"

class Cylinder : public Object {

public:
    Cylinder(const Coordinate &center, float r, float g, float b, float a, float rotateX, float rotateY, float rotateZ, float scaleX,
         float scaleY, float scaleZ, float reflection, float transparency, float refraction, float roughness);

    Coordinate hit(Ray ray) override;

    Coordinate getNorm(Coordinate hitLocation) override;

    vector<float> getShading(Coordinate hitLocation, Coordinate lightDirection) override;

};


#endif //RAYTRACEENGINE_CYLINDER_H
