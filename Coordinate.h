//
// Created by muntan on 27/10/22.
//

#ifndef RAYTRACEENGINE_COORDINATE_H
#define RAYTRACEENGINE_COORDINATE_H

using namespace std;

class Coordinate {
    float x,y,z;
    int point; // 1 when point, 0 when vector
public:
    Coordinate(float x, float y, float z, int point);

    Coordinate();

    Coordinate operator - (Coordinate b);
    Coordinate operator + (Coordinate b);
    Coordinate operator * (float b);

    void normalise();

    void setCoords(float x, float y, float z, int point);

    float getX() const;
    float getY() const;
    float getZ() const;
    int isPoint() const;

    void setPoint(int point);

    void print();

    float distance(Coordinate b) const;

    float dot(Coordinate b);

    Coordinate cross(Coordinate b);

};

#endif //RAYTRACEENGINE_COORDINATE_H
