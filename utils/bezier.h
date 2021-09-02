#ifndef BEZIER_H
#define BEZIER_H

#include <GL/gl.h>
#include <GL/glut.h>

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include <QDebug>

#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 520
#define CTRL_POINT_DIAMETER 10.0f

float p0[2];
float p1[2];
float p2[2];
float p3[2];
float tar=4;

float* bezier(float t, float* p0,float* p1,float* p2,float* p3)
{
    float *res = (float*)malloc(sizeof(float) * 2);
    res[0]=pow((1-t),3)*p0[0]+3*t*pow((1-t),2)*p1[0]+3*pow(t,2)*(1-t)*p2[0]+pow(t,3)*p3[0];
    res[1]=pow((1-t),3)*p0[1]+3*t*pow((1-t),2)*p1[1]+3*pow(t,2)*(1-t)*p2[1]+pow(t,3)*p3[1];
    return res;
}

void displayBezier() {
    glDisable(GL_LIGHTING);
    glColor3f(1,0,0);
    glColor3f(0,1,0);
    glColor3f(0,0,1);
    glColor3f(1,1,1);

    glPointSize(2);
    glColor3f(1,1,0);
    glBegin(GL_LINE_STRIP);
    for(float t=0;t<1;t+=0.02f)
    {
        float* p = bezier(t,p0,p1,p2,p3);
        glVertex3f(p[0],0.1,p[1]);
        free(p);
    }
    glEnd();
    glPointSize(9);
    glBegin(GL_POINTS);
    glColor3f(1,0,0);
    glVertex3f(p0[0],0.1, p0[1]);
    glColor3f(0,1,0);
    glVertex3f(p1[0],0.1, p1[1]);
    glColor3f(0,0,1);
    glVertex3f(p2[0],0.1, p2[1]);
    glColor3f(1,1,1);
    glVertex3f(p3[0],0.1,p3[1]);
    glEnd();

    glFlush();
    glEnable(GL_LIGHTING);
}

#endif // BEZIER_H
