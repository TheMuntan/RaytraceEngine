//
// Created by muntan on 28/10/22.
//

#include "Cube.h"

Cube::Cube(const Coordinate &center, float r, float g, float b, float a, float rotateX, float rotateY, float rotateZ, float scaleX,
           float scaleY, float scaleZ, float reflection, float transparency, float refraction, float roughness) : Object(center, r, g, b, a, rotateX,
                                                                                                        rotateY, rotateZ, scaleX, scaleY, scaleZ,
                                                                                                        reflection, transparency, refraction, roughness) {}

Coordinate Cube::hit(Ray ray) {
    Coordinate failedHit(0, 0, 0, 0);
    Ray genRay(invCoordinate(ray.getOrigin()), invCoordinate(ray.getDirection()));
    array<float, 6> t,u,v;

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

        Coordinate tempI1(tempX, tempY, tempZ ,1);
        Coordinate i1 = transformCoordinate(tempI1);
        return i1;
    }

    return failedHit;
}

Coordinate Cube::getNorm(Coordinate hitLocation) {
    float noiseX = ((float) rand() / (RAND_MAX)) - 0.5;
    float noiseY = ((float) rand() / (RAND_MAX)) - 0.5;
    float noiseZ = ((float) rand() / (RAND_MAX)) - 0.5;

    Coordinate invLocation = invCoordinate(hitLocation);

    Coordinate invNorm;
    if (invLocation.getX() > 0.4999) {
        Coordinate normTemp(0.5,0.0,0.0,0);
        invNorm = normTemp;
    } else if (invLocation.getX() < -0.4999) {
        Coordinate normTemp(-0.5,0.0,0.0,0);
        invNorm = normTemp;
    } else if (invLocation.getY() > 0.4999) {
        Coordinate normTemp(0.0,0.5,0.0,0);
        invNorm = normTemp;
    } else if (invLocation.getY() < -0.4999) {
        Coordinate normTemp(0.0,-0.5,0.0,0);
        invNorm = normTemp;
    } else if (invLocation.getZ() > 0.4999) {
        Coordinate normTemp(0.0,0.0,0.5,0);
        invNorm = normTemp;
    } else if (invLocation.getZ() < -0.4999) {
        Coordinate normTemp(0.0,0.0,-0.5,0);
        invNorm = normTemp;
    }
    invNorm.setCoords(invNorm.getX() + noiseX * this->getRoughness(), invNorm.getY() + noiseY * this->getRoughness(),
                      invNorm.getZ() + noiseZ * this->getRoughness(),invNorm.isPoint());
    invNorm.normalise();

    Coordinate norm = transformCoordinate(invNorm);
    norm.normalise();

    return norm;
}

vector<float> Cube::getShading(Coordinate hitLocation, Coordinate lightDirection) {
    vector<float> shading = getRgba();

    Coordinate normDirection = getNorm(hitLocation);

    float angleLight = acos(normDirection.dot(lightDirection));

    if (angleLight > 2) { // angle too big default=1.5708
        shading[3] = 0.001;
    } else {
        shading[3] = 1.0 - (angleLight/2);
    }

    return shading;
}
