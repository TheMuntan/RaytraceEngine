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
#include "Objects/Plane.h"


using namespace std; // std vector for dynamic vector size


int main(int argc, char *argv[]) {
    int totalObjects = 2;
    Object *objects[totalObjects];

    int screenX = 1280, screenY = 720;

    Coordinate planeCenter1(0.0, 0.0, 0.0, 1);
    Plane plane1(planeCenter1, 1.0,1.0,1.0, 1.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0);
    objects[0] = &plane1;

    Coordinate centerSphere1(0.0, 150.0, 0.0, 1);
    Sphere sphere1(500.0, centerSphere1, 1.0,0.1,0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0);
    objects[1] = &sphere1;

//    Coordinate centerSphere2(-100, 1000, -100, 1);
//    Sphere sphere2(200.0, centerSphere2, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0);
//    objects[2] = &sphere2;
//
//    Coordinate centerSphere3(  500.0, 2500.0, 500.0, 1);
//    Sphere sphere3(1000.0, centerSphere3, 189/255.0, 58/255.0, 167/255.0, 1.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0);
//    objects[3] = &sphere3;
//
//    Coordinate centerCube1(  -600.0, 600.0, 200.0, 1);
//    Cube cube1(centerCube1, 1.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0, 150.0, 150.0, 150.0);
//    objects[4] = &cube1;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

    glutInitWindowPosition(80, 80);
    glutInitWindowSize(screenX, screenY);

    glutCreateWindow("Raytrace Engine");

    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluOrtho2D(0.0, screenX, screenY, 0.0);
    glClearColor(0.0,0.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);

    float camLength = 1000.0; // focal length | distance between eye and near plane

    Coordinate lightDirection(-0.0,-0.0,1.0,0); // vector of general light aka sunlight
    lightDirection.normalise();

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
            glBegin(GL_POINTS);

            Coordinate screenWorld1 = screenCenter + (u * (c/float(screenX) - 1));
            Coordinate screenWorldCoordinate = screenWorld1 + (v * (r/float(screenY) - 1));

            Ray screenRay(eye,screenWorldCoordinate);

            Coordinate hits[totalObjects];

            for (int i=0;i<totalObjects;i++) { // check hits with all existing objects for a screen ray and save coordinate
                Coordinate tempHit = objects[i]->hit(screenRay);
                hits[i] = tempHit;
            }

            Coordinate closest(INFINITY,INFINITY,INFINITY,0);
            int closestIndex = -1;

            for (int i=0;i<totalObjects;i++) { // find closest hit location
                if (hits[i].isPoint()) { // check if there was a hit with this object
                    if (closestIndex = -1)
                        closestIndex = i;
                    if (hits[i].distance(eye) < hits[closestIndex].distance(eye))
                        closestIndex = i;
                }
            }

            if (closestIndex!=-1) {
                Coordinate shadowHit(0,0,0,0);
                Ray shadowRay(hits[closestIndex], lightDirection);
                int i=0;
//                while (shadowHit.isPoint() == 0 and i < totalObjects) { // checking for shadow (is there an object between hit coordinate and light
//                    if (not i==closestIndex) {
//                        shadowHit = objects[i]->hit(shadowRay);
//                    }
//                    i++;
//                }

                vector<float> shading = objects[closestIndex]->getShading(hits[closestIndex], lightDirection);
                if (shadowHit.isPoint() == 1) {
                    glColor3f(0,0,0);
                } else {
                    glColor3f(shading[0]*shading[3], shading[1]*shading[3], shading[2]*shading[3]);
                }
            } else {
                glColor3f(0, 0.7, 1.0); // colour of the sky
            }
            glVertex2i(c / 2, -r / 2 + screenY);
        }
        glEnd();
        glFlush();

    }

    cout << endl << "Drawing complete!" << endl;

    glFlush();

    glutMainLoop();

    return 0;
}
