//
// Created by muntan on 27/10/22.
//

#include "Coordinate.h"
#include <iostream>
#include <cmath>


Coordinate::Coordinate(float x, float y, float z, int point) : x(x), y(y), z(z), point(point) {}

Coordinate Coordinate::operator - (Coordinate b) {
    Coordinate diff(x-b.getX(), y-b.getY(), z-b.getZ(), 0);
    return diff;
}

Coordinate Coordinate::operator + (Coordinate b) {
    Coordinate diff(x+b.getX(), y+b.getY(), z+b.getZ(), 0);
    if (point or b.isPoint()) {
        diff.setPoint(1);
    }
    return diff;
}

Coordinate Coordinate::operator * (float b) {
    Coordinate diff(x*b, y*b, z*b, 0);
    return diff;
}

void Coordinate::normalise() {
    float length = sqrt(pow(x,2) + pow(y,2) + pow(z,2));
    x = x/length;
    y = y/length;
    z = z/length;
}

void Coordinate::setCoords(float x, float y, float z, int point) {
    Coordinate::x = x;
    Coordinate::y = y;
    Coordinate::z = z;
    Coordinate::point = point;
}

float Coordinate::getX() const {
    return x;
}
float Coordinate::getY() const {
    return y;
}
float Coordinate::getZ() const {
    return z;
}
int Coordinate::isPoint() const {
    return point;
}

void Coordinate::setPoint(int point) {
    Coordinate::point = point;
}

void Coordinate::print() {
    cout << endl << "(" << x << "," << y << "," << z << "," << point <<  ")" << endl;
}

float Coordinate::distance(Coordinate b) const {
    float temp = sqrt(pow(x - b.getX(),2) + pow(y - b.getY(),2) + pow(z - b.getZ(),2));
    return temp;
}

float Coordinate::dot(Coordinate b) {
    float temp = x * b.getX() + y * b.getY() + z * b.getZ();
    return temp;
}
Coordinate Coordinate::cross(Coordinate b) {
    Coordinate temp(y * b.getZ() - z * b.getY(), z * b.getX() - x * b.getZ(), x * b.getY() - y * b.getX(),0);
    return temp;
}

Coordinate::Coordinate() {}
