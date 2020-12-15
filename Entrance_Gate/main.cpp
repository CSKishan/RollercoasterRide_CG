#include <windows.h>
#include <GL/glut.h>
#include<stdio.h>
#include<math.h>
#define PI 3.14
void init()
{
    glClearColor(0.0,0.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glOrtho(0,50,0,50,0,10);
}
void Display_on_screen(char *string)

{
    while(*string)
    {
	    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*string++);
    }
}
void circle(float radius_x, float radius_y)
{
    int i = 0;
    float angle1 = 0.0;

    glBegin(GL_POLYGON);

    for(i = 0; i < 100; i++)
    {
        angle1 = 2 * PI * i / 100;
        glVertex3f (cos(angle1) * radius_x, sin(angle1) * radius_y, 0);
    }

    glEnd();
}

void sky()
{
    glPushMatrix();
    glColor3f(0.53f,0.807f,0.98f);
    glTranslated(0,10,1), glBegin(GL_QUADS);
    glVertex2d(-100.0,0.0);
    glVertex2d(100.0,0.0);
    glVertex2d(100.0,1);
    glVertex2d(-100.0,1);
    glEnd();
    glPopMatrix();

}


void floor()
{
    glPushMatrix();
    glColor3f(0.0f, 0.75f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2d(-150.0,0.0);
    glVertex2d(150.0,0.0);
    glVertex2d(150.0,-5);
    glVertex2d(-150.0,-5);
    glEnd();
    glPopMatrix();

}
void compoundwall()
{
    glPushMatrix();
    glColor3f(0.36f, 0.3f, 0.05f);
    glBegin(GL_QUADS);
    glVertex2d(-150.0,0.4);
    glVertex2d(150.0,0.4);
    glVertex2d(150.0,-0.4);
    glVertex2d(-150.0,-0.4);
    glEnd();
    glPopMatrix();

}
void gate()
{
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2f(-0.1,-0.4);
    glVertex2f(0.35,-0.4);
    glVertex2f(0.35,0.4);
    glVertex2f(-0.1,0.4);
    glEnd();
    glPopMatrix();

  //gatesky
    glPushMatrix();
    glColor3f(0.53f,0.807f,0.98f);
    glBegin(GL_QUADS);
    glVertex2f(-0.1,-0.3);
    glVertex2f(0.35,-0.3);
    glVertex2f(0.35,0.4);
    glVertex2f(-0.1,0.4);
    glEnd();
    glPopMatrix();

    //gatefield
    glPushMatrix();
    glColor3f(0.0f, 0.75f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.1,-0.3);
    glVertex2f(0.35,-0.3);
    glVertex2f(0.35,-0.4);
    glVertex2f(-0.1,-0.4);
    glEnd();
    glPopMatrix();

    //rollerbase
    glPushMatrix();
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
    glVertex2f(-0.1,-0.3);
    glVertex2f(0.23,-0.3);
    glVertex2f(0.23,-0.1);
    glVertex2f(-0.1,-0.1);
    glEnd();
    glPopMatrix();

    //rollerline11
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.0f);
    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex2d(0.07, -0.1);
    glVertex2d(0.35, -0.08);
    glEnd();
    glPopMatrix();

    //rollerline12
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.0f);
    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex2d(0.875, 0.410);
    glVertex2d(1,0.45);
    glEnd();
    glPopMatrix();

    //rollerline13
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.0f);
    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex2d(-0.875, 0.410);
    glVertex2d(-1,0.45);
    glEnd();
    glPopMatrix();


    //cart
    glPushMatrix();
    glColor3f(0.65f, 0.65f, 0.65f);
    glBegin(GL_QUADS);
    glVertex2f(-0.1,0);
    glVertex2f(0.07,0);
    glVertex2f(0.07,-0.1);
    glVertex2f(-0.1,-0.1);
    glEnd();
    glPopMatrix();

    //cartline1
    glPushMatrix();
    glColor3f(0.75f, 0.75f, 0.75f);
    glLineWidth(13);
    glBegin(GL_LINES);
    glVertex2d(0.025, 0);
    glVertex2d(0.025, 0.25);
    glEnd();
    glPopMatrix();

    //cartline2
    glPushMatrix();
    glColor3f(0.75f, 0.75f, 0.75f);
    glLineWidth(13);
    glBegin(GL_LINES);
    glVertex2d(-0.075, 0);
    glVertex2d(-0.075, 0.25);
    glEnd();
    glPopMatrix();

    //cartline3
    glPushMatrix();
    glColor3f(0.75f, 0.75f, 0.75f);
    glLineWidth(13);
    glBegin(GL_LINES);
    glVertex2d(-0.025, 0);
    glVertex2d(-0.025, 0.25);
    glEnd();
    glPopMatrix();



    //line1
    glPushMatrix();
    glColor3f(0.45f, 0.45f, 0.45f);
    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex2d(-0.1, 0.4);
    glVertex2d(-0.1, -0.4);
    glEnd();
    glPopMatrix();

    //line2
    glPushMatrix();
    glColor3f(0.45f, 0.45f, 0.45f);
    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex2d(-0.05, 0.4);
    glVertex2d(-0.05, -0.4);
    glEnd();
    glPopMatrix();

    //line3
    glPushMatrix();
    glColor3f(0.45f, 0.45f, 0.45f);
    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex2d(0, 0.4);
    glVertex2d(0, -0.4);
    glEnd();
    glPopMatrix();

    //line4
    glPushMatrix();
    glColor3f(0.45f, 0.45f, 0.45f);
    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex2d(0.05, 0.4);
    glVertex2d(0.05, -0.4);
    glEnd();
    glPopMatrix();

    //line5
    glPushMatrix();
    glColor3f(0.45f, 0.45f, 0.45f);
    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex2d(0.1, 0.4);
    glVertex2d(0.1, -0.4);
    glEnd();
    glPopMatrix();

    //line6
    glPushMatrix();
    glColor3f(0.45f, 0.45f, 0.45f);
    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex2d(0.15, 0.4);
    glVertex2d(0.15, -0.4);
    glEnd();
    glPopMatrix();

    //line7
    glPushMatrix();
    glColor3f(0.45f, 0.45f, 0.45f);
    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex2d(0.2, 0.4);
    glVertex2d(0.2, -0.4);
    glEnd();
    glPopMatrix();

    //line8
    glPushMatrix();
    glColor3f(0.45f, 0.45f, 0.45f);
    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex2d(0.25, 0.4);
    glVertex2d(0.25, -0.4);
    glEnd();
    glPopMatrix();

    //line9
    glPushMatrix();
    glColor3f(0.45f, 0.45f, 0.45f);
    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex2d(0.3, 0.4);
    glVertex2d(0.3, -0.4);
    glEnd();
    glPopMatrix();

    //line10
    glPushMatrix();
    glColor3f(0.45f, 0.45f, 0.45f);
    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex2d(0.35, 0.4);
    glVertex2d(0.35, -0.4);
    glEnd();
    glPopMatrix();

    //line11
    glPushMatrix();
    glColor3f(0.45f, 0.45f, 0.45f);
    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex2d(-0.1, 0.4);
    glVertex2d(0.35, 0.4);
    glEnd();
    glPopMatrix();

    //line12
    glPushMatrix();
    glColor3f(0.45f, 0.45f, 0.45f);
    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex2d(-0.1, -0.4);
    glVertex2d(0.35, -0.4);
    glEnd();
    glPopMatrix();

}
void board()
{
    //line1
    glPushMatrix();
    glColor3f(0.35f, 0.16f, 0.14f);
    glLineWidth(15);
    glBegin(GL_LINES);
    glVertex2d(-0.8, 0.1);
    glVertex2d(-0.8, -0.4);
    glEnd();
    glPopMatrix();

    //line2
    glPushMatrix();
    glColor3f(0.35f, 0.16f, 0.14f);
    glLineWidth(15);
    glBegin(GL_LINES);
    glVertex2d(-0.4, 0.1);
    glVertex2d(-0.4, -0.4);
    glEnd();
    glPopMatrix();

    //board
    glPushMatrix();
    glColor3f(0.71, 0.65, 0.26);
    glBegin(GL_QUADS);
    glVertex2f(-0.875,0);
    glVertex2f(-0.325,0);
    glVertex2f(-0.325,0.65);
    glVertex2f(-0.875,0.65);
    glEnd();
    glPopMatrix();

    //cartlineleft
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.0f);
    glLineWidth(9);
    glBegin(GL_LINES);
    glVertex2d(-0.50, 0.010);
    glVertex2d(-0.875, 0.25);
    glEnd();
    glPopMatrix();

     //cartlineright
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.0f);
    glLineWidth(9);
    glBegin(GL_LINES);
    glVertex2d(-0.3750, 0.010);
    glVertex2d(-0.875, 0.35);
    glEnd();
    glPopMatrix();

    //cartlinepoint
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.0f);
    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex2d(-0.375, 0.0);
    glVertex2d(-0.375, 0.015);
    glEnd();
    glPopMatrix();

    //cartline1
    glPushMatrix();
    glColor3f(0.4f, 0.4f, 0.4f);
    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex2d(-0.835, 0.00);
    glVertex2d(-0.835, 0.23);
    glEnd();
    glPopMatrix();

    //cartline11
    glPushMatrix();
    glColor3f(0.4f, 0.4f, 0.4f);
    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex2d(-0.835, 0.00);
    glVertex2d(-0.873, 0.095);
    glEnd();
    glPopMatrix();

    //cartline12
    glPushMatrix();
    glColor3f(0.4f, 0.4f, 0.4f);
    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex2d(-0.835, 0.23);
    glVertex2d(-0.873, 0.12);
    glEnd();
    glPopMatrix();

    //cartline2
    glPushMatrix();
     glColor3f(0.4f, 0.4f, 0.4f);
    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex2d(-0.725, 0.0);
    glVertex2d(-0.725, 0.165);
    glEnd();
    glPopMatrix();

    //cartline21
    glPushMatrix();
     glColor3f(0.4f, 0.4f, 0.4f);
    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex2d(-0.735, 0.0);
    glVertex2d(-0.835, 0.23);
    glEnd();
    glPopMatrix();

    //cartline22
    glPushMatrix();
    glColor3f(0.4f, 0.4f, 0.4f);
    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex2d(-0.835, 0.0);
    glVertex2d(-0.725, 0.165);
    glEnd();
    glPopMatrix();

    //cartline3
    glPushMatrix();
    glColor3f(0.4f, 0.4f, 0.4f);
    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex2d(-0.62, 0.0);
    glVertex2d(-0.62, 0.095);
    glEnd();
    glPopMatrix();

    //cartline31
    glPushMatrix();
    glColor3f(0.4f, 0.4f, 0.4f);
    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex2d(-0.7, 0.0);
    glVertex2d(-0.62, 0.095);
    glEnd();
    glPopMatrix();

    //cartline32
    glPushMatrix();
    glColor3f(0.4f, 0.4f, 0.4f);
    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex2d(-0.72, 0.16);
    glVertex2d(-0.65, 0);
    glEnd();
    glPopMatrix();

    //cartline4
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.0f);
    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex2d(-0.5, 0.0);
    glVertex2d(-0.5, 0.015);
    glEnd();
    glPopMatrix();

    //cartline41
    glPushMatrix();
    glColor3f(0.4f, 0.4f, 0.4f);
    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex2d(-0.63, 0.095);
    glVertex2d(-0.58, 0.0);
    glEnd();
    glPopMatrix();

    //cartline42
    glPushMatrix();
    glColor3f(0.4f, 0.4f, 0.4f);
    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex2d(-0.59, 0.0);
    glVertex2d(-0.55, 0.04);
    glEnd();
    glPopMatrix();

    //cartline43
    glPushMatrix();
    glColor3f(0.4f, 0.4f, 0.4f);
    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex2d(-0.55, 0.0);
    glVertex2d(-0.55, 0.04);
    glEnd();
    glPopMatrix();

    //trackline1
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.0f);
    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex2d(-0.845, 0.33);
    glVertex2d(-0.873, 0.25);
    glEnd();
    glPopMatrix();


    //trackline2
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.0f);
    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex2d(-0.72, 0.24);
    glVertex2d(-0.76, 0.18);
    glEnd();
    glPopMatrix();


    //trackline3
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.0f);
    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex2d(-0.60, 0.16);
    glVertex2d(-0.65, 0.1);
    glEnd();
    glPopMatrix();

    //trackline4
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.0f);
    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex2d(-0.485, 0.1);
    glVertex2d(-0.533, 0.04);
    glEnd();
    glPopMatrix();

    //trackline5
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.0f);
    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex2d(-0.44, 0.05);
    glVertex2d(-0.48, 0.009);
    glEnd();
    glPopMatrix();

     //trackline6
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.0f);
    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex2d(-0.4, 0.02);
    glVertex2d(-0.415, 0.009);
    glEnd();
    glPopMatrix();


    //cart1
    glPushMatrix();
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_QUADS);
    glVertex2f(-0.83,0.315);
    glVertex2f(-0.74,0.25);
    glVertex2f(-0.77,0.195);
    glVertex2f(-0.865,0.255);
    glEnd();
    glPopMatrix();

    //cart2
    glPushMatrix();
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_QUADS);
    glVertex2f(-0.71,0.23);
    glVertex2f(-0.62,0.175);
    glVertex2f(-0.65,0.115);
    glVertex2f(-0.745,0.18);
    glEnd();
    glPopMatrix();

    //cart3
    glPushMatrix();
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_QUADS);
    glVertex2f(-0.59,0.15);
    glVertex2f(-0.50,0.09);
    glVertex2f(-0.53,0.04);
    glVertex2f(-0.625,0.10);
    glEnd();
    glPopMatrix();

    //cartlines1.1
    glPushMatrix();
    glColor3f(0.75f, 0.75f, 0.75f);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2d(-0.845, 0.275);
    glVertex2d(-0.845, 0.245);
    glEnd();
    glPopMatrix();

    //cartlines1.2
    glPushMatrix();
    glColor3f(0.75f, 0.75f, 0.75f);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2d(-0.845, 0.275);
    glVertex2d(-0.835, 0.3);
    glEnd();
    glPopMatrix();

    //cartlines1.3
    glPushMatrix();
    glColor3f(0.75f, 0.75f, 0.75f);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2d(-0.810, 0.315);
    glVertex2d(-0.835, 0.30);
    glEnd();
    glPopMatrix();

    //cartlines1.4
    glPushMatrix();
    glColor3f(0.75f, 0.75f, 0.75f);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2d(-0.810, 0.32);
    glVertex2d(-0.810, 0.29);
    glEnd();
    glPopMatrix();

     //cartlines2.1
    glPushMatrix();
    glColor3f(0.75f, 0.75f, 0.75f);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2d(-0.82, 0.265);
    glVertex2d(-0.82, 0.225);
    glEnd();
    glPopMatrix();

    //cartlines2.2
    glPushMatrix();
    glColor3f(0.75f, 0.75f, 0.75f);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2d(-0.82, 0.265);
    glVertex2d(-0.81, 0.285);
    glEnd();
    glPopMatrix();

    //cartlines2.3
    glPushMatrix();
    glColor3f(0.75f, 0.75f, 0.75f);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2d(-0.79, 0.305);
    glVertex2d(-0.81, 0.285);
    glEnd();
    glPopMatrix();

    //cartlines2.4
    glPushMatrix();
    glColor3f(0.75f, 0.75f, 0.75f);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2d(-0.790, 0.305);
    glVertex2d(-0.790, 0.28);
    glEnd();
    glPopMatrix();

     //cartlines3.1
    glPushMatrix();
    glColor3f(0.75f, 0.75f, 0.75f);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2d(-0.795, 0.24);
    glVertex2d(-0.795, 0.21);
    glEnd();
    glPopMatrix();

    //cartlines3.2
    glPushMatrix();
    glColor3f(0.75f, 0.75f, 0.75f);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2d(-0.795, 0.24);
    glVertex2d(-0.785, 0.26);
    glEnd();
    glPopMatrix();

    //cartlines3.3
    glPushMatrix();
    glColor3f(0.75f, 0.75f, 0.75f);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2d(-0.762, 0.285);
    glVertex2d(-0.785, 0.26);
    glEnd();
    glPopMatrix();

    //cartlines3.4
    glPushMatrix();
    glColor3f(0.75f, 0.75f, 0.75f);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2d(-0.762, 0.285);
    glVertex2d(-0.762, 0.26);
    glEnd();
    glPopMatrix();


    //cartlines4.1
    glPushMatrix();
    glColor3f(0.75f, 0.75f, 0.75f);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2d(-0.72, 0.1975);
    glVertex2d(-0.72, 0.165);
    glEnd();
    glPopMatrix();

    //cartlines4.2
    glPushMatrix();
    glColor3f(0.75f, 0.75f, 0.75f);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2d(-0.705, 0.2175);
    glVertex2d(-0.72, 0.1975);
    glEnd();
    glPopMatrix();

    //cartlines4.3
    glPushMatrix();
    glColor3f(0.75f, 0.75f, 0.75f);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2d(-0.685, 0.2325);
    glVertex2d(-0.71, 0.2175);
    glEnd();
    glPopMatrix();

    //cartlines4.4
    glPushMatrix();
    glColor3f(0.75f, 0.75f, 0.75f);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2d(-0.685, 0.2325);
    glVertex2d(-0.685, 0.2175);
    glEnd();
    glPopMatrix();


    //cartlines5.1
    glPushMatrix();
    glColor3f(0.75f, 0.75f, 0.75f);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2d(-0.7, 0.18);
    glVertex2d(-0.7, 0.15);
    glEnd();
    glPopMatrix();

    //cartlines5.2
    glPushMatrix();
    glColor3f(0.75f, 0.75f, 0.75f);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2d(-0.685, 0.2);
    glVertex2d(-0.7, 0.18);
    glEnd();
    glPopMatrix();

    //cartlines5.3
    glPushMatrix();
    glColor3f(0.75f, 0.75f, 0.75f);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2d(-0.66, 0.215);
    glVertex2d(-0.688, 0.2);
    glEnd();
    glPopMatrix();

    //cartlines5.4
    glPushMatrix();
    glColor3f(0.75f, 0.75f, 0.75f);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2d(-0.66, 0.215);
    glVertex2d(-0.66, 0.2);
    glEnd();
    glPopMatrix();

     //cartlines6.1
    glPushMatrix();
    glColor3f(0.75f, 0.75f, 0.75f);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2d(-0.6725, 0.160);
    glVertex2d(-0.6725, 0.130);
    glEnd();
    glPopMatrix();

    //cartlines6.2
    glPushMatrix();
    glColor3f(0.75f, 0.75f, 0.75f);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2d(-0.6655, 0.185);
    glVertex2d(-0.6725, 0.16);
    glEnd();
    glPopMatrix();

    //cartlines6.3
    glPushMatrix();
    glColor3f(0.75f, 0.75f, 0.75f);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2d(-0.64, 0.2);
    glVertex2d(-0.6655, 0.18);
    glEnd();
    glPopMatrix();

    //cartlines6.4
    glPushMatrix();
    glColor3f(0.75f, 0.75f, 0.75f);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2d(-0.64, 0.2);
    glVertex2d(-0.64, 0.18);
    glEnd();
    glPopMatrix();

    //cartlines7.1
    glPushMatrix();
    glColor3f(0.75f, 0.75f, 0.75f);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2d(-0.60, 0.115);
    glVertex2d(-0.60, 0.085);
    glEnd();
    glPopMatrix();

    //cartlines7.2
    glPushMatrix();
    glColor3f(0.75f, 0.75f, 0.75f);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2d(-0.59, 0.135);
    glVertex2d(-0.60, 0.115);
    glEnd();
    glPopMatrix();

    //cartlines7.3
    glPushMatrix();
    glColor3f(0.75f, 0.75f, 0.75f);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2d(-0.57, 0.155);
    glVertex2d(-0.59, 0.135);
    glEnd();
    glPopMatrix();

    //cartlines7.4
    glPushMatrix();
    glColor3f(0.75f, 0.75f, 0.75f);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2d(-0.57, 0.135);
    glVertex2d(-0.57, 0.155);
    glEnd();
    glPopMatrix();

     //cartlines8.1
    glPushMatrix();
    glColor3f(0.75f, 0.75f, 0.75f);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2d(-0.575, 0.095);
    glVertex2d(-0.575, 0.065);
    glEnd();
    glPopMatrix();

    //cartlines8.2
    glPushMatrix();
    glColor3f(0.75f, 0.75f, 0.75f);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2d(-0.565, 0.115);
    glVertex2d(-0.575, 0.095);
    glEnd();
    glPopMatrix();

    //cartlines8.3
    glPushMatrix();
    glColor3f(0.75f, 0.75f, 0.75f);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2d(-0.545, 0.135);
    glVertex2d(-0.565, 0.115);
    glEnd();
    glPopMatrix();

    //cartlines8.4
    glPushMatrix();
    glColor3f(0.75f, 0.75f, 0.75f);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2d(-0.545, 0.135);
    glVertex2d(-0.545, 0.115);
    glEnd();
    glPopMatrix();

     //cartlines9.1
    glPushMatrix();
    glColor3f(0.75f, 0.75f, 0.75f);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2d(-0.545, 0.082);
    glVertex2d(-0.545, 0.052);
    glEnd();
    glPopMatrix();

    //cartlines9.2
    glPushMatrix();
    glColor3f(0.75f, 0.75f, 0.75f);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2d(-0.535, 0.102);
    glVertex2d(-0.545, 0.082);
    glEnd();
    glPopMatrix();

    //cartlines9.3
    glPushMatrix();
    glColor3f(0.75f, 0.75f, 0.75f);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2d(-0.525, 0.122);
    glVertex2d(-0.535, 0.102);
    glEnd();
    glPopMatrix();

    //cartlines9.4
    glPushMatrix();
    glColor3f(0.75f, 0.75f, 0.75f);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2d(-0.525, 0.122);
    glVertex2d(-0.525, 0.102);
    glEnd();
    glPopMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glRasterPos3f(-0.75,0.55,0);
    Display_on_screen("ROLLERCOASTER RIDE");
}

