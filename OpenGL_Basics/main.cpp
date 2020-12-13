#include<windows.h>
#include<GL/gl.h> //opengl api library
#include<GL/glu.h> //opengl utility library
#include<GL/glut.h> //utility toolkit

void display();
void reshape(int, int);
void timer(int);

void init()
{
    glClearColor(0.0,0.0,0.0,0.0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutInitWindowPosition(200,100);
    glutInitWindowSize(500,500);
    glutCreateWindow("Basic");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
    init();
    glutMainLoop();
}

float x_position = -10.0;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    //glPointSize(10);
    glBegin(GL_QUADS);
    glColor3f(1,0,0);
    glVertex2f(x_position,1.0);
    glColor3f(0,1,-1.0);
    glVertex2f(x_position,-1.0);
    glColor3f(0,0,1);
    glVertex2f(x_position+2.0,-1.0);
    glColor3f(1,1,1);
    glVertex2f(x_position+2.0,1.0);


    glEnd();

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0,0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, 10, -10, 10);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000/60, timer, 0);

    if(x_position<8)
        x_position += 0.15;
}
