/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#include<windows.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <math.h>
#define PI 3.14

void init()
{
    glClearColor(0.0,0.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glOrtho(0,50,0,50,0,10);

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

void halfcircle(float radius_x, float radius_y)
{
    int i = 0;
    float angle1 = 0.0;

    glBegin(GL_POLYGON);

    for(i = 0; i < 51; i++)
    {
        angle1 = 2 * PI * i / 100;
        glVertex3f (cos(angle1) * radius_x, sin(angle1) * radius_y, 0);
    }

    glEnd();
}

void field()
{

    glPushMatrix();
    glColor3f(0.4, 0.8039, 0);
    glBegin(GL_QUADS);
    glVertex2d(-150.0,0.0);
    glVertex2d(200.0,9.0);
    glVertex2d(200.0,0);
    glVertex2d(-150.0,-50);
    glEnd();
    glPopMatrix();
}

void sky()
{
    glPushMatrix();
    glColor3f(0.53f,0.807f,0.98f);
    glTranslated(0,10,1), glBegin(GL_QUADS);
    glVertex2d(-150.0,0.0);
    glVertex2d(150.0,0.0);
    glVertex2d(150.0,-8);
    glVertex2d(-150.0,-8);
    glEnd();
    glPopMatrix();

}

void hillSide()
{
    glPushMatrix();
    glScaled(1,0.6,0);
    glPushMatrix(); //pahar
    glTranslated(-9.5,0.0,1);
    glColor3f(0.42, 0.56, 0.137);
    glTranslatef(0,5,0);
    halfcircle(12,5);
    glPopMatrix();

    glPushMatrix();
    glTranslated(8.5,0.0,1);
    glColor3f(0.0,1.0,0);
    glTranslatef(0,5,0);
    halfcircle(15,7);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-4.5,0.0,1);
    glColor3f(0.68, 1, 0.184);
    glTranslatef(0,5,0);
    halfcircle(6,3);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-13.4,5,1);
    glBegin(GL_TRIANGLES);
    glVertex2f(1.0,0.0);
    glVertex2f(4.0,1.75);
    glVertex2f(5.0,0.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslated(4.2,5,1);
    glRotated(180,0,1,0);
    glBegin(GL_TRIANGLES);
    glVertex2f(1.0,0.0);
    glVertex2f(4.0,1.78);
    glVertex2f(5.0,0.0);
    glEnd();
    glPopMatrix();
    glPopMatrix();
}


void track()
{
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2d(-100.0, -2.0);
    glVertex2d(100.0, -2.0);
    glEnd();
    glPopMatrix();
}

void ticketbox()
{
    int shitf_x = 12;
    int shift_y = -8;
    glPushMatrix();
    glColor3f(0.5f, 0.35f, 0.05f);
    glBegin(GL_QUADS);
    glVertex2d(0 + shitf_x,0.5 + shift_y);
    glVertex2d(0 + shitf_x,5 + shift_y);
    glVertex2d(3 + shitf_x,5 + shift_y);
    glVertex2d(3 + shitf_x,0.5 + shift_y);

    glColor3f(0,0,0);
    glBegin(GL_QUADS);
    glVertex2d(12.2 ,3 + shift_y);
    glVertex2d(12.2 ,4.75 + shift_y);
    glVertex2d(14.8 ,4.75 + shift_y);
    glVertex2d(14.8 ,3 + shift_y);
    glEnd();
    glPopMatrix();
}

void fcart()
{
    int shitf_x = 0;
    int shift_y = -2;
    glPushMatrix();
    glColor3f(0.86f, 0.078f, 0.235f);
    glBegin(GL_QUADS);
    glVertex2d(-0.5 + shitf_x,0.5 + shift_y);
    glVertex2d(0.5 + shitf_x,2 + shift_y);
    glVertex2d(4.5 + shitf_x,2 + shift_y);
    glVertex2d(4.5 + shitf_x,0.5 + shift_y);
    glEnd();
    glPopMatrix();
}

void chain(double pos)
{
    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(5);
    glBegin(GL_LINES);
    glVertex2d(pos, -1.4);
    glVertex2d(pos+3.75, -1.4);
    glEnd();
    glPopMatrix();
}

void cart(double pos)
{
    double shitf_x = 0 + pos;
    double shift_y = -2;
    glPushMatrix();
    glColor3f(0.86f, 0.078f, 0.235f);
    glBegin(GL_QUADS);
    glVertex2d(1.5 + shitf_x,0.5 + shift_y);
    glVertex2d(1.5 + shitf_x,2 + shift_y);
    glVertex2d(4.5 + shitf_x,2 + shift_y);
    glVertex2d(4.5 + shitf_x,0.5 + shift_y);
    glEnd();
    glPopMatrix();
}

void wheels()
{
    float i=0;
    //fcart wheels
    glPushMatrix();
    glTranslated(1,-1.75,0);
    glScaled(0.3,0.3,0);
    glColor3f(0,0.0,0);
    circle(0.88,0.88);
    glPopMatrix();

    glPushMatrix();
    glTranslated(3.5,-1.75,0);
    glScaled(0.3,0.3,0);
    glColor3f(0,0.0,0);
    circle(0.88,0.88);
    glPopMatrix();

    //trailing cart wheels
    glPushMatrix();
    glTranslated(6 + i,-1.75,0);
    glScaled(0.3,0.3,0);
    glColor3f(0,0.0,0);
    circle(0.88,0.88);
    glPopMatrix();

    glPushMatrix();
    glTranslated(7.5 + i,-1.75,0);
    glScaled(0.3,0.3,0);
    glColor3f(0,0.0,0);
    circle(0.88,0.88);
    glPopMatrix();

    i+=3.75;
    glPushMatrix();
    glTranslated(6 + i,-1.75,0);
    glScaled(0.3,0.3,0);
    glColor3f(0,0.0,0);
    circle(0.88,0.88);
    glPopMatrix();

    glPushMatrix();
    glTranslated(7.5 + i,-1.75,0);
    glScaled(0.3,0.3,0);
    glColor3f(0,0.0,0);
    circle(0.88,0.88);
    glPopMatrix();

    i+=3.75;
    glPushMatrix();
    glTranslated(6 + i,-1.75,0);
    glScaled(0.3,0.3,0);
    glColor3f(0,0.0,0);
    circle(0.88,0.88);
    glPopMatrix();

    glPushMatrix();
    glTranslated(7.5 + i,-1.75,0);
    glScaled(0.3,0.3,0);
    glColor3f(0,0.0,0);
    circle(0.88,0.88);
    glPopMatrix();

    i+=3.75;
    glPushMatrix();
    glTranslated(6 + i,-1.75,0);
    glScaled(0.3,0.3,0);
    glColor3f(0,0.0,0);
    circle(0.88,0.88);
    glPopMatrix();

    glPushMatrix();
    glTranslated(7.5 + i,-1.75,0);
    glScaled(0.3,0.3,0);
    glColor3f(0,0.0,0);
    circle(0.88,0.88);
    glPopMatrix();

    i+=3.75;
    glPushMatrix();
    glTranslated(6 + i,-1.75,0);
    glScaled(0.3,0.3,0);
    glColor3f(0,0.0,0);
    circle(0.88,0.88);
    glPopMatrix();

    glPushMatrix();
    glTranslated(7.5 + i,-1.75,0);
    glScaled(0.3,0.3,0);
    glColor3f(0,0.0,0);
    circle(0.88,0.88);
    glPopMatrix();
}

void man()
{
    //head
    glPushMatrix();
    glTranslated(2,-5,0);
    glScaled(0.3,0.3,0);
    glColor3f(1.0,1.0,1.0);
    circle(2,2);
    glPopMatrix();

    //torso
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(6);
    glBegin(GL_LINES);
    glVertex2d(2, -5);
    glVertex2d(2, -7.5);
    glEnd();
    glPopMatrix();

    //left hand
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(6);
    glBegin(GL_LINES);
    glVertex2d(2, -6);
    glVertex2d(0.75, -7);
    glEnd();
    glPopMatrix();

    //left leg
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(6);
    glBegin(GL_LINES);
    glVertex2d(2, -7.5);
    glVertex2d(1.25, -9);
    glEnd();
    glPopMatrix();

    //right hand
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(6);
    glBegin(GL_LINES);
    glVertex2d(2, -6);
    glVertex2d(3.25, -7);
    glEnd();
    glPopMatrix();

    //right leg
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(6);
    glBegin(GL_LINES);
    glVertex2d(2, -7.5);
    glVertex2d(2.75, -9);
    glEnd();
    glPopMatrix();
}

void button()
{
    //down
    glColor3f(1.0,0.0,0.0);
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2i(21.5,6);
    glVertex2i(27,6);

    //right
    glColor3f(1.0,0.0,0.0);
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2i(27,6);
    glVertex2i(27,8);

    //top
    glColor3f(1.0,0.0,0.0);
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2i(21.5,8);
    glVertex2i(27,8);

    //left
    glColor3f(1.0,0.0,0.0);
    glLineWidth(3);
    glBegin(GL_LINES);
    glVertex2i(21.5,8);
    glVertex2i(21.5,6);
}

void Display_on_screen(char *string)

{
    while(*string)
    {
	    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,*string++);
    }
}

