//
// Created by muntan on 27/01/23.
//

#include <array>
#include "Cylinder.h"

Cylinder::Cylinder(const Coordinate &center, float r, float g, float b, float a, float rotateX, float rotateY,
                   float rotateZ, float scaleX, float scaleY, float scaleZ, float reflection, float transparency,
                   float refraction) : Object(center, r, g, b, a, rotateX, rotateY, rotateZ, scaleX, scaleY, scaleZ,
                                              reflection, transparency, refraction) {}

Coordinate Cylinder::hit(Ray ray) {
    Coordinate failedHit(0, 0, 0, 0);
    Ray genRay(invCoordinate(ray.getOrigin()), invCoordinate(ray.getDirection()));
    array<float, 2> t;

    // check upper and lower plane first. (abs(x,y) < 0.5) z == -0.5 and z == 0.5
    t[0] = (-genRay.getOrigin().getZ() - 0.5) / genRay.getDirection().getZ(); // find t for hit with z = -0.5 plane
    t[1] = (-genRay.getOrigin().getZ() + 0.5) / genRay.getDirection().getZ(); // find t for hit with z = +0.5 plane
    Coordinate tempI1, tempI2;

    if (t[0] > 0.0) {
        float tempX1 = genRay.getOrigin().getX() + genRay.getDirection().getX() * t[0];
        float tempY1 = genRay.getOrigin().getY() + genRay.getDirection().getY() * t[0];
        float tempZ1 = genRay.getOrigin().getZ() + genRay.getDirection().getZ() * t[0];
        tempI1 = Coordinate(tempX1, tempY1, tempZ1, 1);
    }
    if (t[1] > 0.0) {
        float tempX2 = genRay.getOrigin().getX() + genRay.getDirection().getX() * t[1];
        float tempY2 = genRay.getOrigin().getY() + genRay.getDirection().getY() * t[1];
        float tempZ2 = genRay.getOrigin().getZ() + genRay.getDirection().getZ() * t[1];
        tempI2 = Coordinate(tempX2, tempY2, tempZ2, 1);
    }
    if ((pow(tempI1.getX(),2) + pow(tempI1.getY(),2) <= 1) and t[0] > 0.0 and genRay.getOrigin().getZ() < tempI1.getZ()) {
        transformCoordinate(tempI1);
        return tempI1;
    } else if ((pow(tempI2.getX(),2) + pow(tempI2.getY(),2) <= 1) and t[1] > 0.0 and genRay.getOrigin().getZ() > tempI2.getZ()) {
        transformCoordinate(tempI2);
        return tempI2;
    }


    float A = pow(genRay.getDirection().getX(), 2) +
              pow(genRay.getDirection().getY(), 2);
    float B = (2 * genRay.getOrigin().getX() * genRay.getDirection().getX()) +
              (2 * genRay.getOrigin().getY() * genRay.getDirection().getY());
    float C = pow(genRay.getOrigin().getX(), 2) + pow(genRay.getOrigin().getY(), 2) - 1; // 1 is radius squared

    float discrim = B * B - 4 * A * C;

    if (discrim < 0) {
        return failedHit; //returns a coordinate with 0 as the last value when no hit is found
    }

    float t1 = (-B - sqrt(discrim)) / (2 * A);
    float t2 = (-B + sqrt(discrim)) / (2 * A);
    float tempZ1 = genRay.getOrigin().getZ() + genRay.getDirection().getZ() * t1;
    float tempZ2 = genRay.getOrigin().getZ() + genRay.getDirection().getZ() * t2;

    if (t1 < t2 and t1 > 0.0 and abs(tempZ1) < 0.5) {
        float tempX = genRay.getOrigin().getX() + genRay.getDirection().getX() * t1;
        float tempY = genRay.getOrigin().getY() + genRay.getDirection().getY() * t1;

        Coordinate tempI1(tempX, tempY, tempZ1 ,1);
        Coordinate i1 = transformCoordinate(tempI1);
        return i1;
    } else if (t2 > 0.0 and (abs(tempZ2) < 0.5)){
        float tempX = genRay.getOrigin().getX() + genRay.getDirection().getX() * t2;
        float tempY = genRay.getOrigin().getY() + genRay.getDirection().getY() * t2;

        Coordinate tempI2(tempX, tempY, tempZ2 ,1);
        Coordinate i2 = transformCoordinate(tempI2);
        return i2;
    }

    return failedHit;
}

Coordinate Cylinder::getNorm(Coordinate hitLocation) {
    Coordinate invLocation = invCoordinate(hitLocation);
    if (invLocation.getZ() >= 0.4999) { // check if we are on the top or bottom of the cylinder
        Coordinate invNorm(0.0,0.0,-0.5,0);
        invNorm.normalise();
        Coordinate norm = transformCoordinate(invNorm);
        norm.normalise();
        return norm;
    } else if (invLocation.getZ() <= -0.4999) {
        Coordinate invNorm(0.0,0.0,0.5,0);
        invNorm.normalise();
        Coordinate norm = transformCoordinate(invNorm);
        norm.normalise();
        return norm;
    }

    Coordinate center(0.0,0.0,0.0,1);
    Coordinate invNorm = invLocation - center;
    invNorm.normalise();
    invNorm.setCoords(invNorm.getX(),invNorm.getY(),0.0,invNorm.isPoint());
    Coordinate norm = transformCoordinate(invNorm);
    norm.normalise();
//    Coordinate norm(0.0,0.0,1.0,0);
    return norm;
}

vector<float> Cylinder::getShading(Coordinate hitLocation, Coordinate lightDirection) {
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