#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Coordinate {
    int x,y,z,p=1;
public:
    Coordinate(int x, int y, int z) : x(x), y(y), z(z) {}

    void setCoords(int x, int y, int z) {
        Coordinate::x = x;
        Coordinate::y = y;
        Coordinate::z = z;
    }

    int getX() const {
        return x;
    }
    int getY() const {
        return y;
    }
    int getZ() const {
        return z;
    }
    int getP() const {
        return p;
    }

};

class Vector {
    int x,y,z,p=0;
public:
    Vector(int x, int y, int z) : x(x), y(y), z(z) {}

    int getX() const {
        return x;
    }
    int getY() const {
        return y;
    }
    int getZ() const {
        return z;
    }
    int getP() const {
        return p;
    }
};

class Ray {
    Coordinate start;
    Vector vect;
public:
    Ray(const Coordinate &start, const Vector &vect) : start(start), vect(vect) {}

    const Coordinate &getStart() const {
        return start;
    }
    const Vector &getVect() const {
        return vect;
    }
};

class Object {
    Coordinate center;
    int radius;
public:
    Object(const Coordinate &center, int radius) : center(center), radius(radius) {}

    const Coordinate &getCenter() const {
        return center;
    }
    int getRadius() const {
        return radius;
    }
};

double distance(Coordinate a, Coordinate b) {
    return sqrt(pow(a.getX() - b.getX(),2) + pow(a.getY() - b.getY(),2) + pow(a.getZ() - b.getZ(),2));

}

Coordinate hit(Ray ray, Object object) {
    Coordinate temp(0,0,0);
    double dist = distance(object.getCenter(), ray.getStart());
    cout << endl << dist << endl;

    return temp;
};

int main() {

    int nRows = 10, nCols = 20;
    Coordinate eye(0,0,0);

    for(int r = 0; r < nRows; r++) {
        cout << endl;
        for (int c = 0; c < nCols; c++) {
            cout << "O";
        }
    }

    Coordinate centerSphere(3,3,3);
    Object sphere(centerSphere,1);


    Coordinate startRay(0,0,0);
    Vector vectRay(1,1,1);
    Ray firstRay(startRay,vectRay);

    hit(firstRay, sphere);


    return 0;
}
