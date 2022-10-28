//
// Created by muntan on 28/10/22.
//

#include "Plane.h"

Plane::Plane(const Coordinate &center, float r, float g, float b, float a, float rotateX, float rotateY, float rotateZ,
             float scaleX, float scaleY, float scaleZ)
        : Object(center, r, g, b, a, rotateX, rotateY, rotateZ, scaleX, scaleY, scaleZ) {}

Coordinate Plane::hit(Ray ray) {
    Coordinate failedHit(0, 0, 0, 0);
    Ray genRay = this->invRay(ray);

    float t = -genRay.getOrigin().getZ() / genRay.getDirection().getZ();

    if (t > 0.0) {
        float tempX = genRay.getOrigin().getX() + genRay.getDirection().getX() * t;
        float tempY = genRay.getOrigin().getY() + genRay.getDirection().getY() * t;
        float tempZ = genRay.getOrigin().getZ() + genRay.getDirection().getZ() * t;

        Coordinate i1 = calcRealCoords(tempX, tempY, tempZ ,1);
        return i1;
    }

    return failedHit;
}

vector<float> Plane::getShading(Coordinate hitLocation, Coordinate lightDirection) {
    vector<float> shading = getRgba();

    vector<float> test = {1.0, 1.0, 1.0, 1.0};

    return test;
}