void ticketcounter()
{
    glPushMatrix();
    glColor3f(0.72, 0.45, 0.20);
    glBegin(GL_QUADS);
    glVertex2f(0.6,-0.45);
    glVertex2f(0.9,-0.45);
    glVertex2f(0.9,0.3);
    glVertex2f(0.6,0.3);
    glEnd();
    glPopMatrix();

    //window
    glPushMatrix();
    glColor3f(0, 0, 0);
    glBegin(GL_QUADS);
    glVertex2f(0.625,0);
    glVertex2f(0.875,0);
    glVertex2f(0.875,0.275);
    glVertex2f(0.625,0.275);
    glEnd();
    glPopMatrix();

    glColor3f(0.0, 0.0, 0.0);
    glRasterPos3f(0.68,-0.075,0);
    Display_on_screen("TICKET");
    glColor3f(0.0, 0.0, 0.0);
    glRasterPos3f(0.66,-0.135,0);
    Display_on_screen("COUNTER");
}

void ticketcounterman()
{
    //head
    glPushMatrix();
    glTranslated(0.75,0.175,0);
    glScaled(0.09,0.09,0.1);
    glColor3f(1.0,1.0,1.0);
    circle(0.60,0.8);
    glPopMatrix();

    //body
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glLineWidth(6);
    glBegin(GL_LINES);
    glVertex2d(0.75, 0.15);
    glVertex2d(0.75, 0);
    glEnd();
    glPopMatrix();

    //left hand
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(6);
    glBegin(GL_LINES);
    glVertex2d(0.75, 0.02);
    glVertex2d(0.82, 0.09);
    glEnd();
    glPopMatrix();

    //right hand
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(6);
    glBegin(GL_LINES);
    glVertex2d(0.68, 0.09);
    glVertex2d(0.75, 0.02);
    glEnd();
    glPopMatrix();

}
void standingman()
{
    //head
    glPushMatrix();
    glTranslated(0.5,-0.5,0);
    glScaled(0.09,0.09,0.1);
    glColor3f(1.0,1.0,1.0);
    circle(0.60,0.8);
    glPopMatrix();

    //body
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glLineWidth(6);
    glBegin(GL_LINES);
    glVertex2d(0.5, -0.5);
    glVertex2d(0.5, -0.8);
    glEnd();
    glPopMatrix();

    //left hand
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(6);
    glBegin(GL_LINES);
    glVertex2d(0.5, -0.7);
    glVertex2d(0.60, -0.6);
    glEnd();
    glPopMatrix();

    //right hand
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(6);
    glBegin(GL_LINES);
    glVertex2d(0.5, -0.7);
    glVertex2d(0.4, -0.6);
    glEnd();
    glPopMatrix();

    //left leg
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(6);
    glBegin(GL_LINES);
    glVertex2d(0.5, -0.8);
    glVertex2d(0.58, -0.9);
    glEnd();
    glPopMatrix();

    //right leg
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(6);
    glBegin(GL_LINES);
    glVertex2d(0.5, -0.8);
    glVertex2d(0.42, -0.9);
    glEnd();
    glPopMatrix();

}

