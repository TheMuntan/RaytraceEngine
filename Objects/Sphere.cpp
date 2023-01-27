//
// Created by muntan on 27/10/22.
//

#include "Sphere.h"
#include "cmath"
#include <iostream>


using namespace std;

Sphere::Sphere(float radius, const Coordinate &center, float r, float g, float b, float a, float rotateX, float rotateY, float rotateZ, float scaleX,
               float scaleY, float scaleZ, float reflection, float transparency, float refraction) :
               Object(center, r, g, b, a, rotateX, rotateY, rotateZ, scaleX*radius, scaleY*radius, scaleZ*radius, reflection, transparency, refraction), radius(radius) {}

Coordinate Sphere::hit(Ray ray) { // first index is row, second index is column
    Coordinate failedHit(0, 0, 0, 0);
    Ray genRay(invCoordinate(ray.getOrigin()), invCoordinate(ray.getDirection()));

    float A = pow(genRay.getDirection().getX(), 2) + pow(genRay.getDirection().getY(), 2) +
              pow(genRay.getDirection().getZ(), 2);
    float B = (2 * genRay.getOrigin().getX() * genRay.getDirection().getX()) +
              (2 * genRay.getOrigin().getY() * genRay.getDirection().getY()) +
              (2 * genRay.getOrigin().getZ() * genRay.getDirection().getZ());
    float C = pow(genRay.getOrigin().getX(), 2) + pow(genRay.getOrigin().getY(), 2) + pow(genRay.getOrigin().getZ(), 2) - 1; // 1 is radius squared

    float discrim = B * B - 4 * A * C;

    if (discrim < 0) {
        return failedHit; //returns a coordinate with 0 as the last value when no hit is found
    }

    float t1 = (-B - sqrt(discrim)) / (2 * A);
    float t2 = (-B + sqrt(discrim)) / (2 * A);

//    if (t1 < 0.0 or t2 < 0.0) {
//        return failedHit; //returns a coordinate with 0 as the last value when no hit is found
//    }

    if (t1 < t2 and t1 > 0.0) {
        float tempX = genRay.getOrigin().getX() + genRay.getDirection().getX() * t1;
        float tempY = genRay.getOrigin().getY() + genRay.getDirection().getY() * t1;
        float tempZ = genRay.getOrigin().getZ() + genRay.getDirection().getZ() * t1;

        Coordinate tempI1(tempX, tempY, tempZ ,1);
        Coordinate i1 = transformCoordinate(tempI1);
        return i1;
    } else if (t2 > 0.0) {

        float tempX = genRay.getOrigin().getX() + genRay.getDirection().getX() * t2;
        float tempY = genRay.getOrigin().getY() + genRay.getDirection().getY() * t2;
        float tempZ = genRay.getOrigin().getZ() + genRay.getDirection().getZ() * t2;

        Coordinate tempI2(tempX, tempY, tempZ ,1);
        Coordinate i2 = transformCoordinate(tempI2);
        return i2;
    }
    return failedHit;
}


Coordinate Sphere::getNorm(Coordinate hitLocation) {

    Coordinate invLocation = invCoordinate(hitLocation);
    Coordinate center(0.0,0.0,0.0,1);
    Coordinate invNorm = invLocation - center;
    invNorm.normalise();
    Coordinate norm = transformCoordinate(invNorm);
    norm.normalise();
//    float randoms = static_cast <float> (rand())/static_cast <float> (RAND_MAX);
//    float randoms2 = static_cast <float> (rand())/static_cast <float> (RAND_MAX);
//    float randoms3 = static_cast <float> (rand())/static_cast <float> (RAND_MAX);
//    Coordinate rough(norm.getX() + randoms/100.0-0.005, norm.getY()+ randoms2/100.0-0.005, norm.getZ()+ randoms3/100.0-0.005, 0);
//    rough.normalise();
    return norm;
}

vector<float> Sphere::getShading(Coordinate hitLocation, Coordinate lightDirection) {
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

