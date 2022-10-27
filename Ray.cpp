//
// Created by muntan on 27/10/22.
//

#include "Ray.h"

Ray::Ray(const Coordinate origin, const Coordinate direction) : origin(origin), direction(direction) {
    if (direction.isPoint())
        Ray::direction.setCoords(direction.getX()-origin.getX(), direction.getY()-origin.getY(), direction.getZ()-origin.getZ(), direction.isPoint()-origin.isPoint());
}

const Coordinate Ray::getOrigin() const {
    return origin;
}
const Coordinate Ray::getDirection() const {
    return direction;
}

void Ray::setOrigin(Coordinate origin) {
    Ray::origin = origin;
}

void Ray::setDirection(Coordinate direction) {
    Ray::direction = direction;
}
