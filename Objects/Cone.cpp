//
// Created by muntan on 28/01/23.
//

#include "Cone.h"
#include <array>

Cone::Cone(const Coordinate &center, float r, float g, float b, float a, float rotateX, float rotateY,
                   float rotateZ, float scaleX, float scaleY, float scaleZ, float reflection, float transparency,
                   float refraction, float roughness) : Object(center, r, g, b, a, rotateX, rotateY, rotateZ, scaleX, scaleY, scaleZ,
                                              reflection, transparency, refraction, roughness) {}

Coordinate Cone::hit(Ray ray) {
    Coordinate failedHit(0, 0, 0, 0);
    Ray genRay(invCoordinate(ray.getOrigin()), invCoordinate(ray.getDirection()));
    float t0;

    // check lower plane first. (abs(x,y) < 0.5) z == 0
    t0 = (-genRay.getOrigin().getZ() - 1) / genRay.getDirection().getZ(); // find t for hit with z = -1 plane
    Coordinate tempI1;

    if (t0 > 0.0) {
        float tempX1 = genRay.getOrigin().getX() + genRay.getDirection().getX() * t0;
        float tempY1 = genRay.getOrigin().getY() + genRay.getDirection().getY() * t0;
        float tempZ1 = genRay.getOrigin().getZ() + genRay.getDirection().getZ() * t0;
        tempI1 = Coordinate(tempX1, tempY1, tempZ1, 1);
    }
    if ((pow(tempI1.getX(),2) + pow(tempI1.getY(),2) <= 1) and t0 > 0.0 and genRay.getOrigin().getZ() < tempI1.getZ()) {
        transformCoordinate(tempI1);
        return tempI1;
    }

    float A = pow(genRay.getDirection().getX(), 2) +
              pow(genRay.getDirection().getY(), 2) -
              pow(genRay.getDirection().getZ(), 2);
    float B = 2 * (genRay.getOrigin().getX() * genRay.getDirection().getX() +
              genRay.getOrigin().getY() * genRay.getDirection().getY() -
              genRay.getOrigin().getZ() * genRay.getDirection().getZ());
    float C = pow(genRay.getOrigin().getX(), 2) +
                pow(genRay.getOrigin().getY(), 2) -
                pow(genRay.getOrigin().getZ(), 2);

    float discrim = B * B - 4 * A * C;

    if (discrim < 0) {
        return failedHit; //returns a coordinate with 0 as the last value when no hit is found
    }

    float t1 = (-B - sqrt(discrim)) / (2 * A);
    float t2 = (-B + sqrt(discrim)) / (2 * A);
    float tempZ1 = genRay.getOrigin().getZ() + genRay.getDirection().getZ() * t1;
    float tempZ2 = genRay.getOrigin().getZ() + genRay.getDirection().getZ() * t2;

    if (t1 < t2 and t1 > 0.0 and tempZ1 >= -1.0 and tempZ1 <= 0.0) {
        float tempX = genRay.getOrigin().getX() + genRay.getDirection().getX() * t1;
        float tempY = genRay.getOrigin().getY() + genRay.getDirection().getY() * t1;

        Coordinate tempI1(tempX, tempY, tempZ1 ,1);
        Coordinate i1 = transformCoordinate(tempI1);
        return i1;
    } else if (t2 > 0.0 and tempZ2 >= -1.0 and tempZ2 <= 0.0){
        float tempX = genRay.getOrigin().getX() + genRay.getDirection().getX() * t2;
        float tempY = genRay.getOrigin().getY() + genRay.getDirection().getY() * t2;

        Coordinate tempI2(tempX, tempY, tempZ2 ,1);
        Coordinate i2 = transformCoordinate(tempI2);
        return i2;
    }

    return failedHit;
}

Coordinate Cone::getNorm(Coordinate hitLocation) {
    float noiseX = ((float) rand() / (RAND_MAX)) - 0.5;
    float noiseY = ((float) rand() / (RAND_MAX)) - 0.5;
    float noiseZ = ((float) rand() / (RAND_MAX)) - 0.5;
    Coordinate invLocation = invCoordinate(hitLocation);
    if (invLocation.getZ() <= -0.9999) { // check if we are on the bottom of the Cone
        Coordinate invNorm(0.0,0.0,-0.5,0);
        invNorm.normalise();
        invNorm.setCoords(invNorm.getX() + noiseX * this->getRoughness(), invNorm.getY() + noiseY * this->getRoughness(),
                          invNorm.getZ() + noiseZ * this->getRoughness(),invNorm.isPoint());
        invNorm.normalise();
        Coordinate norm = transformCoordinate(invNorm);
        norm.normalise();
        return norm;
    }

    Coordinate center(0.0,0.0,-1,1);
    Coordinate invNorm = invLocation - center;
    invNorm.normalise();
    invNorm.setCoords(invNorm.getX() + noiseX * this->getRoughness(), invNorm.getY() + noiseY * this->getRoughness(),
                      invNorm.getZ() + noiseZ * this->getRoughness(),invNorm.isPoint());
    invNorm.normalise();
    Coordinate norm = transformCoordinate(invNorm);
    norm.normalise();
    return norm;
}

vector<float> Cone::getShading(Coordinate hitLocation, Coordinate lightDirection) {
    vector<float> shading = getRgba();

    Coordinate normDirection = getNorm(hitLocation);
//    Coordinate normDirection = hitLocation - getCenter();

    float angleLight = acos(normDirection.dot(lightDirection));


    if (angleLight > 2) { // angle too big default=1.5708
        shading[3] = 0.001;
    } else {
        shading[3] = 1.0 - (angleLight/1.5708);
    }


    return shading;
}