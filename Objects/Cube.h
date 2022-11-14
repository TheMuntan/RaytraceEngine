//
// Created by muntan on 28/10/22.
//

#ifndef RAYTRACEENGINE_CUBE_H
#define RAYTRACEENGINE_CUBE_H


#include <array>
#include "Object.h"
#include "../Ray.h"

using namespace std;

class Cube : public Object {
    array<float, 6> t,u,v;

public:
    Cube(const Coordinate &center, float r, float g, float b, float a, float rotateX, float rotateY, float rotateZ, float scaleX,
         float scaleY, float scaleZ);

    Coordinate hit(Ray ray) override;

    vector<float> getShading(Coordinate hitLocation, Coordinate lightDirection) override;

};



#endif //RAYTRACEENGINE_CUBE_H