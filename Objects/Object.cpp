//
// Created by muntan on 27/10/22.
//

#include "Object.h"

Object::Object(const Coordinate &center, int r, int g, int b, float rotateX, float rotateY, float rotateZ, float scaleX,
               float scaleY, float scaleZ) : center(center), r(r), g(g), b(b), rotateX(rotateX), rotateY(rotateY),
                                                                rotateZ(rotateZ), scaleX(scaleX), scaleY(scaleY), scaleZ(scaleZ) {
    float temp1Matrix[4][4]; // first index is row, second index is column
    float temp1InvMatrix[4][4];
    float temp2Matrix[4][4]; // first index is row, second index is column
    float temp2InvMatrix[4][4];
    float temp3Matrix[4][4]; // first index is row, second index is column
    float temp3InvMatrix[4][4];
    float translMatrix[4][4];
    float invTranslMatrix[4][4];
    float scaleMatrix[4][4];
    float invScaleMatrix[4][4];
    float rotateXMatrix[4][4];
    float invRotateXMatrix[4][4];
    float rotateYMatrix[4][4];
    float invRotateYMatrix[4][4];
    float rotateZMatrix[4][4];
    float invRotateZMatrix[4][4];

    for (int i=0;i<4;i++){
        for (int j=0;j<4;j++){
            temp1Matrix[i][j] = 0;
            temp1InvMatrix[i][j] = 0;
            temp2Matrix[i][j] = 0;
            temp2InvMatrix[i][j] = 0;
            temp3Matrix[i][j] = 0;
            temp3InvMatrix[i][j] = 0;
            translMatrix[i][j] = 0;
            invTranslMatrix[i][j] = 0;
            scaleMatrix[i][j] = 0;
            invScaleMatrix[i][j] = 0;
            rotateXMatrix[i][j] = 0;
            invRotateXMatrix[i][j] = 0;
            rotateYMatrix[i][j] = 0;
            invRotateYMatrix[i][j] = 0;
            rotateZMatrix[i][j] = 0;
            invRotateZMatrix[i][j] = 0;
        }
    }
    for (int i=0;i<4;i++){
        translMatrix[i][i] = 1;
        invTranslMatrix[i][i] = 1;
        rotateXMatrix[i][i] = 1;
        invRotateXMatrix[i][i] = 1;
        rotateYMatrix[i][i] = 1;
        invRotateYMatrix[i][i] = 1;
        rotateZMatrix[i][i] = 1;
        invRotateZMatrix[i][i] = 1;
    }
    translMatrix[0][3] = center.getX();
    translMatrix[1][3] = center.getY();
    translMatrix[2][3] = center.getZ();

    invTranslMatrix[0][3] = -center.getX();
    invTranslMatrix[1][3] = -center.getY();
    invTranslMatrix[2][3] = -center.getZ();

    scaleMatrix[0][0] = scaleX;
    scaleMatrix[1][1] = scaleY;
    scaleMatrix[2][2] = scaleZ;
    invScaleMatrix[0][0] = 1/float(scaleX);
    invScaleMatrix[1][1] = 1/float(scaleY);
    invScaleMatrix[2][2] = 1/float(scaleZ);
    
    scaleMatrix[3][3] = 1;
    invScaleMatrix[3][3] = 1;

    float thetaX = ((rotateX) * (M_PI / 180.0)); // turn degrees into radians
    float thetaY = ((rotateY) * (M_PI / 180.0)); // turn degrees into radians
    float thetaZ = ((rotateZ) * (M_PI / 180.0)); // turn degrees into radians

    rotateXMatrix[1][1] = cos(thetaX);
    rotateXMatrix[2][1] = sin(thetaX);
    rotateXMatrix[1][2] = -sin(thetaX);
    rotateXMatrix[2][2] = cos(thetaX);

    rotateYMatrix[0][0] = cos(thetaY);
    rotateYMatrix[2][0] = -sin(thetaY);
    rotateYMatrix[0][2] = sin(thetaY);
    rotateYMatrix[2][2] = cos(thetaY);

    rotateZMatrix[0][0] = cos(thetaZ);
    rotateZMatrix[1][0] = -sin(thetaZ);
    rotateZMatrix[0][1] = sin(thetaZ);
    rotateZMatrix[1][1] = cos(thetaZ);

    invRotateXMatrix[1][1] = cos(-thetaX);
    invRotateXMatrix[2][1] = sin(-thetaX);
    invRotateXMatrix[1][2] = -sin(-thetaX);
    invRotateXMatrix[2][2] = cos(-thetaX);

    invRotateYMatrix[0][0] = cos(-thetaY);
    invRotateYMatrix[2][0] = sin(-thetaY);
    invRotateYMatrix[0][2] = -sin(-thetaY);
    invRotateYMatrix[2][2] = cos(-thetaY);

    invRotateZMatrix[0][0] = cos(-thetaZ);
    invRotateZMatrix[1][0] = sin(-thetaZ);
    invRotateZMatrix[0][1] = -sin(-thetaZ);
    invRotateZMatrix[1][1] = cos(-thetaZ);

    for (int i=0;i<4;i++){
        for (int j=0;j<4;j++){
            for (int k=0;k<4;k++){
                temp1Matrix[i][j] += translMatrix[i][k] * scaleMatrix[k][j]; // calculate matrix with translation and scale
                temp1InvMatrix[i][j] += invScaleMatrix[i][k] * invTranslMatrix[k][j];
            }
        }
    }
    for (int i=0;i<4;i++){
        for (int j=0;j<4;j++){
            for (int k=0;k<4;k++){
                temp2Matrix[i][j] += temp1Matrix[i][k] * rotateZMatrix[k][j];
                temp2InvMatrix[i][j] += invRotateZMatrix[i][k] * temp1InvMatrix[k][j];
            }
        }
    }
    for (int i=0;i<4;i++){
        for (int j=0;j<4;j++){
            for (int k=0;k<4;k++){
                temp3Matrix[i][j] += temp2Matrix[i][k] * rotateYMatrix[k][j];
                temp3InvMatrix[i][j] += invRotateYMatrix[i][k] * temp2InvMatrix[k][j];
            }
        }
    }

    for (int i=0;i<4;i++){
        for (int j=0;j<4;j++){
            matrix[i][j] = 0;
            invMatrix[i][j] = 0;
            for (int k=0;k<4;k++){
                matrix[i][j] += temp3Matrix[i][k] * rotateXMatrix[k][j];
                invMatrix[i][j] += invRotateXMatrix[i][k] * temp3InvMatrix[k][j];
            }
        }
    }

}

