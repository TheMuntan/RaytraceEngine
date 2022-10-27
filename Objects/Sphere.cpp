//
// Created by muntan on 27/10/22.
//

#include "Sphere.h"
#include "cmath"

Sphere::Sphere(float radius, const Coordinate &center, int r, int g, int b, float rotateX, float rotateY, float rotateZ, float scaleX,
               float scaleY, float scaleZ) : Object(center, r, g, b, rotateX, rotateY, rotateZ, scaleX*radius, scaleY*radius, scaleZ*radius), radius(radius) {}

Coordinate Sphere::hit(Ray ray) { // first index is row, second index is column
    Coordinate failedHit(0, 0, 0, 0);

    float tempX = (invMatrix[0][0] * ray.getOrigin().getX() + invMatrix[0][1] * ray.getOrigin().getY() +
                   invMatrix[0][2] * ray.getOrigin().getZ() + invMatrix[0][3] * ray.getOrigin().isPoint());
    float tempY = (invMatrix[1][0] * ray.getOrigin().getX() + invMatrix[1][1] * ray.getOrigin().getY() +
                   invMatrix[1][2] * ray.getOrigin().getZ() + invMatrix[1][3] * ray.getOrigin().isPoint());
    float tempZ = (invMatrix[2][0] * ray.getOrigin().getX() + invMatrix[2][1] * ray.getOrigin().getY() +
                   invMatrix[2][2] * ray.getOrigin().getZ() + invMatrix[2][3] * ray.getOrigin().isPoint());
    float tempP = (invMatrix[3][0] * ray.getOrigin().getX() + invMatrix[3][1] * ray.getOrigin().getY() +
                   invMatrix[3][2] * ray.getOrigin().getZ() + invMatrix[3][3] * ray.getOrigin().isPoint());
    Coordinate tempOrig(tempX, tempY, tempZ, tempP);
    tempX = (invMatrix[0][0] * ray.getDirection().getX() + invMatrix[0][1] * ray.getDirection().getY() +
             invMatrix[0][2] * ray.getDirection().getZ() + invMatrix[0][3] * ray.getDirection().isPoint());
    tempY = (invMatrix[1][0] * ray.getDirection().getX() + invMatrix[1][1] * ray.getDirection().getY() +
             invMatrix[1][2] * ray.getDirection().getZ() + invMatrix[1][3] * ray.getDirection().isPoint());
    tempZ = (invMatrix[2][0] * ray.getDirection().getX() + invMatrix[2][1] * ray.getDirection().getY() +
             invMatrix[2][2] * ray.getDirection().getZ() + invMatrix[2][3] * ray.getDirection().isPoint());
    tempP = (invMatrix[3][0] * ray.getDirection().getX() + invMatrix[3][1] * ray.getDirection().getY() +
             invMatrix[3][2] * ray.getDirection().getZ() + invMatrix[3][3] * ray.getDirection().isPoint());
    Coordinate tempDir(tempX, tempY, tempZ, tempP);

    Ray genRay(tempOrig, tempDir);

    float A = pow(genRay.getDirection().getX(), 2) + pow(genRay.getDirection().getY(), 2) +
              pow(genRay.getDirection().getZ(), 2);
    float B = (2 * genRay.getOrigin().getX() * genRay.getDirection().getX()) +
              (2 * genRay.getOrigin().getY() * genRay.getDirection().getY()) +
              (2 * genRay.getOrigin().getZ() * genRay.getDirection().getZ());
    float C =
            pow(genRay.getOrigin().getX(), 2) + pow(genRay.getOrigin().getY(), 2) + pow(genRay.getOrigin().getZ(), 2) -
            1; //pow(radius,2)

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
        tempX = genRay.getOrigin().getX() + genRay.getDirection().getX() * t1;
        tempY = genRay.getOrigin().getY() + genRay.getDirection().getY() * t1;
        tempZ = genRay.getOrigin().getZ() + genRay.getDirection().getZ() * t1;
        tempP = 1;

        float newX = (matrix[0][0] * tempX + matrix[0][1] * tempY + matrix[0][2] * tempZ + matrix[0][3] * tempP);
        float newY = (matrix[1][0] * tempX + matrix[1][1] * tempY + matrix[1][2] * tempZ + matrix[1][3] * tempP);
        float newZ = (matrix[2][0] * tempX + matrix[2][1] * tempY + matrix[2][2] * tempZ + matrix[2][3] * tempP);
        float newP = (matrix[3][0] * tempX + matrix[3][1] * tempY + matrix[3][2] * tempZ + matrix[3][3] * tempP);

        Coordinate i1(newX, newY, newZ, newP);
        return i1;
    } else {

        tempX = genRay.getOrigin().getX() + genRay.getDirection().getX() * t2;
        tempY = genRay.getOrigin().getY() + genRay.getDirection().getY() * t2;
        tempZ = genRay.getOrigin().getZ() + genRay.getDirection().getZ() * t2;
        tempP = 1;

        float  newX = (matrix[0][0] * tempX + matrix[0][1] * tempY + matrix[0][2] * tempZ + matrix[0][3] * tempP);
        float  newY = (matrix[1][0] * tempX + matrix[1][1] * tempY + matrix[1][2] * tempZ + matrix[1][3] * tempP);
        float newZ = (matrix[2][0] * tempX + matrix[2][1] * tempY + matrix[2][2] * tempZ + matrix[2][3] * tempP);
        float  newP = (matrix[3][0] * tempX + matrix[3][1] * tempY + matrix[3][2] * tempZ + matrix[3][3] * tempP);


        Coordinate i2(newX, newY, newZ, newP);
        return i2;
    }
}

float Sphere::getRadius() const {
    return radius;
};