void entranceboard()
{

    //line1
    glPushMatrix();
    glColor3f(0.35f, 0.16f, 0.14f);
    glLineWidth(10);
    glBegin(GL_LINES);
    glVertex2d(-0.125, 0.4);
    glVertex2d(-0.125, 0.475);
    glEnd();
    glPopMatrix();

    //line2
    glPushMatrix();
    glColor3f(0.35f, 0.16f, 0.14f);
    glLineWidth(10);
    glBegin(GL_LINES);
    glVertex2d(0.375, 0.4);
    glVertex2d(0.375, 0.475);
    glEnd();
    glPopMatrix();

    //board
    glPushMatrix();
    glColor3f(1.0, 0.6, 0.0);
    glBegin(GL_QUADS);
    glVertex2f(0.4,0.475);
    glVertex2f(-0.15,0.475);
    glVertex2f(-0.15,0.625);
    glVertex2f(0.4,0.625);
    glEnd();
    glPopMatrix();

    glColor3f(0.0, 0.0, 0.0);
    glRasterPos3f(0.03,0.55,0);
    Display_on_screen("ENTRANCE");

}
void grass()
{
    glPushMatrix();
    glColor3f(0.0,0.4,0.0);
    glBegin(GL_QUADS);
    glVertex2f(-0.7,-0.75);
    glVertex2f(-0.6,-0.75);
    glVertex2f(-0.6,-0.790);
    glVertex2f(-0.7,-0.790);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_POLYGON);
    glVertex2f(-0.60,-0.75);
    glVertex2f(-0.62,-0.65);
    glVertex2f(-0.61,-0.75);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_POLYGON);
    glVertex2f(-0.60,-0.65);
    glVertex2f(-0.62,-0.75);
    glVertex2f(-0.61,-0.75);
    glEnd();
    glPopMatrix();
