//
// Created by muntan on 27/10/22.
//

#include "Sphere.h"
#include "cmath"

Sphere::Sphere(float radius, const Coordinate &center, int r, int g, int b, float rotateX, float rotateY, float rotateZ, float scaleX,
               float scaleY, float scaleZ) : Object(center, r, g, b, rotateX, rotateY, rotateZ, scaleX*radius, scaleY*radius, scaleZ*radius), radius(radius) {}

Coordinate Sphere::hit(Ray ray) { // first index is row, second index is column
    Coordinate failedHit(0, 0, 0, 0);
    Ray genRay = this->invRay(ray);

    float A = pow(genRay.getDirection().getX(), 2) + pow(genRay.getDirection().getY(), 2) +
              pow(genRay.getDirection().getZ(), 2);
    float B = (2 * genRay.getOrigin().getX() * genRay.getDirection().getX()) +
              (2 * genRay.getOrigin().getY() * genRay.getDirection().getY()) +
              (2 * genRay.getOrigin().getZ() * genRay.getDirection().getZ());
    float C = pow(genRay.getOrigin().getX(), 2) + pow(genRay.getOrigin().getY(), 2) + pow(genRay.getOrigin().getZ(), 2) - 1;

    float discrim = B * B - 4 * A * C;

    if (discrim < 0) {
        //cout << endl << "No hit." << endl;
        Coordinate temp(0, 0, 0, 0);
        return failedHit; //returns a coordinate with 0 as the last value when no hit is found
    }

    float t1 = (-B - sqrt(discrim)) / (2 * A);
    float t2 = (-B + sqrt(discrim)) / (2 * A);

    if (t1 < 0.0 or t2 < 0.0) {
        //cout << endl << "No hit." << endl;
        return failedHit; //returns a coordinate with 0 as the last value when no hit is found

    }

    if (t1 < t2) {
        float tempX = genRay.getOrigin().getX() + genRay.getDirection().getX() * t1;
        float tempY = genRay.getOrigin().getY() + genRay.getDirection().getY() * t1;
        float tempZ = genRay.getOrigin().getZ() + genRay.getDirection().getZ() * t1;

        Coordinate i1 = calcRealCoords(tempX, tempY, tempZ ,1);
        return i1;
    } else {

        float tempX = genRay.getOrigin().getX() + genRay.getDirection().getX() * t2;
        float tempY = genRay.getOrigin().getY() + genRay.getDirection().getY() * t2;
        float tempZ = genRay.getOrigin().getZ() + genRay.getDirection().getZ() * t2;


        Coordinate i2 = calcRealCoords(tempX, tempY, tempZ ,1);
        return i2;
    }
    return failedHit;
}

float Sphere::getRadius() const {
    return radius;
};
