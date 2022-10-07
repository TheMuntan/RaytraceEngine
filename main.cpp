#include <iostream>
#include <string>
using namespace std;

class Coordinate {
public:
    int x,y,z;
};

class Ray {
public:
    Coordinate start;

};

class Object {
public:
    string shape;

};

int main() {
    cout << "Hello, World!" << std::endl;

    int nRows = 10, nCols = 20;
    Coordinate eye;
    eye.x = 0;
    eye.y = 0;
    eye.z = 0;

    for(int r = 0; r < nRows; r++) {
        cout << endl;
        for (int c = 0; c < nCols; c++) {
            cout << "O";
        }
    }


    Object sphere;
    sphere.shape = "sphere";

    cout << endl << sphere.shape << endl;

    return 0;
}