void display()
{

    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0,1.0,0.0);
    glRasterPos2i(15,40);
    glRasterPos3f(19.5,40,0);
    Display_on_screen("ROLLERCOASTER RIDE");

    glRasterPos3f(7,26,0);
    Display_on_screen("Keerthesh S");
    glRasterPos3f(34,26,0);
    Display_on_screen("4NM17CS087");

    glRasterPos3f(7,22,0);
    Display_on_screen("Kiran Mahadev Giraddi");
    glRasterPos3f(34,22,0);
    Display_on_screen("4NM17CS088");

    glRasterPos3f(7,18,0);
    Display_on_screen("Kirthi Puthran");
    glRasterPos3f(34,18,0);
    Display_on_screen("4NM17CS089");

    glRasterPos3f(7,14,0);
    Display_on_screen("Kishan");
    glRasterPos3f(34,14,0);
    Display_on_screen("4NM17CS090");

    glRasterPos3f(22.7,6.5,0);
    Display_on_screen("NEXT");
    //button
    button();

    // top line
    glColor3f(1.0,0.0,0.0);
    glLineWidth(5);
    glBegin(GL_LINES);
    glVertex2i(17.5,42.7);
    glVertex2i(31.5,42.7);

    // bottom line
    glColor3f(1.0,0.0,0.0);
    glLineWidth(5);
    glBegin(GL_LINES);
    glVertex2i(17.5,39);
    glVertex2i(31.5,39);

    glEnd();
    glFlush();

}

void rc_gate()
{
    glClear(GL_COLOR_BUFFER_BIT);

    //back
    sky();
    hillSide();
    field();

    track();
    fcart();
    chain(4.5);
    cart(3.75);
    chain(8.25);
    cart(7.5);
    chain(12);
    cart(11.25);
    chain(15.75);
    cart(15);
    chain(19.5);
    wheels();

    man();
    ticketbox();

    glutPostRedisplay();
    glFlush();

}

void mymouse(int button,int state,int x,int y)
{
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
	    glLoadIdentity();
	    glOrtho(-20.0, 20.0, -10.0, 10.0, -15.0, 15.0);
	    glutDisplayFunc(rc_gate);
	}
	glutPostRedisplay();
}


int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(1,1);
    glutInitWindowSize(1400, 950);
    glutCreateWindow("CG PROJECT");
    glutMouseFunc(mymouse);
    init();
    glutDisplayFunc(display);
    glutMainLoop();
}
