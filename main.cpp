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
#include <chrono>

using namespace std; // std vector for dynamic vector size


int main(int argc, char *argv[]) {
    int totalObjects = 0;

//    int screenX = 1920, screenY = 1080;
    int screenX = 1280, screenY = 720;
//    int screenX = 720, screenY = 480;

    // OBJECT DECLARATION STARTS HERE.
    // COPY PASTE THE DESIRED SCENE AND REPLACE THE SECTION BELOW UNTIL THE NEXT COMMENT:

    Coordinate planeCenter1(0.0, 0.0, 0.0, 1);
    Plane plane1(planeCenter1, 255/255.0, 255/255.0, 255/255.0, 0.1,
                 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0);
    totalObjects++;

    Coordinate carCenter1(0.0, 0.0, 0.0, 1);
    Cube cube1(carCenter1, 255/255.0, 56/255.0, 56/255.0, 1.0,
               0.0, 0.0, 0.0, 3000.0, 1000.0, 1000.0, 0.5, 0.0, 0.0, 0.005);
    totalObjects++;

    Coordinate carCenter2(0.0, 500.0, 100.0, 1);
    Sphere sphere1(100,carCenter2, 255/255.0, 56/255.0, 56/255.0, 1.0,
                   0.0, 0.0, 0.0, 16.5, 10.0, 10.0, 0.5, 0.0, 0.0, 0.05);
    totalObjects++;

    Coordinate carWheel1(1100.0, -500.0, 180.0, 1);
    Sphere wheel1(1,carWheel1, 143/255.0, 141/255.0, 141/255.0, 1.0,
                  -90.0, 0.0, 0.0, 300.0, 100.0, 300.0, 0.0, 0.0, 0.0, 0.0);
    totalObjects++;

    Coordinate carWheel2(-1100.0, -500.0, 180.0, 1);
    Sphere wheel2(1,carWheel2, 143/255.0, 141/255.0, 141/255.0, 1.0,
                  -90.0, 0.0, 0.0, 300.0, 100.0, 300.0, 0.0, 0.0, 0.0, 0.0);
    totalObjects++;

    Coordinate buildingCenter1(5000.0, 13000.0, 0.0, 1);
    Cube building1(buildingCenter1, 143/255.0, 141/255.0, 141/255.0, 1.0,
                   0.0, 0.0, 0.0, 6000.0, 12000.0, 100000.0, 0.2, 0.0, 0.0, 0.0);
    totalObjects++;

    Coordinate buildingCenter2(-5000.0, 13000.0, 0.0, 1);
    Cube building2(buildingCenter2, 143/255.0, 141/255.0, 141/255.0, 1.0,
                   0.0, 0.0, 0.0, 6000.0, 12000.0, 100000.0, 0.2, 0.0, 0.0, 0.0);
    totalObjects++;

    Coordinate buildingCenter3(5000.0, 30000.0, 0.0, 1);
    Cube building3(buildingCenter3, 143/255.0, 141/255.0, 141/255.0, 1.0,
                   0.0, 0.0, 0.0, 6000.0, 12000.0, 100000.0, 0.2, 0.0, 0.0, 0.0);
    totalObjects++;

    Coordinate buildingCenter4(-5000.0, 30000.0, 0.0, 1);
    Cube building4(buildingCenter4, 143/255.0, 141/255.0, 141/255.0, 1.0,
                   0.0, 0.0, 0.0, 6000.0, 12000.0, 100000.0, 0.2, 0.0, 0.0, 0.0);
    totalObjects++;

    Coordinate buildingCenter5(5000.0, 47000.0, 0.0, 1);
    Cube building5(buildingCenter5, 143/255.0, 141/255.0, 141/255.0, 1.0,
                   0.0, 0.0, 0.0, 6000.0, 12000.0, 100000.0, 0.2, 0.0, 0.0, 0.0);
    totalObjects++;

    Coordinate buildingCenter6(-5000.0, 47000.0, 0.0, 1);
    Cube building6(buildingCenter6, 143/255.0, 141/255.0, 141/255.0, 1.0,
                   0.0, 0.0, 0.0, 6000.0, 12000.0, 100000.0, 0.2, 0.0, 0.0, 0.0);
    totalObjects++;

    Coordinate buildingCenter7(5000.0, 64000.0, 0.0, 1);
    Cube building7(buildingCenter7, 143/255.0, 141/255.0, 141/255.0, 1.0,
                   0.0, 0.0, 0.0, 6000.0, 12000.0, 100000.0, 0.2, 0.0, 0.0, 0.0);
    totalObjects++;

    Coordinate buildingCenter8(-5000.0, 64000.0, 0.0, 1);
    Cube building8(buildingCenter8, 143/255.0, 141/255.0, 141/255.0, 1.0,
                   0.0, 0.0, 0.0, 6000.0, 12000.0, 100000.0, 0.2, 0.0, 0.0, 0.0);
    totalObjects++;

    Coordinate buildingCenter9(20000.0, 13000.0, 0.0, 1);
    Cube building9(buildingCenter9, 143/255.0, 141/255.0, 141/255.0, 1.0,
                   0.0, 0.0, 0.0, 6000.0, 12000.0, 100000.0, 0.2, 0.0, 0.0, 0.0);
    totalObjects++;

    Coordinate buildingCenter10(-20000.0, 13000.0, 0.0, 1);
    Cube building10(buildingCenter10, 143/255.0, 141/255.0, 141/255.0, 1.0,
                   0.0, 0.0, 0.0, 6000.0, 12000.0, 100000.0, 0.2, 0.0, 0.0, 0.0);
    totalObjects++;

    Coordinate buildingCenter11(5000.0, -13000.0, 0.0, 1);
    Cube building11(buildingCenter11, 143/255.0, 141/255.0, 141/255.0, 1.0,
                   0.0, 0.0, 0.0, 6000.0, 12000.0, 100000.0, 0.2, 0.0, 0.0, 0.0);
    totalObjects++;

    Coordinate buildingCenter12(-5000.0, -13000.0, 0.0, 1);
    Cube building12(buildingCenter12, 143/255.0, 141/255.0, 141/255.0, 1.0,
                   0.0, 0.0, 0.0, 6000.0, 12000.0, 100000.0, 0.2, 0.0, 0.0, 0.0);
    totalObjects++;

    Coordinate buildingCenter13(5000.0, 95000.0, 0.0, 1);
    Cube building13(buildingCenter13, 143/255.0, 141/255.0, 141/255.0, 1.0,
                   0.0, 0.0, 0.0, 6000.0, 12000.0, 100000.0, 0.2, 0.0, 0.0, 0.0);
    totalObjects++;

    Coordinate buildingCenter14(-5000.0, 95000.0, 0.0, 1);
    Cube building14(buildingCenter14, 143/255.0, 141/255.0, 141/255.0, 1.0,
                   0.0, 0.0, 0.0, 6000.0, 12000.0, 100000.0, 0.2, 0.0, 0.0, 0.0);
    totalObjects++;

    Coordinate roadCenter(0.0, 800.0, 0.0, 1);
    Cube road1(roadCenter, 0/255.0, 0/255.0, 0/255.0, 1.0,
               0.0, 0.0, 0.0, 100000.0, 3000.0, 10.0, 0.0, 0.0, 0.0, 0.0);
    totalObjects++;

    Coordinate buildingCenter15(17000.0, -13000.0, 0.0, 1);
    Cube building15(buildingCenter15, 143/255.0, 141/255.0, 141/255.0, 1.0,
                    0.0, 0.0, 0.0, 6000.0, 12000.0, 100000.0, 0.2, 0.0, 0.0, 0.0);
    totalObjects++;

    Coordinate buildingCenter16(-17000.0, -13000.0, 0.0, 1);
    Cube building16(buildingCenter16, 143/255.0, 141/255.0, 141/255.0, 1.0,
                    0.0, 0.0, 0.0, 6000.0, 12000.0, 100000.0, 0.2, 0.0, 0.0, 0.0);
    totalObjects++;


    Object *objects[totalObjects];
    objects[0] = &plane1;
    objects[1] = &cube1;
    objects[2] = &sphere1;
    objects[3] = &wheel1;
    objects[4] = &wheel2;
    objects[5] = &building1;
    objects[6] = &building2;
    objects[7] = &building3;
    objects[8] = &building4;
    objects[9] = &building5;
    objects[10] = &building6;
    objects[11] = &building7;
    objects[12] = &building8;
    objects[13] = &building9;
    objects[14] = &building10;
    objects[15] = &building11;
    objects[16] = &building12;
    objects[17] = &building13;
    objects[18] = &building14;
    objects[19] = &road1;
    objects[20] = &building15;
    objects[21] = &building16;


    Coordinate lightPosition(0.0,-1000.0,2000.0,1); // point light coordinate
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

    Coordinate eye(0.0, -2000.0, 2000.0, 1);
    Coordinate lookPoint(0.0, 200.0, 800.0, 1);

    do {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

        eye.setCoords(eye.getX() + moveX, eye.getY() + moveY, eye.getZ() + moveZ, 1);
        lookPoint.setCoords(lookPoint.getX() + lookX, lookPoint.getY() + lookY, lookPoint.getZ() + lookZ, 1);
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
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()/1000000.0 << " s" << std::endl;
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
