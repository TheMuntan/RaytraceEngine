//
// Created by muntan on 27/10/22.
//

#ifndef RAYTRACEENGINE_RAY_H
#define RAYTRACEENGINE_RAY_H

#include "Coordinate.h"

using namespace std;

class Ray {
    Coordinate origin;
    Coordinate direction;
public:
    Ray(const Coordinate origin, const Coordinate direction);

    Ray();

    const Coordinate getOrigin() const;
    const Coordinate getDirection() const;

    void setOrigin(Coordinate origin);

    void setDirection(Coordinate direction);
};


#endif //RAYTRACEENGINE_RAY_H
