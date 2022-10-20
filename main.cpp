#include <iostream>
#include <cmath>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

using namespace std;

class Coordinate {
    float x,y,z;
    int point;//1 when point, 0 when vector
public:
    Coordinate(float x, float y, float z, int point) : x(x), y(y), z(z), point(point) {}

    Coordinate operator - (Coordinate b) {
        Coordinate diff(x-b.getX(), y-b.getY(), z-b.getZ(), 0);
        return diff;
    }

    Coordinate operator + (Coordinate b) {
        Coordinate diff(x+b.getX(), y+b.getY(), z+b.getZ(), 0);
        if (point or b.isPoint()) {
            diff.setPoint(1);
        }
        return diff;
    }

    Coordinate operator * (float b) {
        Coordinate diff(x*b, y*b, z*b, 0);
        return diff;
    }

    void normalise() {
        float length = sqrt(pow(x,2) + pow(y,2) + pow(z,2));
        x = x/length;
        y = y/length;
        z = z/length;
    }

    void setCoords(float x, float y, float z, int point) {
        x = x;
        y = y;
        z = z;
        point = point;
    }

    float getX() const {
        return x;
    }
    float getY() const {
        return y;
    }
    float getZ() const {
        return z;
    }
    int isPoint() const {
        return point;
    }

    void setPoint(int point) {
        Coordinate::point = point;
    }

    void print() {
        cout << endl << "(" << x << "," << y << "," << z << "," << point <<  ")" << endl;
    }

    float distance(Coordinate b) {
        float temp = sqrt(pow(x - b.getX(),2) + pow(y - b.getY(),2) + pow(z - b.getZ(),2));
        return temp;
    }

    float dot(Coordinate b) {
        float temp = x * b.getX() + y * b.getY() + z * b.getZ();
        return temp;
    }
    Coordinate cross(Coordinate b) {
        Coordinate temp(y * b.getZ() - z * b.getY(), z * b.getX() - x * b.getZ(), x * b.getY() - y * b.getX(),0);
        return temp;
    }

};

class Ray {
    Coordinate origin;
    Coordinate direction;
public:
    Ray(const Coordinate origin, const Coordinate direction) : origin(origin), direction(direction) {}

    const Coordinate getOrigin() const {
        return origin;
    }
    const Coordinate getDirection() const {
        return direction;
    }

    void setOrigin(Coordinate origin) {
        Ray::origin = origin;
    }

    void setDirection(Coordinate direction) {
        Ray::direction = direction;
    }
};

class Object {
    Coordinate center;
    int r,g,b;
public:
    Object(const Coordinate &center, int r, int g, int b) : center(center), r(r), g(g), b(b) {}

    int getR() const {
        return r;
    }

    int getG() const {
        return g;
    }

    int getB() const {
        return b;
    }
};

class Sphere : public Object {
    float radius;
    float matrix[4][4];
public:
    Sphere(const Coordinate &center, int r, int g, int b, float radius) : Object(center, r, g, b), radius(radius) {
        for (int i=0;i<4;i++){
            for (int j=0;j<4;j++){
                matrix[i][j] = 0;
            }
        }
        for (int i=0;i<4;i++){
            matrix[i][i] = 1;
        }
        matrix[3][0] = center.getX();
        matrix[3][1] = center.getY();
        matrix[3][2] = center.getZ();
    }


    Coordinate hit(Ray ray) {
        Coordinate tempOrig(ray.getOrigin().getX()- matrix[3][0],ray.getOrigin().getY()- matrix[3][1],ray.getOrigin().getZ()- matrix[3][2],1);
        Coordinate tempDir(ray.getDirection().getX()- matrix[3][0],ray.getDirection().getY()- matrix[3][1],ray.getDirection().getZ()- matrix[3][2],0);

        Ray genRay(tempOrig, tempDir);

        float A = pow(genRay.getDirection().getX(),2) + pow(genRay.getDirection().getY(),2) + pow(genRay.getDirection().getZ(),2);
        float B = (2*genRay.getOrigin().getX() * genRay.getDirection().getX()) + (2*genRay.getOrigin().getY()*genRay.getDirection().getY()) + (2*genRay.getOrigin().getZ() * genRay.getDirection().getZ());
        float C = pow(genRay.getOrigin().getX(),2) + pow(genRay.getOrigin().getY(),2) + pow(genRay.getOrigin().getZ(),2) - pow(radius,2);

        float discrim = B*B - 4 * A * C;

        if (discrim<0) {
            //cout << endl << "No hit." << endl;
            Coordinate temp(0,0,0,0);
            return temp; //returns a coordinate with 0 as the last value when no hit is found
        }

        float t1 = (-B + sqrt(discrim))/(2*A);
        float t2 = (-B - sqrt(discrim))/(2*A);

        Coordinate i1(genRay.getOrigin().getX() + genRay.getDirection().getX() * t1 + matrix[3][0],
                      genRay.getOrigin().getY() + genRay.getDirection().getY() * t1 + matrix[3][1],
                      genRay.getOrigin().getZ() + genRay.getDirection().getZ() * t1 + matrix[3][2],
                      1);

        Coordinate i2(genRay.getOrigin().getX() + genRay.getDirection().getX() * t2 + matrix[3][0],
                      genRay.getOrigin().getY() + genRay.getDirection().getY() * t2 + matrix[3][1],
                      genRay.getOrigin().getZ() + genRay.getDirection().getZ() * t2 + matrix[3][2],
                      1);

        cout << endl << "Hit enter:";
        i1.print();
        cout << endl << "Hit exit:";
        i2.print();

        return i1;
    };

};

