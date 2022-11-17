//
// Created by muntan on 28/10/22.
//

#include "Plane.h"

Plane::Plane(const Coordinate &center, float r, float g, float b, float a, float rotateX, float rotateY, float rotateZ,
             float scaleX, float scaleY, float scaleZ, float reflection)
        : Object(center, r, g, b, a, rotateX, rotateY, rotateZ, scaleX, scaleY, scaleZ, reflection) {}

Coordinate Plane::hit(Ray ray) {
    Coordinate failedHit(0, 0, 0, 0);
    Ray genRay(invCoordinate(ray.getOrigin()), invCoordinate(ray.getDirection()));

    float t = -genRay.getOrigin().getZ() / genRay.getDirection().getZ();

    if (t > 0.0) {
        float tempX = genRay.getOrigin().getX() + genRay.getDirection().getX() * t;
        float tempY = genRay.getOrigin().getY() + genRay.getDirection().getY() * t;
        float tempZ = genRay.getOrigin().getZ() + genRay.getDirection().getZ() * t;

        Coordinate tempI1(tempX, tempY, tempZ ,1);
        Coordinate i1 = transformCoordinate(tempI1);
        return i1;
    }

    return failedHit;
}

Coordinate Plane::getNorm(Coordinate hitLocation) {
    Coordinate invNorm(0.0,0.0,1.0,0);
    invNorm.normalise();
    Coordinate norm = transformCoordinate(invNorm);
    norm.normalise();
    return norm;
}

vector<float> Plane::getShading(Coordinate hitLocation, Coordinate lightDirection) {
    vector<float> shading = getRgba();

    float tempX = (invMatrix[0][0] * hitLocation.getX() + invMatrix[0][1] * hitLocation.getY() +
                   invMatrix[0][2] * hitLocation.getZ() + invMatrix[0][3] * hitLocation.isPoint());
    float tempY = (invMatrix[1][0] * hitLocation.getX() + invMatrix[1][1] * hitLocation.getY() +
                   invMatrix[1][2] * hitLocation.getZ() + invMatrix[1][3] * hitLocation.isPoint());

    int squareSize = 32;
    if (sin(tempX/squareSize) > 0.0 and sin(tempY/squareSize) > 0.0 or (sin(tempX/squareSize) < 0.0 and sin(tempY/squareSize) < 0.0)) {
        shading = {1.0, 1.0, 1.0, 1.0};

    } else if (sin(tempX/squareSize) > 0.0 and sin(tempY/squareSize) < 0.0 or (sin(tempX/squareSize) < 0.0 and sin(tempY/squareSize) > 0.0)) {
        shading = {189/255.0, 58/255.0, 167/255.0, 1.0};
    }

    Coordinate norm(0.0, 0.0, 1.0, 0);
    tempX = (matrix[0][0] * norm.getX() + matrix[0][1] * norm.getY() +
             matrix[0][2] * norm.getZ() + matrix[0][3] * norm.isPoint());
    tempY = (matrix[1][0] * norm.getX() + matrix[1][1] * norm.getY() +
             matrix[1][2] * norm.getZ() + matrix[1][3] * norm.isPoint());
    float tempZ = (matrix[2][0] * norm.getX() + matrix[2][1] * norm.getY() +
             matrix[2][2] * norm.getZ() + matrix[2][3] * norm.isPoint());
    Coordinate normDirection(tempX, tempY, tempZ, 0);

    float angleLight = acos(normDirection.dot(lightDirection));

    if (angleLight > 2) { // angle too big default=1.5708
        shading[3] = 0.001;
    } else {
        shading[3] = 1.0 - (angleLight/2);
    }


    return shading;
}
