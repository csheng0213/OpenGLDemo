//
//  main.cpp
//  OpenGLDemo
//
//  Created by cs on 16/9/29.
//  Copyright © 2016年 cs. All rights reserved.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <Math.h>

#define GL_PI 3.1415f


GLfloat x1 = 100.0f;
GLfloat y2 = 150.0f;
GLsizei rsize = 50.f;

GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;

GLfloat windowWidth;
GLfloat windowHeight;

GLfloat nRange = 250.0f;
void setupRc()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glPointSize(1.0f);
}

void DrawTest()
{
    glRectf(x1, y2, x1 + rsize, y2 + rsize);
    glutWireTeapot(50.0f);
}

void DrawPointTest()
{
    glBegin(GL_POINTS);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(50.0f, 50.0f, 50.0f);
    glEnd();
}

void DrawPointTest1()
{
    GLfloat X, Y, Z , angle, xRot = 30, yRot = 30;
    glPushMatrix();
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    
    glBegin(GL_POINTS);
        Z = -50.0f;
        for(angle = 0.0f; angle <= (2.0*GL_PI)*3.0f; angle += 0.1f)
        {
            X = 50.0f*sin(angle);
            Y = 50.0f*cos(angle);
            glVertex3f(X, Y, Z);
            Z += 0.5f;
        }
    glEnd();
    glPopMatrix();
    
}

void Display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0, 0);
    
    printf("x1: %f y1: %f w: %f h: %f \n", x1, y1, x1+rsize, y2+rsize);
    
    DrawPointTest1();
    
    glFlush();
    glutSwapBuffers();
}

void ChangSize(GLsizei w, GLsizei h)
{
    if(h == 0 )
        h = 1;
    
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    if( w <= h )
    {
        windowHeight = 250.0f*h/w;
        windowWidth = 250.0f;
    }else
    {
        windowWidth = 250.0f*w/h;
        windowHeight = 250.0f;
    }
    if(w <=h )
    {
        glOrtho(-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);
    }else
    {
        glOrtho(-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void TimerFunction(int value)
{
    if(x1 > windowWidth-rsize || x1 < 0)
        xstep = -xstep;
    
    if(y2 < windowHeight-rsize || y2 < 0)
        ystep = -ystep;
    
    if(x1 > windowWidth - rsize)
        x1 = windowWidth - rsize - 1;
    
    if(y2 > windowHeight -rsize)
        y2 = windowHeight- rsize - 1;
    
    x1 += xstep;
//    y1 += ystep;
    
    glutPostRedisplay();
    glutTimerFunc(33, TimerFunction, 1);
    
}
int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Xcode Glut Demo");
    glutDisplayFunc(Display);
    glutReshapeFunc(ChangSize);
    
    glutTimerFunc(33, TimerFunction, 1);
    
    setupRc();
    
    glutMainLoop();
}