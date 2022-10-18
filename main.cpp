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
        Coordinate::x = x;
        Coordinate::y = y;
        Coordinate::z = z;
        Coordinate::point = point;
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

};

class Sphere : private Object {
    double radius;
public:
    Sphere(const Coordinate &center, int r, int g, int b, double radius) : Object(center, r, g, b), radius(radius) {}

    Coordinate hit(Ray ray) { //zet de hit functie binnen de object class, dan kan je gewoon object.hit(ray)
        Coordinate temp(-1,-1,-1,1);
        //Coordinate tempOrig(ray.getOrigin().getX()-sphere.getTranslationX(),ray.getOrigin().getY()-sphere.getTranslationY(),ray.getOrigin().getZ()-sphere.getTranslationZ(),1);
        //Coordinate tempDir(ray.getDirection().getX()-sphere.getTranslationX(),ray.getDirection().getY()-sphere.getTranslationY(),ray.getDirection().getZ()-sphere.getTranslationZ(),0);

        //Ray genRay(tempOrig, tempDir);

        double A = pow(ray.getDirection().getX(),2) + pow(ray.getDirection().getY(),2) + pow(ray.getDirection().getZ(),2);
        double B = (2*ray.getOrigin().getX() * ray.getDirection().getX()) + (2*ray.getOrigin().getY()*ray.getDirection().getY()) + (2*ray.getOrigin().getZ() * ray.getDirection().getZ());
        double C = pow(ray.getOrigin().getX(),2) + pow(ray.getOrigin().getY(),2) + pow(ray.getOrigin().getZ(),2) - pow(radius,2);

        double discrim = B*B - 4 * A * C;

        if (discrim<0) {
            cout << endl << "No hit." << endl;
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

int main(int argc, char *argv[]) {

    int screenX = 1280, screenY = 720;



    int nRows = 10, nCols = 20;
    Coordinate eye(0,0,0, 1);

    for(int r = 0; r < nRows; r++) {
        cout << endl;
        for (int c = 0; c < nCols; c++) {
            cout << "O";
        }
    }

    Coordinate centerSphere(0,0,0,1);
    Sphere sphere(centerSphere,255,255,255,1);

    Coordinate originRay(-3,0,0,1);
    Coordinate directionRay(-2,0,0,0);
    Ray firstRay(originRay,directionRay);

    Coordinate i1 = sphere.hit(firstRay);


    Coordinate centerSphere2(3,3,3,1);
    Sphere sphere2(centerSphere,255,255,255,1);

    Coordinate originRay2(0,0,0,1);
    Coordinate directionRay2(1,1,1,0);
    Ray firstRay2(originRay,directionRay);

    sphere2.hit(firstRay2);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowPosition(80, 80);
    glutInitWindowSize(screenX,screenY);

    glutCreateWindow("Raytrace Engine");

    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluOrtho2D( 0.0, screenX, screenY,0.0 );

    glBegin(GL_POINTS);
        glColor3f(255,255,255);
        glVertex2i(100,100);
    glEnd();

    glEnable(GL_SCISSOR_TEST);
    glScissor(100, 200, 1, 1);
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
// Remember to disable scissor test, or, perhaps reset the scissor rectangle:
    glDisable(GL_SCISSOR_TEST);



    while (1)
        ;


    return 0;
}
