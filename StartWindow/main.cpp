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



int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(1,1);
    glutInitWindowSize(1400, 950);
    glutCreateWindow("CG PROJECT");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
}
