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
    Cube(const Coordinate &center, int r, int g, int b, float rotateX, float rotateY, float rotateZ, float scaleX,
         float scaleY, float scaleZ);

    Coordinate hit(Ray ray);


};



#endif //RAYTRACEENGINE_CUBE_H
