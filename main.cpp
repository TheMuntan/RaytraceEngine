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
    int totalObjects = 0;

//    int screenX = 1920, screenY = 1080;
    int screenX = 1280, screenY = 720;
//    int screenX = 720, screenY = 480;

    Coordinate planeCenter1(0.0, 0.0, 0.0, 1);
    Plane plane1(planeCenter1, 88/255.0, 0/255.0, 133/255.0, 1.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0);
    totalObjects++;

    Coordinate centerSphere1(200.0, 500.0, 1000.0, 1);
    Sphere sphere1(600.0, centerSphere1, 1.0,0.1,0.0, 1.0, 0.0, 180.0, 0.0, 1.0, 1.0, 1.0, 0.5);
    totalObjects++;

    Coordinate centerSphere2(300, 350, 160, 1);
    Sphere sphere2(150.0, centerSphere2, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0);
    totalObjects++;

    Coordinate centerSphere3(  2200.0, 1500.0, 1300.0, 1);
    Sphere sphere3(1000.0, centerSphere3, 189/255.0, 58/255.0, 167/255.0, 1.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0);
    totalObjects++;

    Coordinate centerCube1(  -800.0, 200.0, 600.0, 1);
    Cube cube1(centerCube1, 66/255.0, 135/255.0, 245/255.0, 1.0, 0.0, 0.0, 0.0, 300.0, 300.0, 300.0, 0.0);
    totalObjects++;

    Coordinate centerCube2(  -1600.0, 0.0, 700.0, 1);
    Cube cube2(centerCube2, 235/255.0, 210/255.0, 26/255.0, 1.0, 20.0, 0.0, 0.0, 1000.0, 1000.0, 1000.0, 0.0);
    totalObjects++;

//    Coordinate planeCenter2(0.0, 0.0, 5000.0, 1);
//    Plane plane2(planeCenter2, 1.0,1.0,1.0, 1.0, 00.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0);
//    totalObjects++;

    Object *objects[totalObjects];
    objects[0] = &plane1;
    objects[1] = &sphere1;
    objects[2] = &sphere2;
    objects[3] = &sphere3;
    objects[4] = &cube1;
    objects[5] = &cube2;
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

    int shadingFactor = 1;
    Coordinate lightPosition(0.0,300.0,3000.0,1); // point light coordinate
//    Coordinate lightPosition(0.0,0.0,1200.0,1); // point light coordinate

    Coordinate eye(0.0, -2000.0, 2000.0, 1);
    Coordinate lookPoint(0.0, 200.0, 800.0, 1);
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

            vector<float> shading;
            shading.push_back(65/255.0);
            shading.push_back(127/255.0);
            shading.push_back(224/255.0);
            shading.push_back(1.0);

            if (closestIndex != -1) {

                Coordinate lightDirection = lightPosition - hits[closestIndex]; // calculate vector direction of light
                lightDirection.normalise();
                Ray shadowRay;

                // Check reflection on object
                float reflectionAmount = objects[closestIndex]->getReflection();
                if (reflectionAmount > 0.0) {
                    Coordinate reflection = objects[closestIndex]->reflect(hits[closestIndex], lookVector);
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
                    if (reflectionIndex != -1) { // reflection of other object
//                        vector<float> reflectShading;
//                        vector<float> tempShading;
//                        vector<float> objShading = objects[closestIndex]->getShading(reflectionHit[closestIndex], lightDirection);

                        lightDirection = lightPosition - reflectionHit[reflectionIndex]; // calculate vector direction of light
                        lightDirection.normalise();

                        shading = objects[reflectionIndex]->getShading(reflectionHit[reflectionIndex], lightDirection);
//                        for (int i;i<4;i++) {
//                            tempShading.push_back(reflectShading[i]*reflectionAmount+objShading[i]*(1.0-reflectionAmount));
//                        }
//
//                        shading = tempShading;


                        // check for shadow
                        Ray reflect(reflectionHit[reflectionIndex], lightDirection);
                        shadowRay = reflect;
                    } else { // reflection of sky
                        Ray reflect(hits[closestIndex], lightDirection);
                        shadowRay = reflect;

                    }
                } else {
                    Ray noReflect(hits[closestIndex], lightDirection);
                    shadowRay = noReflect;

                    shading = objects[closestIndex]->getShading(hits[closestIndex], lightDirection);
                }

                Coordinate shadowHit(0,0,0,0);
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

                if (shadowIndex != -1 and (shadowObject[i].distance(hits[closestIndex]) < lightPosition.distance(hits[closestIndex])) ) {
                    shadingFactor = 4;
                } else {
                    shadingFactor = 1;
                }
            }

            glColor3f(shading[0]*shading[3]/shadingFactor, shading[1]*shading[3]/shadingFactor, shading[2]*shading[3]/shadingFactor);
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
