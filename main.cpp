#include <iostream>
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

#include "Coordinate.h"
#include "Ray.h"
#include "Objects/Object.h"
#include "Objects/Sphere.h"
#include "Objects/Cube.h"


using namespace std; // std vector for dynamic vector size


int main(int argc, char *argv[]) {
    Sphere *spheres[3];

    int screenX = 1280, screenY = 720;

    Coordinate centerSphere(500.0, 1500.0, 0.0, 1);
    Sphere sphere(500.0, centerSphere, 1.0,0.1,0.0, 0.0, 0.0, 0.0, 2, 1.0, 1.0);
    spheres[0] = &sphere;

//    Coordinate originRay(-3, 0, 0, 1);
//    Coordinate directionRay(-2, 0, 0, 1);
//    Ray ray1(originRay, directionRay);
//
//    Coordinate i1 = sphere.hit(ray1);

    Coordinate centerSphere2(-100, 1000, -100, 1);
    Sphere sphere2(200.0, centerSphere2, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0);
    spheres[1] = &sphere2;

//    Coordinate originRay2(0, 3, 3, 1);
//    Coordinate directionRay2(1, 3, 3, 1);
//    Ray ray2(originRay2, directionRay2);
//
//    sphere2.hit(ray2);

    Coordinate centerSphere3(  500.0, 2000.0, 500.0, 1);
    Sphere sphere3(1000.0, centerSphere3, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0);
    spheres[2] = &sphere3;

//    Coordinate originRay3(0, 3, 3, 1);
//    Coordinate directionRay3(3, 4, 3, 1);
//    Ray ray3(originRay3, directionRay3);
//
//    sphere3.hit(ray3);

    Coordinate centerCube1(  0.0, 600.0, 100.0, 1);
    Cube cube1(centerCube1, 1, 0.0, 1, 0.0, 0.0, 0.0, 100.0, 100.0, 100.0);


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

    float camLength = 1000.0; // focal length | distance between eye and near plane

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

            Ray screenRay(eye,screenWorldCoordinate);

            Coordinate hits[3];

            for (int i=0;i<3;i++) { // check hits with all existing objects for a screen ray and save coordinate
            Coordinate tempHit = spheres[i]->hit(screenRay);
            hits[i] = tempHit;
            }

            Coordinate closest(INFINITY,INFINITY,INFINITY,0);
            int closestIndex = -1;

            for (int i=0;i<3;i++) { // find closest hit location
                if (hits[i].isPoint()) { // check if there was a hit with this object
                    if (hits[i].distance(eye) < hits[closestIndex].distance(eye))
                        closestIndex = i;
                }
            }

            if (closestIndex!=-1) {
                glBegin(GL_POINTS);
                glColor3f(spheres[closestIndex]->getR(), spheres[closestIndex]->getG(), spheres[closestIndex]->getB());

                if ((spheres[closestIndex]->getCenter().distance(eye)-hits[closestIndex].distance(eye))<spheres[closestIndex]->getRadius()/2.0) {
                    glColor3f(spheres[closestIndex]->getR()/5.0, spheres[closestIndex]->getG()/5.0, spheres[closestIndex]->getB()/5.0);
//                    glColor4f(spheres[closestIndex]->getR(), spheres[closestIndex]->getG(), spheres[closestIndex]->getB(), 0.1);
                }

                glVertex2i(c / 2, -r / 2 + screenY);
            }
            if (cube1.hit(screenRay).isPoint()) {
                glColor3f(cube1.getR(), cube1.getG(), cube1.getB());
                glVertex2i(c / 2, -r / 2 + screenY);

            }

        }
        glEnd();
        glFlush();

    }

    cout << endl << "Done scanning!";

    glEnd();
    glFlush();

    while (1)
        ;


    return 0;
}
