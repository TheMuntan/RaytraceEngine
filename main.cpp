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
    double x,y,z;
    int point;//1 when point, 0 when vector
public:
    Coordinate(double x, double y, double z, int point) : x(x), y(y), z(z), point(point) {}

    void setCoords(double x, double y, double z, int point) {
        x = x;
        y = y;
        z = z;
        point = point;
    }

    double getX() const {
        return x;
    }
    double getY() const {
        return y;
    }
    double getZ() const {
        return z;
    }
    int isPoint() const {
        return point;
    }

    void print() {
        cout << endl << "(" << x << "," << y << "," << z << "," << point <<  ")" << endl;
    }

    double distance(Coordinate b) {
        double temp = sqrt(pow(x - b.getX(),2) + pow(y - b.getY(),2) + pow(z - b.getZ(),2));
        return temp;
    }

    double dot(Coordinate b) {
        double temp = x * b.getX() + y * b.getY() + z * b.getZ();
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
    double radius;
    float matrix[4][4];
public:
    Sphere(const Coordinate &center, int r, int g, int b, double radius) : Object(center, r, g, b), radius(radius) {
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
        //Coordinate tempOrig(ray.getOrigin().getX()-sphere.getTranslationX(),ray.getOrigin().getY()-sphere.getTranslationY(),ray.getOrigin().getZ()-sphere.getTranslationZ(),1);
        //Coordinate tempDir(ray.getDirection().getX()-sphere.getTranslationX(),ray.getDirection().getY()-sphere.getTranslationY(),ray.getDirection().getZ()-sphere.getTranslationZ(),0);

        //Ray genRay(tempOrig, tempDir);

        double A = pow(ray.getDirection().getX(),2) + pow(ray.getDirection().getY(),2) + pow(ray.getDirection().getZ(),2);
        double B = (2*ray.getOrigin().getX() * ray.getDirection().getX()) + (2*ray.getOrigin().getY()*ray.getDirection().getY()) + (2*ray.getOrigin().getZ() * ray.getDirection().getZ());
        double C = pow(ray.getOrigin().getX(),2) + pow(ray.getOrigin().getY(),2) + pow(ray.getOrigin().getZ(),2) - pow(radius,2);

        double discrim = B*B - 4 * A * C;

        if (discrim<0) {
            //cout << endl << "No hit." << endl;
            Coordinate temp(0,0,0,0);
            return temp;
        }

        double t1 = (-B + sqrt(discrim))/(2*A);
        double t2 = (-B - sqrt(discrim))/(2*A);

        Coordinate i1(ray.getOrigin().getX() + ray.getDirection().getX() * t1,
                      ray.getOrigin().getY() + ray.getDirection().getY() * t1,
                      ray.getOrigin().getZ() + ray.getDirection().getZ() * t1,
                      1);

        Coordinate i2(ray.getOrigin().getX() + ray.getDirection().getX() * t2,
                      ray.getOrigin().getY() + ray.getDirection().getY() * t2,
                      ray.getOrigin().getZ() + ray.getDirection().getZ() * t2,
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
    int W = screenX/2, H = screenY/2; // Technically H = N*tan(theta/2) and W = H*aspect
    int N = 50; //distance between eye and screen
    int u[screenX],v[screenY];

    for (int c = 0; c < screenX; c++) {
        u[c] = (-W + (W * 2 * c) / screenX);
    }
    for (int r = 0; r < screenY; r++) {
        v[r] = (-H + (H * 2 * r) / screenY);
    }

    Coordinate centerSphere(0, 0, 0, 1);
    Sphere sphere(centerSphere, 148,0,211, 1);

    Coordinate originRay(-3, 0, 0, 1);
    Coordinate directionRay(-2, 0, 0, 0);
    Ray firstRay(originRay, directionRay);

    Coordinate i1 = sphere.hit(firstRay);

    Coordinate centerSphere2(3, 3, 3, 1);
    Sphere sphere2(centerSphere, 0, 255, 0, 1);

    Coordinate originRay2(0, 0, 0, 1);
    Coordinate directionRay2(1, 1, 1, 0);
    Ray firstRay2(originRay, directionRay);

    sphere2.hit(firstRay2);

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

    glBegin(GL_POINTS);
//        Coordinate eye(-3, -3, -3, 1);
//
//        for (int r = 0; r < screenY; r++) {
//            for (int c = 0; c < screenX; c++) {
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
//
//            }
//        }

//        for (int i = 0; i < 500; i++) {
//                glVertex2i(i, i);
//        }
    glEnd();
    glFlush();

    while (1)
        ;


    return 0;
}
