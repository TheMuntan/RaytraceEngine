//
// Created by muntan on 28/10/22.
//

#include "Cube.h"

Cube::Cube(const Coordinate &center, float r, float g, float b, float a, float rotateX, float rotateY, float rotateZ, float scaleX,
           float scaleY, float scaleZ) : Object(center, r, g, b, a, rotateX, rotateY, rotateZ, scaleX, scaleY, scaleZ) {}

Coordinate Cube::hit(Ray ray) {
    Coordinate failedHit(0, 0, 0, 0);
    Ray genRay = this->invRay(ray);

    // check top and bottom plane
        t[0] = (-genRay.getOrigin().getZ() - 0.5) / genRay.getDirection().getZ(); // find t for hit with z = -0.5 plane
        t[1] = (-genRay.getOrigin().getZ() + 0.5) / genRay.getDirection().getZ(); // find t for hit with z = +0.5 plane
        u[0] = (genRay.getOrigin().getX() + genRay.getDirection().getX() * t[0]); // get x and y coordinate by filling in the found t
        v[0] = (genRay.getOrigin().getY() + genRay.getDirection().getY() * t[0]);
        u[1] = (genRay.getOrigin().getX() + genRay.getDirection().getX() * t[1]);
        v[1] = (genRay.getOrigin().getY() + genRay.getDirection().getY() * t[1]);

    // check left and right plane
        t[2] = (-genRay.getOrigin().getX() - 0.5) / genRay.getDirection().getX(); // x = -0.5
        t[3] = (-genRay.getOrigin().getX() + 0.5) / genRay.getDirection().getX(); // x = +0.5
        u[2] = (genRay.getOrigin().getZ() + genRay.getDirection().getZ() * t[2]);
        v[2] = (genRay.getOrigin().getY() + genRay.getDirection().getY() * t[2]);
        u[3] = (genRay.getOrigin().getZ() + genRay.getDirection().getZ() * t[3]);
        v[3] = (genRay.getOrigin().getY() + genRay.getDirection().getY() * t[3]);

    // check front and back plane
        t[4] = (-genRay.getOrigin().getY() - 0.5) / genRay.getDirection().getY(); // y = -0.5
        t[5] = (-genRay.getOrigin().getY() + 0.5) / genRay.getDirection().getY(); // y = +0.5
        u[4] = (genRay.getOrigin().getX() + genRay.getDirection().getX() * t[4]);
        v[4] = (genRay.getOrigin().getZ() + genRay.getDirection().getZ() * t[4]);
        u[5] = (genRay.getOrigin().getX() + genRay.getDirection().getX() * t[5]);
        v[5] = (genRay.getOrigin().getZ() + genRay.getDirection().getZ() * t[5]);

    // find closest hit
    float tempU = 0.0, tempV = 0.0, tempT = INFINITY;
    int index = -1;

    for (int i=0;i<6;i++) {
        if ((t[i]<tempT) and (t[i]>0.0) and (abs(u[i])<=0.5) and (abs(v[i])<=0.5)) {
            tempT = t[i];
            tempU = u[i];
            tempV = v[i];
            index = i;
        }
    }

    if (index != -1) {
        float tempX = genRay.getOrigin().getX() + genRay.getDirection().getX() * tempT;
        float tempY = genRay.getOrigin().getY() + genRay.getDirection().getY() * tempT;
        float tempZ = genRay.getOrigin().getZ() + genRay.getDirection().getZ() * tempT;

        Coordinate i1 = calcRealCoords(tempX, tempY, tempZ ,1);
        return i1;
    }

    return failedHit;
}

vector<float> Cube::getShading(Coordinate hitLocation, Coordinate lightDirection) {
    vector<float> shading = getRgba();

    float tempX = (invMatrix[0][0] * hitLocation.getX() + invMatrix[0][1] * hitLocation.getY() +
                   invMatrix[0][2] * hitLocation.getZ() + invMatrix[0][3] * hitLocation.isPoint());
    float tempY = (invMatrix[1][0] * hitLocation.getX() + invMatrix[1][1] * hitLocation.getY() +
                   invMatrix[1][2] * hitLocation.getZ() + invMatrix[1][3] * hitLocation.isPoint());
    float tempZ = (invMatrix[2][0] * hitLocation.getX() + invMatrix[2][1] * hitLocation.getY() +
                   invMatrix[2][2] * hitLocation.getZ() + invMatrix[2][3] * hitLocation.isPoint());

    Coordinate norm;
    if (tempX > 0.99) {
        Coordinate normTemp(0.5,0.0,0.0,0);
        norm = normTemp;
    } else if (tempX < -0.99) {
        Coordinate normTemp(-0.5,0.0,0.0,0);
        norm = normTemp;
    } else if (tempY > 0.99) {
        Coordinate normTemp(0.0,0.5,0.0,0);
        norm = normTemp;
    } else if (tempY < -0.99) {
        Coordinate normTemp(0.0,-0.5,0.0,0);
        norm = normTemp;
    } else if (tempZ > 0.99) {
        Coordinate normTemp(0.0,0.0,0.5,0);
        norm = normTemp;
    } else if (tempZ < -0.99) {
        Coordinate normTemp(0.0,0.0,-0.5,0);
        norm = normTemp;
    }

    tempX = (invMatrix[0][0] * norm.getX() + invMatrix[0][1] * norm.getY() +
             invMatrix[0][2] * norm.getZ() + invMatrix[0][3] * norm.isPoint());
    tempY = (invMatrix[1][0] * norm.getX() + invMatrix[1][1] * norm.getY() +
             invMatrix[1][2] * norm.getZ() + invMatrix[1][3] * norm.isPoint());
    tempZ = (invMatrix[2][0] * norm.getX() + invMatrix[2][1] * norm.getY() +
             invMatrix[2][2] * norm.getZ() + invMatrix[2][3] * norm.isPoint());
    Coordinate normDirection(tempX, tempY, tempZ, 0);

    shading[3] = 1.0;
    normDirection.normalise();

    float angleLight = acos(normDirection.dot(lightDirection));


    if (angleLight > 2) { // angle too big default=1.5708
        shading[3] = 0.001;
    } else {
        shading[3] = 1.0 - (angleLight/2);
    }

    return shading;
}
