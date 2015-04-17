#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <GL/glut.h>

#include "Window.h"
#include "Keyboard.h"
#include "Matrix4.h"
#include "main.h"
#include "Utility.h"

using namespace std;

namespace Globals
{
    Cube cube;
    Ball ball;
    House house;
    Bunny bunny;
    Dragon dragon;
    TestObject testObject;
    Object* curr_obj = &bunny;
    World world;
    Matrix4 m_trans_origin;
    Camera camera;
    GLuint texture[128];
};

int main(int argc, char *argv[])
{
    float specular[] = { 1.0, 1.0, 1.0, 1.0 };
    float shininess[] = { 100.0 };
    float position[] = { 0.0, 10.0, 1.0, 0.0 };	// light source position

    glutInit(&argc, argv);      	      	      // initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   // open an OpenGL context with double buffering, RGB colors, and depth buffering
    glutInitWindowSize(Window::width, Window::height);      // set initial window size
    glutCreateWindow("OpenGL Cube");    	      // open window and set window title

    glEnable(GL_DEPTH_TEST);            	      // enable depth buffering
    glClear(GL_DEPTH_BUFFER_BIT);       	      // clear depth buffer
    glClearColor(0.0, 0.0, 0.0, 0.0);   	      // set clear color to black
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // set polygon drawing mode to fill front and back of each polygon
    glDisable(GL_CULL_FACE);     // disable back face culling to render both sides of polygons
    glShadeModel(GL_SMOOTH);             	      // set shading to smooth
    glMatrixMode(GL_PROJECTION);

    // Generate material properties:
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    // Generate light source:
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Install callback functions:
    glutDisplayFunc(Window::displayCallback);
    glutReshapeFunc(Window::reshapeCallback);
    glutIdleFunc(Window::idleCallback);
    glutKeyboardFunc(Keyboard::keyPressCb);
    glutSpecialFunc(Keyboard::specialFuncCb);

    // Allocate all textures in one go
    glGenTextures(128, Globals::texture);
    load_texture("Resources/particle.tga", Globals::texture[0]);
    load_texture("Resources/Marble.tga", Globals::texture[1]);

    glutMainLoop();
    return 0;
}

