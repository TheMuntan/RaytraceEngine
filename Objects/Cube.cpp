//
// Created by muntan on 28/10/22.
//

#include "Cube.h"

Cube::Cube(const Coordinate &center, int r, int g, int b, float rotateX, float rotateY, float rotateZ, float scaleX,
           float scaleY, float scaleZ) : Object(center, r, g, b, rotateX, rotateY, rotateZ, scaleX, scaleY, scaleZ) {}

Coordinate Cube::hit(Ray ray) {
    Coordinate failedHit(0, 0, 0, 0);
    Ray genRay = this->invRay(ray);

    // check top and bottom plane
    t[0] = (genRay.getOrigin().getZ() - 1.0) / -genRay.getDirection().getZ();
    t[1] = (genRay.getOrigin().getZ() + 1.0) / -genRay.getDirection().getZ();
    u[0] = (genRay.getOrigin().getX() + genRay.getDirection().getX() * t[0]);
    v[0] = (genRay.getOrigin().getY() + genRay.getDirection().getY() * t[0]);
    u[1] = (genRay.getOrigin().getX() + genRay.getDirection().getX() * t[1]);
    v[1] = (genRay.getOrigin().getY() + genRay.getDirection().getY() * t[1]);

    // check left and right plane
    t[2] = (genRay.getOrigin().getX() + 1.0) / -genRay.getDirection().getX();
    t[3] = (genRay.getOrigin().getX() - 1.0) / -genRay.getDirection().getX();
    u[2] = (genRay.getOrigin().getZ() + genRay.getDirection().getZ() * t[2]);
    v[2] = (genRay.getOrigin().getY() + genRay.getDirection().getY() * t[2]);
    u[3] = (genRay.getOrigin().getZ() + genRay.getDirection().getZ() * t[3]);
    v[3] = (genRay.getOrigin().getY() + genRay.getDirection().getY() * t[3]);

    // check front and back plane
    t[4] = (genRay.getOrigin().getY() + 1.0) / -genRay.getDirection().getY();
    t[5] = (genRay.getOrigin().getY() - 1.0) / -genRay.getDirection().getY();
    u[4] = (genRay.getOrigin().getX() + genRay.getDirection().getX() * t[4]);
    v[4] = (genRay.getOrigin().getZ() + genRay.getDirection().getZ() * t[4]);
    u[5] = (genRay.getOrigin().getX() + genRay.getDirection().getX() * t[5]);
    v[5] = (genRay.getOrigin().getZ() + genRay.getDirection().getZ() * t[5]);


    // find closest hit
    float tempU = 0.0, tempV = 0.0, tempT = INFINITY;
    int index = -1;

    for (int i=0;i<6;i++) {
        if ((t[i]<tempT) and (t[i]>0.0) and (abs(u[i])<=1.0) and (abs(v[i])<=1.0)) {
            tempT = t[i];
            tempU = u[i];
            tempV = v[i];
            index = i;
        }
    }

    if (index!=-1) {
        float tempX = genRay.getOrigin().getX() + genRay.getDirection().getX() * tempT;
        float tempY = genRay.getOrigin().getY() + genRay.getDirection().getY() * tempT;
        float tempZ = genRay.getOrigin().getZ() + genRay.getDirection().getZ() * tempT;

        Coordinate i1 = calcRealCoords(tempX, tempY, tempZ ,1);
        return i1;
    }





    return failedHit;
}