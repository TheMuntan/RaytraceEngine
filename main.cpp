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
#include "Objects/Cylinder.h"
#include "Objects/Cone.h"
#include <iostream>

using namespace std; // std vector for dynamic vector size


int main(int argc, char *argv[]) {
    int totalObjects = 0;

//    int screenX = 1920, screenY = 1080;
    int screenX = 1280, screenY = 720;
//    int screenX = 720, screenY = 480;

    // OBJECT DECLARATION STARTS HERE.
    // COPY PASTE THE DESIRED SCENE AND REPLACE THE SECTION BELOW:
    Coordinate planeCenter1(0.0, 0.0, -6000.0, 1);
    Plane plane1(planeCenter1, 52/255.0, 204/255.0, 235/255.0, 1.0,
                 -10.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0);
    totalObjects++;

    Coordinate sharkHead(0.0,1500.0,800.0,1);
    Cone shark1(sharkHead, 36/255.0, 101/255.0, 166/255.0, 1.0,
                0,0,0,1800,2000,3000,0.0,0.0,0.0);
    totalObjects++;

    Coordinate sharkBody(0.0,-100.0,-1200.0,1);
    Cylinder shark2(sharkBody, 166/255.0, 207/255.0, 247/255.0, 1.0,
                    -30,0,0,1110,700,1100,0.0,0.0,0.0);
    totalObjects++;

    Coordinate sharkEye1(1200.0,1500.0,-1200.0,1);
    Sphere shark3(100,sharkEye1, 0/255.0, 0/255.0, 0/255.0, 1.0,
                  -15,0,0,1.0,1.0,1.0,0.0,0.0,0.0);
    totalObjects++;

    Coordinate sharkEye2(-1200.0,1500.0,-1200.0,1);
    Sphere shark4(100,sharkEye2, 0/255.0, 0/255.0, 0/255.0, 1.0,
                  -15,0,0,1.0,1.0,1.0,0.0,0.0,0.0);
    totalObjects++;

    Coordinate humanBody(0,-100,1600,1);
    Sphere human1(100,humanBody, 252/255.0, 179/255.0, 179/255.0, 1.0,
                  0,0,0,2.0,1.0,0.5,0.0,0.0,0.0);
    totalObjects++;

    Coordinate humanHead(200,-100,1650,1);
    Sphere human2(50,humanHead, 252/255.0, 179/255.0, 179/255.0, 1.0,
                  0,0,0,1.0,1.0,1.0,0.0,0.0,0.0);
    totalObjects++;

    Coordinate humanFoot1(-200,-100,1550,1);
    Cube human3(humanFoot1, 252/255.0, 179/255.0, 179/255.0, 1.0,
                  0,0,0,50.0,100.0,100.0,0.0,0.0,0.0);
    totalObjects++;


    Object *objects[totalObjects];
    objects[0] = &plane1;
    objects[1] = &shark1;
    objects[2] = &shark2;
    objects[3] = &shark3;
    objects[4] = &shark4;
    objects[5] = &human1;
    objects[6] = &human2;
    objects[7] = &human3;

    Coordinate lightPosition(0.0, -2000.0, 2000.0, 1); // point light coordinate
    // OBJECT DECLARATION ENDS HERE.



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

    int moveX = 0;
    int moveY = 0;
    int moveZ = 0;
    int lookX = 0;
    int lookY = 0;
    int lookZ = 0;

    do {
        Coordinate eye(0.0 + moveX, -2000.0 + moveY, 2000.0 + moveZ, 1);
        Coordinate lookPoint(0.0 + lookX, 200.0 + lookY, 800.0 + lookZ, 1);
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

        for (int r = 0; r < screenY * 2; r++) {
            for (int c = 0; c < screenX * 2; c++) {
                glBegin(GL_POINTS);

                Coordinate screenWorld1 = screenCenter + (u * (c / float(screenX) - 1));
                Coordinate screenWorldCoordinate = screenWorld1 + (v * (r / float(screenY) - 1));
                eye.setCoords(eye.getX(),eye.getY(),eye.getZ(),eye.isPoint());
                Coordinate worldVector = screenWorldCoordinate - eye;

                worldVector.normalise();

                Ray screenRay(eye, worldVector);

                Coordinate hits[totalObjects];

                for (int i = 0; i <
                                totalObjects; i++) { // check hits with all existing objects for a screen ray and save coordinate
                    Coordinate tempHit = objects[i]->hit(screenRay);
                    hits[i] = tempHit;
                }

                int closestIndex = -1;

                for (int i = 0; i < totalObjects; i++) { // find closest hit location
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
                shading.push_back(0 / 255.0);
                shading.push_back(0 / 255.0);
                shading.push_back(0 / 255.0);
                shading.push_back(0.0);
                vector<float> skyShading;
                skyShading.push_back(65 / 255.0);
                skyShading.push_back(127 / 255.0);
                skyShading.push_back(224 / 255.0);
                skyShading.push_back(1.0);

                if (closestIndex != -1) {

                    Coordinate lightDirection =
                            lightPosition - hits[closestIndex]; // calculate vector direction of light
                    lightDirection.normalise();
                    Ray shadowRay;

                    // Check reflection on object
                    float reflectionAmount = objects[closestIndex]->getReflection();
                    if (reflectionAmount > 0.0) {
                        Coordinate reflection = objects[closestIndex]->reflect(hits[closestIndex], worldVector);
                        Ray reflectRay(hits[closestIndex], reflection);
                        Coordinate reflectionHit[totalObjects];
                        for (int i = 0; i <
                                        totalObjects; i++) { // check hits with all existing objects for a screen ray and save coordinate
                            if (i != closestIndex) {
                                Coordinate tempHit = objects[i]->hit(reflectRay);
                                reflectionHit[i] = tempHit;
                            } else {
                                Coordinate fakeHit(0.0, 0.0, 0.0, 0);
                                reflectionHit[i] = fakeHit;
                            }
                        }
                        int reflectionIndex = -1;

                        for (int i = 0; i < totalObjects; i++) { // find closest reflection location
                            if (reflectionHit[i].isPoint()) { // check if there was a hit with this object
                                if (reflectionIndex == -1) {
                                    reflectionIndex = i;
                                } else {
                                    if (reflectionHit[i].distance(hits[closestIndex]) <
                                        reflectionHit[reflectionIndex].distance(hits[closestIndex])) {
                                        reflectionIndex = i;
                                    }
                                }
                            }
                        }
                        if (reflectionIndex != -1) { // reflection of other object
                            vector<float> reflectShading;
                            vector<float> objShading = objects[closestIndex]->getShading(hits[closestIndex],
                                                                                         lightDirection);

                            lightDirection = lightPosition -
                                             reflectionHit[reflectionIndex]; // calculate vector direction of light
                            lightDirection.normalise();

                            vector<float> tempShading = objects[reflectionIndex]->getShading(
                                    reflectionHit[reflectionIndex], lightDirection);
                            for (int i = 0; i < 4; i++) {
                                reflectShading.push_back(
                                        tempShading[i] * reflectionAmount + objShading[i] * (1.0 - reflectionAmount));
                            }
                            shading = reflectShading;

                            // check for shadow
                            Ray reflect(reflectionHit[reflectionIndex], lightDirection);
                            shadowRay = reflect;
                        } else { // reflection of sky
                            vector<float> reflectShading;
                            vector<float> objShading = objects[closestIndex]->getShading(hits[closestIndex],
                                                                                         lightDirection);

                            for (int i = 0; i < 4; i++) {
                                reflectShading.push_back(
                                        skyShading[i] * reflectionAmount + objShading[i] * (1.0 - reflectionAmount));
                            }
                            shading = reflectShading;

                            Ray reflect(hits[closestIndex], lightDirection);
                            shadowRay = reflect;

                        }
                    } else {
                        Ray noReflect(hits[closestIndex], lightDirection);
                        shadowRay = noReflect;

                        shading = objects[closestIndex]->getShading(hits[closestIndex], lightDirection);
                    }

                    //refraction and transparency
                    float transparencyAmount = objects[closestIndex]->getTransparency();
                    if (transparencyAmount > 0.0) {
                        Coordinate refraction = objects[closestIndex]->refract(hits[closestIndex], worldVector);
                        Ray refractRay(hits[closestIndex], refraction);
                        Coordinate refractionHit[totalObjects];
                        for (int i = 0; i <
                                        totalObjects; i++) { // check hits with all existing objects for a screen ray and save coordinate
                            if (i !=
                                closestIndex) {
                                Coordinate tempHit = objects[i]->hit(refractRay);
                                refractionHit[i] = tempHit;
                            } else {
                                Coordinate fakeHit(0.0, 0.0, 0.0, 0);
                                refractionHit[i] = fakeHit;
                            }
                        }
                        int refractionIndex = -1;

                        for (int i = 0; i < totalObjects; i++) { // find closest refraction location
                            if (refractionHit[i].isPoint()) { // check if there was a hit with this object
                                if (refractionIndex == -1) {
                                    refractionIndex = i;
                                } else {
                                    if (refractionHit[i].distance(hits[closestIndex]) <
                                        refractionHit[refractionIndex].distance(hits[closestIndex])) {
                                        refractionIndex = i;
                                    }
                                }
                            }
                        }
                        if (refractionIndex != -1) { // refraction hits other object
                            vector<float> refractShading;

                            lightDirection = lightPosition -
                                             refractionHit[refractionIndex]; // calculate vector direction of light
                            lightDirection.normalise();

                            vector<float> tempShading = objects[refractionIndex]->getShading(
                                    refractionHit[refractionIndex], lightDirection);
                            for (int i = 0; i < 4; i++) {
                                refractShading.push_back(
                                        tempShading[i] * transparencyAmount + shading[i] * (1.0 - transparencyAmount));
                            }
                            shading = refractShading;

                            //check for shadow in the refracted spot
                            Ray refract(hits[closestIndex], lightDirection);
                            shadowRay = refract;


                        } else { // refraction of sky
                            vector<float> refractShading;

                            for (int i = 0; i < 4; i++) {
                                refractShading.push_back(
                                        skyShading[i] * transparencyAmount + shading[i] * (1.0 - transparencyAmount));
                            }
                            shading = refractShading;

                            Ray refract(hits[closestIndex], lightDirection);
                            shadowRay = refract;

                        }
                    }

                    Coordinate shadowHit(0, 0, 0, 0);
                    int i = 0;
                    Coordinate shadowObject[totalObjects];
                    for (int i = 0; i <
                                    totalObjects; i++) { // checking for shadow (is there an object between hit coordinate and light
                        if (i != closestIndex) {
                            shadowHit = objects[i]->hit(shadowRay);
                            shadowObject[i] = shadowHit;
                        } else {
                            Coordinate failHit(0.0, 0.0, 0.0, 0);
                            shadowObject[i] = failHit;
                        }
                    }
                    int shadowIndex = -1;

                    for (int i = 0; i < totalObjects; i++) { // find closest hit location
                        if (shadowObject[i].isPoint()) { // check if there was a hit with this object
                            if (shadowIndex == -1) {
                                shadowIndex = i;
                            } else {
                                if (shadowObject[i].distance(hits[closestIndex]) <
                                    shadowObject[shadowIndex].distance(hits[closestIndex])) {
                                    shadowIndex = i;
                                }
                            }
                        }
                    }

                    if (shadowIndex != -1 and (shadowObject[shadowIndex].distance(hits[closestIndex]) <
                                               lightPosition.distance(hits[closestIndex]))) {
                        float transp = 1 - objects[shadowIndex]->getTransparency();
                        shadingFactor = 3 * transp + 1;
                    } else {
                        shadingFactor = 1;
                    }
                } else {
                    shading = skyShading;
                }

                glColor3f(shading[0] * shading[3] / shadingFactor, shading[1] * shading[3] / shadingFactor,
                          shading[2] * shading[3] / shadingFactor);
                glVertex2i(c / 2, -r / 2 + screenY);
            }
            glEnd();
            glFlush();

        }

        cout << endl << "Drawing complete!" << endl;

        glFlush();
        cout << "Move in X axis:" << endl;
        cin >> moveX;
        cout << "Move in Y axis:" << endl;
        cin >> moveY;
        cout << "Move in Z axis:" << endl;
        cin >> moveZ;
        cout << "Look in X axis:" << endl;
        cin >> lookX;
        cout << "Look in Y axis:" << endl;
        cin >> lookY;
        cout << "Look in Z axis:" << endl;
        cin >> lookZ;

    } while (moveX != 0 or moveY != 0 or moveZ != 0 or
            lookX != 0 or lookY != 0 or lookZ != 0);

    glutMainLoop();

    return 0;
}