int Object::getR() const {
    return r;
}

int Object::getG() const {
    return g;
}

int Object::getB() const {
    return b;
}

void Object::setRotateX(float rotateX) {
    Object::rotateX = rotateX;
}

void Object::setRotateY(float rotateY) {
    Object::rotateY = rotateY;
}

void Object::setRotateZ(float rotateZ) {
    Object::rotateZ = rotateZ;
}

const Coordinate Object::getCenter() const {
    return center;
}

Ray Object::invRay(Ray ray) {
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

    Ray newRay(tempOrig, tempDir);
    return newRay;
}

Coordinate Object::calcRealCoords(float tempX, float tempY, float tempZ, float tempP) {
    float newX = (matrix[0][0] * tempX + matrix[0][1] * tempY + matrix[0][2] * tempZ + matrix[0][3] * tempP);
    float newY = (matrix[1][0] * tempX + matrix[1][1] * tempY + matrix[1][2] * tempZ + matrix[1][3] * tempP);
    float newZ = (matrix[2][0] * tempX + matrix[2][1] * tempY + matrix[2][2] * tempZ + matrix[2][3] * tempP);
    float newP = (matrix[3][0] * tempX + matrix[3][1] * tempY + matrix[3][2] * tempZ + matrix[3][3] * tempP);

    Coordinate realCoords(newX, newY, newZ, newP);
    return realCoords;

}

