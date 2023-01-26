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
//#include <GL/freeglut.h>
//#include "Objects/freeglut_std.h"
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
    Plane plane1(planeCenter1, 88/255.0, 0/255.0, 133/255.0, 1.0,
                 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0);
    totalObjects++;

    Coordinate centerSphere1(1200.0, 500.0, 1000.0, 1);
    Sphere sphere1(600.0, centerSphere1, 1.0,0.1,0.0, 1.0,
                   0.0, 180.0, 0.0, 2.0, 1.0, 1.0, 0.6, 0.0, 0.0);
    totalObjects++;

    Coordinate centerSphere2(300, 350, 160, 1);
    Sphere sphere2(150.0, centerSphere2, 0.0, 1.0, 0.0, 1.0,
                   0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0);
    totalObjects++;

    Coordinate centerSphere3(  -1200.0, 1500.0, 1300.0, 1);
    Sphere sphere3(1000.0, centerSphere3, 189/255.0, 58/255.0, 167/255.0, 1.0,
                   0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0, 0.5, 0.0);
    totalObjects++;

    Coordinate centerCube1(  -800.0, 200.0, 600.0, 1);
    Cube cube1(centerCube1, 66/255.0, 135/255.0, 245/255.0, 1.0,
               0.0, 0.0, 0.0, 300.0, 300.0, 300.0, 0.0, 0.0, 0.0);
    totalObjects++;

    Coordinate centerCube2(  -1600.0, 0.0, 700.0, 1);
    Cube cube2(centerCube2, 235/255.0, 210/255.0, 26/255.0, 1.0,
               60.0, 0.0, 0.0, 1000.0, 1000.0, 1000.0, 0.0, 0.0, 0.0);
    totalObjects++;

    Coordinate centerCube3(  -1800.0, 3800.0, 700.0, 1);
    Cube cube3(centerCube3, 140/255.0, 32/255.0, 230/255.0, 1.0,
               0.0, 0.0, 0.0, 1000.0, 1000.0, 1000.0, 0.0, 0.0, 0.0);
    totalObjects++;

//    Coordinate planeCenter2(0.0, 0.0, 5000.0, 1);
//    Plane plane2(planeCenter2, 1.0,1.0,1.0, 1.0, 00.0, 0.0, 0.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0);
//    totalObjects++;

    Object *objects[totalObjects];
    objects[0] = &plane1;
    objects[1] = &sphere1;
    objects[2] = &sphere2;
    objects[3] = &sphere3;
    objects[4] = &cube1;
    objects[5] = &cube2;
    objects[6] = &cube3;
//    objects[7] = &plane2;

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
            Coordinate worldVector = screenWorldCoordinate - eye;

            worldVector.normalise();

            Ray screenRay(eye,worldVector);

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
            shading.push_back(0/255.0);
            shading.push_back(0/255.0);
            shading.push_back(0/255.0);
            shading.push_back(0.0);
            vector<float> skyShading;
            skyShading.push_back(65/255.0);
            skyShading.push_back(127/255.0);
            skyShading.push_back(224/255.0);
            skyShading.push_back(1.0);

            if (closestIndex != -1) {

                Coordinate lightDirection = lightPosition - hits[closestIndex]; // calculate vector direction of light
                lightDirection.normalise();
                Ray shadowRay;

                // Check reflection on object
                float reflectionAmount = objects[closestIndex]->getReflection();
                if (reflectionAmount > 0.0) {
                    Coordinate reflection = objects[closestIndex]->reflect(hits[closestIndex], worldVector);
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
                        if (reflectionHit[i].isPoint()) { // check if there was a hit with this object
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
                        vector<float> reflectShading;
                        vector<float> objShading = objects[closestIndex]->getShading(hits[closestIndex], lightDirection);

                        lightDirection = lightPosition - reflectionHit[reflectionIndex]; // calculate vector direction of light
                        lightDirection.normalise();

                        vector<float> tempShading = objects[reflectionIndex]->getShading(reflectionHit[reflectionIndex], lightDirection);
                        for (int i=0;i<4;i++) {
                            reflectShading.push_back(tempShading[i]*reflectionAmount+objShading[i]*(1.0-reflectionAmount));
                        }
                        shading = reflectShading;

                        // check for shadow
                        Ray reflect(reflectionHit[reflectionIndex], lightDirection);
                        shadowRay = reflect;
                    } else { // reflection of sky
                        vector<float> reflectShading;
                        vector<float> objShading = objects[closestIndex]->getShading(hits[closestIndex], lightDirection);

                        for (int i=0;i<4;i++) {
                            reflectShading.push_back(skyShading[i]*reflectionAmount+objShading[i]*(1.0-reflectionAmount));
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
                    for (int i=0;i<totalObjects;i++) { // check hits with all existing objects for a screen ray and save coordinate
                        if (i != closestIndex){ // TODO: later this will be removed as it can hit itself and be re-refracted
                            Coordinate tempHit = objects[i]->hit(refractRay);
                            refractionHit[i] = tempHit;
                        } else {
                            Coordinate fakeHit(0.0,0.0,0.0,0);
                            refractionHit[i] = fakeHit;
                        }
                    }
                    int refractionIndex = -1;

                    for (int i=0;i<totalObjects;i++) { // find closest refraction location
                        if (refractionHit[i].isPoint()) { // check if there was a hit with this object TODO: remove closestIndex AND make it use the refraction again
                            if (refractionIndex == -1) {
                                refractionIndex = i;
                            } else {
                                if (refractionHit[i].distance(hits[closestIndex]) < refractionHit[refractionIndex].distance(hits[closestIndex])) {
                                    refractionIndex = i;
                                }
                            }
                        }
                    }
                    if (refractionIndex != -1) { // refraction hits other object
                        vector<float> refractShading;

                        lightDirection = lightPosition - refractionHit[refractionIndex]; // calculate vector direction of light
                        lightDirection.normalise();

                        vector<float> tempShading = objects[refractionIndex]->getShading(refractionHit[refractionIndex], lightDirection);
                        for (int i=0;i<4;i++) {
                            refractShading.push_back(tempShading[i]*transparencyAmount+shading[i]*(1.0-transparencyAmount));
                        }
                        shading = refractShading;

                        //check for shadow in the refracted spot
                        Ray refract(hits[closestIndex], lightDirection);
                        shadowRay = refract;


                    } else { // refraction of sky
                        vector<float> refractShading;

                        for (int i=0;i<4;i++) {
                            refractShading.push_back(skyShading[i]*transparencyAmount+shading[i]*(1.0-transparencyAmount));
                        }
                        shading = refractShading;

                        Ray refract(hits[closestIndex], lightDirection);
                        shadowRay = refract;

                    }
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

                if (shadowIndex != -1 and (shadowObject[shadowIndex].distance(hits[closestIndex]) < lightPosition.distance(hits[closestIndex])) ) {
                    float transp = 1 - objects[shadowIndex]->getTransparency();
                    shadingFactor = 3 * transp + 1;
                } else {
                    shadingFactor = 1;
                }
            } else {
                shading = skyShading;
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
