//
// Created by muntan on 28/01/23.
//

#ifndef RAYTRACEENGINE_CONE_H
#define RAYTRACEENGINE_CONE_H

#include "Object.h"

class Cone : public Object {
public:
    Cone(const Coordinate &center, float r, float g, float b, float a, float rotateX, float rotateY, float rotateZ, float scaleX,
             float scaleY, float scaleZ, float reflection, float transparency, float refraction);

    Coordinate hit(Ray ray) override;

    Coordinate getNorm(Coordinate hitLocation) override;

    vector<float> getShading(Coordinate hitLocation, Coordinate lightDirection) override;

};


#endif //RAYTRACEENGINE_CONE_H