//float * inverse(float in[4][4]) {
//    float * out[4][4];
//
//    return out;
//};

int main(int argc, char *argv[]) {

    int screenX = 1280, screenY = 720;

    Coordinate centerSphere(0, 0, 0, 1);
    Sphere sphere(centerSphere, 255,0,0, 1);

    Coordinate originRay(-3, 0, 0, 1);
    Coordinate directionRay(-2, 0, 0, 0);
    Ray firstRay(originRay, directionRay);

    Coordinate i1 = sphere.hit(firstRay);

    Coordinate centerSphere2(3, 3, 3, 1);
    Sphere sphere2(centerSphere2, 0, 255, 0, 1);

    Coordinate originRay2(0, 3, 3, 1);
    Coordinate directionRay2(1, 3, 3, 0);
    Ray firstRay2(originRay2, directionRay2);

    sphere2.hit(firstRay2);

    Coordinate centerSphere3(  0.0, 10.0, 0.0, 1);
    Sphere sphere3(centerSphere3, 0, 255, 0, 3.0);

    Coordinate originRay3(0, 3, 3, 1);
    Coordinate directionRay3(1, 3, 3, 0);
    Ray firstRay3(originRay3, directionRay3);

    sphere3.hit(firstRay3);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowPosition(80, 80);
    glutInitWindowSize(screenX, screenY);

    glutCreateWindow("Raytrace Engine");

    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluOrtho2D(0.0, screenX, screenY, 0.0);
    glClearColor(0.0,0.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);

    float camLength = 1.0; //
    float theta = 30; //viewing angle
    float angle = tan((theta/2.0) * (M_PI / 180.0));
    float aspect = (float(screenX)/screenY); //aspect ratio
    int N = 300; //distance between eye and screen
    float H = N * tan((theta/2.0) * (M_PI / 180.0));
    float W = H * aspect;
    float indWidth = 1/float(screenX);
    float indHeight = 1/float(screenY);



    glBegin(GL_POINTS);
        Coordinate eye(0.0, 0.0, 0.0, 1);
        Coordinate lookPoint(0.0, 2.0, 0.0, 1);
        Coordinate lookVector = lookPoint - eye;
        lookVector.normalise();
        Coordinate up(0.0, 0.0, 1.0, 0);


        Coordinate u = lookVector.cross(up);
        u.normalise();
        Coordinate v = u.cross(lookVector);
        v.normalise();
        u = u * screenX;
        v = v * screenY;

        Coordinate screenCenter = eye + (lookVector * camLength);

        for (int r = 0; r < screenY*2; r++) {
            for (int c = 0; c < screenX*2; c++) {
                Coordinate screenWorld1 = screenCenter + (u * (c/float(screenX) - 1));
                Coordinate screenWorldCoordinate = screenWorld1 + (v * (r/float(screenY) - 1));

                Ray screenRays1(eye,screenWorldCoordinate);
                if (sphere3.hit(screenRays1).isPoint()) {
                    glColor3f(sphere3.getR(), sphere3.getG(), sphere3.getB());
                glVertex2i(screenWorldCoordinate.getX(), screenWorldCoordinate.getZ());
                }

            }
        }

//        for (int r = 0; r < screenY; r++) {
//            for (int c = 0; c < screenX; c++) {
//                float xx = (2 * ((c + 0.5) * indWidth) - 1) * angle * aspect;
//                float yy = (1 - 2 * ((r + 0.5) * indHeight)) * angle;
//                Coordinate raydir(xx, yy, -1, 0);
//                //raydir.normalize();
//                Ray screenRays1(eye,raydir);
//                if (sphere3.hit(screenRays1).isPoint()) {
//                    glColor3f(sphere2.getR(), sphere2.getG(), sphere2.getB());
//                    glVertex2i(raydir.getX()+W, raydir.getY()+H);
//                }
//
//                float x=0,y=0,z=0;
//                x = eye.getX() - N;
//                y = eye.getY() + u[c];
//                z = eye.getZ() + v[r];
//                Coordinate screenVec(x,y,z,0);
//                Ray screenRays(eye,screenVec);
//                if (sphere2.hit(screenRays).isPoint()) {
//                    glColor3f(sphere2.getR(), sphere2.getG(), sphere2.getB());
//                    glVertex2i(screenVec.getX()+W, screenVec.getY()+H);
//                }
//            }
//        }

        for (int i = 0; i < 500; i++) {
            glColor3f(0, 153, 255);
            glVertex2i(i, i);
        }
    glEnd();
    glFlush();

    while (1)
        ;


    return 0;
}
