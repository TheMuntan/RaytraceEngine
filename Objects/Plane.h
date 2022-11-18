//
// Created by muntan on 28/10/22.
//

#ifndef RAYTRACEENGINE_PLANE_H
#define RAYTRACEENGINE_PLANE_H


#include "Object.h"

class Plane : public Object {
public:
    Plane(const Coordinate &center, float r, float g, float b, float a, float rotateX, float rotateY, float rotateZ,
          float scaleX, float scaleY, float scaleZ, float reflection, float transparency, float refraction);

    Coordinate hit(Ray ray) override;

    vector<float> getShading(Coordinate hitLocation, Coordinate lightDirection) override;

    Coordinate getNorm(Coordinate hitLocation) override;

};


#endif //RAYTRACEENGINE_PLANE_H
