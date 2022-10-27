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
        Coordinate::x = x;
        Coordinate::y = y;
        Coordinate::z = z;
        Coordinate::point = point;
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
    Ray(const Coordinate origin, const Coordinate direction) : origin(origin), direction(direction) {
        if (direction.isPoint())
            Ray::direction.setCoords(direction.getX()-origin.getX(), direction.getY()-origin.getY(), direction.getZ()-origin.getZ(), direction.isPoint()-origin.isPoint());
    }

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
    float rotateX, rotateY, rotateZ;
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
    float invMatrix[4][4];
public:
    Sphere(const Coordinate &center, int r, int g, int b, float radius) : Object(center, r, g, b), radius(radius) {
        float tempMatrix[4][4];
        float tempInvMatrix[4][4];
        float scaleMatrix[4][4];
        float invScaleMatrix[4][4];
        for (int i=0;i<4;i++){
            for (int j=0;j<4;j++){
                tempMatrix[i][j] = 0;
                tempInvMatrix[i][j] = 0;
                scaleMatrix[i][j] = 0;
                invScaleMatrix[i][j] = 0;

            }
        }
        for (int i=0;i<4;i++){
            tempMatrix[i][i] = 1;
            tempInvMatrix[i][i] = 1;
        }
        tempMatrix[3][0] = center.getX();
        tempMatrix[3][1] = center.getY();
        tempMatrix[3][2] = center.getZ();

        tempInvMatrix[3][0] = -center.getX();
        tempInvMatrix[3][1] = -center.getY();
        tempInvMatrix[3][2] = -center.getZ();

        for (int i=0;i<3;i++){
            scaleMatrix[i][i] = radius;
            invScaleMatrix[i][i] = 1/float(radius);
        }
        scaleMatrix[3][3] = 1;
        invScaleMatrix[3][3] = 1;

        for (int i=0;i<4;i++){
            for (int j=0;j<4;j++){
                matrix[i][j] = 0;
                invMatrix[i][j] = 0;
                for (int k=0;k<4;k++){
                    matrix[i][j] += tempMatrix[k][i] * scaleMatrix[j][k];
                    invMatrix[i][j] += invScaleMatrix[k][i] * tempInvMatrix[j][k];
                }
            }
        }

    }

    Coordinate hit(Ray ray) {
        float tempX = (invMatrix[0][0] * ray.getOrigin().getX() + invMatrix[0][1] * ray.getOrigin().getY() + invMatrix[0][2] * ray.getOrigin().getZ() + invMatrix[0][3] * ray.getOrigin().isPoint());
        float tempY = (invMatrix[1][0] * ray.getOrigin().getX() + invMatrix[1][1] * ray.getOrigin().getY() + invMatrix[1][2] * ray.getOrigin().getZ() + invMatrix[1][3] * ray.getOrigin().isPoint());
        float tempZ = (invMatrix[2][0] * ray.getOrigin().getX() + invMatrix[2][1] * ray.getOrigin().getY() + invMatrix[2][2] * ray.getOrigin().getZ() + invMatrix[2][3] * ray.getOrigin().isPoint());
        float tempP = (invMatrix[3][0] * ray.getOrigin().getX() + invMatrix[3][1] * ray.getOrigin().getY() + invMatrix[3][2] * ray.getOrigin().getZ() + invMatrix[3][3] * ray.getOrigin().isPoint());
        Coordinate tempOrig(tempX,tempY,tempZ,tempP);
        tempX = (invMatrix[0][0] * ray.getDirection().getX() + invMatrix[0][1] * ray.getDirection().getY() + invMatrix[0][2] * ray.getDirection().getZ() + invMatrix[0][3] * ray.getDirection().isPoint());
        tempY = (invMatrix[1][0] * ray.getDirection().getX() + invMatrix[1][1] * ray.getDirection().getY() + invMatrix[1][2] * ray.getDirection().getZ() + invMatrix[1][3] * ray.getDirection().isPoint());
        tempZ = (invMatrix[2][0] * ray.getDirection().getX() + invMatrix[2][1] * ray.getDirection().getY() + invMatrix[2][2] * ray.getDirection().getZ() + invMatrix[2][3] * ray.getDirection().isPoint());
        tempP = (invMatrix[3][0] * ray.getDirection().getX() + invMatrix[3][1] * ray.getDirection().getY() + invMatrix[3][2] * ray.getDirection().getZ() + invMatrix[3][3] * ray.getDirection().isPoint());
        Coordinate tempDir(tempX,tempY,tempZ,tempP);

        Ray genRay(tempOrig, tempDir);

        float A = pow(genRay.getDirection().getX(),2) + pow(genRay.getDirection().getY(),2) + pow(genRay.getDirection().getZ(),2);
        float B = (2*genRay.getOrigin().getX() * genRay.getDirection().getX()) + (2*genRay.getOrigin().getY()*genRay.getDirection().getY()) + (2*genRay.getOrigin().getZ() * genRay.getDirection().getZ());
        float C = pow(genRay.getOrigin().getX(),2) + pow(genRay.getOrigin().getY(),2) + pow(genRay.getOrigin().getZ(),2) - 1; //pow(radius,2)

        float discrim = B*B - 4 * A * C;

        if (discrim<0) {
            //cout << endl << "No hit." << endl;
            Coordinate temp(0,0,0,0);
            return temp; //returns a coordinate with 0 as the last value when no hit is found
        }

        float t1 = (-B - sqrt(discrim))/(2*A);
        float t2 = (-B + sqrt(discrim))/(2*A);

        tempX = genRay.getOrigin().getX() + genRay.getDirection().getX() * t1;
        tempY = genRay.getOrigin().getY() + genRay.getDirection().getY() * t1;
        tempZ = genRay.getOrigin().getZ() + genRay.getDirection().getZ() * t1;
        tempP = 1;

        float newX = (matrix[0][0] * tempX + matrix[0][1] * tempY + matrix[0][2] * tempZ + matrix[0][3] * tempP);
        float newY = (matrix[1][0] * tempX + matrix[1][1] * tempY + matrix[1][2] * tempZ + matrix[1][3] * tempP);
        float newZ = (matrix[2][0] * tempX + matrix[2][1] * tempY + matrix[2][2] * tempZ + matrix[2][3] * tempP);
        float newP = (matrix[3][0] * tempX + matrix[3][1] * tempY + matrix[3][2] * tempZ + matrix[3][3] * tempP);

        Coordinate i1(newX,newY,newZ,newP);

//        tempX = genRay.getOrigin().getX() + genRay.getDirection().getX() * t2;
//        tempY = genRay.getOrigin().getY() + genRay.getDirection().getY() * t2;
//        tempZ = genRay.getOrigin().getZ() + genRay.getDirection().getZ() * t2;
//        tempP = 1;
//
//        newX = (matrix[0][0] * tempX + matrix[0][1] * tempY + matrix[0][2] * tempZ + matrix[0][3] * tempP);
//        newY = (matrix[1][0] * tempX + matrix[1][1] * tempY + matrix[1][2] * tempZ + matrix[1][3] * tempP);
//        newZ = (matrix[2][0] * tempX + matrix[2][1] * tempY + matrix[2][2] * tempZ + matrix[2][3] * tempP);
//        newP = (matrix[3][0] * tempX + matrix[3][1] * tempY + matrix[3][2] * tempZ + matrix[3][3] * tempP);
//
//
//        Coordinate i2(newX,newY,newZ,newP);
//
//        cout << endl << "Hit enter:";
//        i1.print();
//        cout << endl << "Hit exit:";
//        i2.print();

        return i1;
    };

};

