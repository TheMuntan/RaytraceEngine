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
    int totalObjects = 6;
    Object *objects[totalObjects];

    int screenX = 1280, screenY = 720;
//    int screenX = 720, screenY = 480;

    Coordinate planeCenter1(0.0, 0.0, 0.0, 1);
    Plane plane1(planeCenter1, 1.0,1.0,1.0, 1.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0);
    objects[0] = &plane1;

    Coordinate centerSphere1(200.0, 300.0, 1200.0, 1);
    Sphere sphere1(300.0, centerSphere1, 1.0,0.1,0.0, 1.0, 0.0, 180.0, 0.0, 1.0, 1.0, 1.0, 0.0);
    objects[1] = &sphere1;

    Coordinate centerSphere2(300, 350, 160, 1);
    Sphere sphere2(150.0, centerSphere2, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0);
    objects[2] = &sphere2;

    Coordinate centerSphere3(  1500.0, 2500.0, 1300.0, 1);
    Sphere sphere3(1000.0, centerSphere3, 189/255.0, 58/255.0, 167/255.0, 1.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0);
    objects[3] = &sphere3;

    Coordinate centerCube1(  -600.0, 600.0, 300.0, 1);
    Cube cube1(centerCube1, 66/255.0, 135/255.0, 245/255.0, 1.0, 0.0, 0.0, 0.0, 150.0, 150.0, 150.0, 0.0);
    objects[4] = &cube1;

    Coordinate centerCube2(  -1600.0, 400.0, 700.0, 1);
    Cube cube2(centerCube2, 235/255.0, 210/255.0, 26/255.0, 1.0, 20.0, 0.0, 0.0, 500.0, 500.0, 500.0, 0.0);
    objects[5] = &cube2;

//    Coordinate planeCenter2(0.0, 2000.0, 0.0, 1);
//    Plane plane2(planeCenter2, 1.0,1.0,1.0, 1.0, 70.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0);
//    objects[6] = &plane2;

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

    int shadingFactor = 4;
//    Coordinate lightPosition(0.0,300.0,3000.0,1); // point light coordinate
    Coordinate lightPosition(0.0,0.0,1200.0,1); // point light coordinate

    Coordinate eye(0.0, -2000.0, 2000.0, 1);
    Coordinate lookPoint(0.0, 200.0, 200.0, 1);
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

            int closestIndex = -1;

            for (int i=0;i<totalObjects;i++) { // find closest hit location
                if (hits[i].isPoint()) { // check if there was a hit with this object
                    if (closestIndex == -1) {
                        closestIndex = i;
                    } else {
                        if (hits[i].distance(eye) < hits[closestIndex].distance(eye)) {
                            closestIndex = i;
                        }
                    }
                }
            }


            if (closestIndex != -1) {
                vector<float> shading;
                Coordinate lightDirection = lightPosition - hits[closestIndex]; // calculate vector direction of light
                lightDirection.normalise();

                // Check reflection on object
                Coordinate reflection = objects[closestIndex]->reflect(hits[closestIndex], lookVector);
                if (! reflection.isPoint()) {
                    Ray reflectRay(hits[closestIndex], reflection);
                    Coordinate reflectionHit[totalObjects];
                    for (int i=0;i<totalObjects;i++) { // check hits with all existing objects for a screen ray and save coordinate
                        if (i != closestIndex){
                            Coordinate tempHit = objects[i]->hit(reflectRay);
                            reflectionHit[i] = tempHit;
                        } else {
                            Coordinate fakeHit(0.0,0.0,0.0,0);
                            reflectionHit[i] = fakeHit;
                        }
                    }
                    int reflectionIndex = -1;

                    for (int i=0;i<totalObjects;i++) { // find closest reflection location
                        if (reflectionHit[i].isPoint() and i != closestIndex) { // check if there was a hit with this object
                            if (reflectionIndex == -1) {
                                reflectionIndex = i;
                            } else {
                                if (reflectionHit[i].distance(hits[closestIndex]) < reflectionHit[reflectionIndex].distance(hits[closestIndex])) {
                                    reflectionIndex = i;
                                }
                            }
                        }
                    }
                    if (reflectionIndex != -1) {
                        lightDirection = lightPosition - reflectionHit[reflectionIndex]; // calculate vector direction of light
                        lightDirection.normalise();

                        shading = objects[reflectionIndex]->getShading(reflectionHit[reflectionIndex], lightDirection, reflection);
                    } else {
                        glColor3f(0, 0.7, 1.0); // colour of the sky
                    }
                } else {
                    shading = objects[closestIndex]->getShading(hits[closestIndex], lightDirection, lookVector);
                }

                Coordinate shadowHit(0,0,0,0);
                Ray shadowRay(hits[closestIndex], lightDirection);
                int i=0;
                Coordinate shadowObject[totalObjects];
                for (int i=0;i<totalObjects;i++) { // checking for shadow (is there an object between hit coordinate and light
                    if (i != closestIndex) {
                        shadowHit = objects[i]->hit(shadowRay);
                        shadowObject[i] = shadowHit;
                    } else {
                        Coordinate failHit(0.0,0.0,0.0,0);
                        shadowObject[i] = failHit;
                    }
                }
                int shadowIndex = -1;

                for (int i=0;i<totalObjects;i++) { // find closest hit location
                    if (shadowObject[i].isPoint()) { // check if there was a hit with this object
                        if (shadowIndex == -1) {
                            shadowIndex = i;
                        } else {
                            if (shadowObject[i].distance(hits[closestIndex]) < shadowObject[shadowIndex].distance(hits[closestIndex])) {
                                shadowIndex = i;
                            }
                        }
                    }
                }

                if (shadowIndex != -1 and (abs(shadowObject[i].distance(hits[closestIndex])) < abs(lightPosition.distance(hits[closestIndex]))) ) {
                    glColor3f(shading[0]*shading[3]/shadingFactor, shading[1]*shading[3]/shadingFactor, shading[2]*shading[3]/shadingFactor);
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