//left tilt
    glPushMatrix();
    glBegin(GL_POLYGON);
    glVertex2f(-0.63,-0.75);
    glVertex2f(-0.65,-0.65);
    glVertex2f(-0.64,-0.75);
    glEnd();
    glPopMatrix();
//right tilt
    glPushMatrix();
    glBegin(GL_POLYGON);
    glVertex2f(-0.61,-0.625);
    glVertex2f(-0.63,-0.75);
    glVertex2f(-0.62,-0.75);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_POLYGON);
    glVertex2f(-0.61,-0.75);
    glVertex2f(-0.63,-0.65);
    glVertex2f(-0.62,-0.75);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_POLYGON);
    glVertex2f(-0.63,-0.65);
    glVertex2f(-0.65,-0.75);
    glVertex2f(-0.64,-0.75);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_POLYGON);
    glVertex2f(-0.62,-0.75);
    glVertex2f(-0.64,-0.65);
    glVertex2f(-0.63,-0.75);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_POLYGON);
    glVertex2f(-0.64,-0.75);
    glVertex2f(-0.66,-0.65);
    glVertex2f(-0.65,-0.75);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_POLYGON);
    glVertex2f(-0.64,-0.625);
    glVertex2f(-0.66,-0.75);
    glVertex2f(-0.65,-0.75);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_POLYGON);
    glVertex2f(-0.65,-0.75);
    glVertex2f(-0.67,-0.65);
    glVertex2f(-0.66,-0.75);
    glEnd();
    glPopMatrix();

    glBegin(GL_POLYGON);
    glVertex2f(-0.65,-0.65);
    glVertex2f(-0.67,-0.75);
    glVertex2f(-0.66,-0.75);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_POLYGON);
    glVertex2f(-0.66,-0.75);
    glVertex2f(-0.68,-0.65);
    glVertex2f(-0.67,-0.75);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_POLYGON);
    glVertex2f(-0.66,-0.65);
    glVertex2f(-0.68,-0.75);
    glVertex2f(-0.67,-0.75);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_POLYGON);
    glVertex2f(-0.67,-0.75);
    glVertex2f(-0.69,-0.65);
    glVertex2f(-0.68,-0.75);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_POLYGON);
    glVertex2f(-0.67,-0.75);
    glVertex2f(-0.69,-0.65);
    glVertex2f(-0.68,-0.75);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_POLYGON);
    glVertex2f(-0.68,-0.75);
    glVertex2f(-0.70,-0.65);
    glVertex2f(-0.69,-0.75);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_POLYGON);
    glVertex2f(-0.68,-0.75);
    glVertex2f(-0.70,-0.65);
    glVertex2f(-0.69,-0.75);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_POLYGON);
    glVertex2f(-0.68,-0.75);
    glVertex2f(-0.71,-0.65);
    glVertex2f(-0.69,-0.75);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_POLYGON);
    glVertex2f(-0.68,-0.75);
    glVertex2f(-0.70,-0.65);
    glVertex2f(-0.69,-0.75);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_POLYGON);
    glVertex2f(-0.69,-0.75);
    glVertex2f(-0.715,-0.65);
    glVertex2f(-0.70,-0.75);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_POLYGON);
    glVertex2f(-0.69,-0.75);
    glVertex2f(-0.71,-0.65);
    glVertex2f(-0.70,-0.75);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_POLYGON);
    glVertex2f(-0.59,-0.65);
    glVertex2f(-0.615,-0.75);
    glVertex2f(-0.60,-0.75);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glBegin(GL_POLYGON);
    glVertex2f(-0.59,-0.65);
    glVertex2f(-0.61,-0.75);
    glVertex2f(-0.60,-0.75);
    glEnd();
    glPopMatrix();
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();
    glBegin(GL_POLYGON);
    sky();
    floor();
    compoundwall();
    gate();
    board();
    ticketcounter();
    ticketcounterman();
    standingman();
    entranceboard();
    grass();

    glEnd();
    glFlush();
}


int main(int argc,char ** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(1,1);
    glutInitWindowSize(1400, 950);
    glutCreateWindow("CG Project");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}