int main(int argc, char *argv[]) {

    Sphere *spheres[2];


    int screenX = 1280, screenY = 720;
    Coordinate centerSphere3(  500.0, 2000.0, 500.0, 1);
    Sphere sphere3(centerSphere3, 50, 0, 255, 1000.0);
    spheres[0] = &sphere3;

    Coordinate centerSphere(500.0, 1500.0, 0.0, 1);
    Sphere sphere(centerSphere, 255,0,0, 500.0);
    spheres[1] = &sphere;

    Coordinate originRay(-3, 0, 0, 1);
    Coordinate directionRay(-2, 0, 0, 1);
    Ray ray1(originRay, directionRay);

    Coordinate i1 = sphere.hit(ray1);

    Coordinate centerSphere2(3, 3, 3, 1);
    Sphere sphere2(centerSphere2, 0, 255, 0, 2);

    Coordinate originRay2(0, 3, 3, 1);
    Coordinate directionRay2(1, 3, 3, 1);
    Ray ray2(originRay2, directionRay2);

    sphere2.hit(ray2);


    Coordinate originRay3(0, 3, 3, 1);
    Coordinate directionRay3(3, 4, 3, 1);
    Ray ray3(originRay3, directionRay3);

    sphere3.hit(ray3);

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

//    float theta = 30; //viewing angle
//    float angle = tan((theta/2.0) * (M_PI / 180.0));
//    float aspect = (float(screenX)/screenY); //aspect ratio
//    float indWidth = 1/float(screenX);
//    float indHeight = 1/float(screenY);

    float camLength = 1000.0; // focal length | distance between

    glBegin(GL_POINTS);
        Coordinate eye(0.0, -1000.0, 200.0, 1);
        Coordinate lookPoint(0.0, 1.0, 200.0, 1);
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
                for (int i=0;i<2;i++) {
                    if (spheres[i]->hit(screenRays1).isPoint()) {
                        glBegin(GL_POINTS);
                        glColor3f(spheres[i]->getR(), spheres[i]->getG(), spheres[i]->getB());
                        glVertex2i(c/2, -r/2+screenY);
                        glEnd();
                        glFlush();
                    }
                }

            }
        }

//        for (int i = 0; i < 500; i++) {
//            glColor3f(0, 153, 255);
//            glVertex2i(i, i);
//        }
    glEnd();
    glFlush();

    while (1)
        ;


    return 0;
}
