#include<windows.h>
#include<GL/gl.h> //opengl api library
#include<GL/glu.h> //opengl utility library
#include<GL/glut.h> //utility toolkit

void display();
void reshape(int, int);

void init()
{
    glClearColor(0.0,0.0,0.0,0.0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);

    glutInitWindowPosition(200,100);
    glutInitWindowSize(500,500);
    glutCreateWindow("Basic");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    init();
    glutMainLoop();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glPointSize(10);
    glBegin(GL_TRIANGLES);
    glColor3f(1,0,0);
    glVertex2f(5,5);
    glColor3f(0,1,0);
    glVertex2f(-5,-5);
    glColor3f(0,0,1);
    glVertex2f(-5,5);


    glEnd();

    glFlush();
}

void reshape(int w, int h)
{
    glViewport(0,0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, 10, -10, 10);
    glMatrixMode(GL_MODELVIEW);


}
