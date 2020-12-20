
#include <windows.h>
#include <GL/glut.h>
#include<stdio.h>
#include<math.h>
#define PI 3.14

void display();
void draw_wagon();
void draw_seat();
void place_camera(int);
void set_material(int material);

float x_position=0.5;
float y_position=-0.5;
float x_pos=0.35;
int state=1;

//* LEFT and RIGHT arrow: Look Around 360 degrees"
//* UP and DOWN arrow: Move forward and backward"
//* + : Move up"
//* - : Move down"

const int SKY_FRONT=0,SKY_RIGHT=1,SKY_LEFT=2,SKY_BACK=3,SKY_UP=4,SKY_DOWN=5, ROLLER_BODY=6, ROLLER_FRAME=7;
int ni=0, prevx=0, rcam=1,bezno,camw=1, roll=0, background=0;
GLint skybox[6], grass,help=0,x_r=0, y_r=0, z_r=0;
GLfloat viewer[3] = {1.0f, 0.0f, 0.0f},camera[3] = {0.0f, 0.0, 0.0};
GLdouble curr=0, prev=0,angle=0.0,c_angle=90.0,lx=50.0,ly=50.0,lz=50.0,bez_prog=0.0,roller_speed=0.00015,gy=0,movcord[3]={-150,-10,200};

double bez[][3]={
	{30,10,-200},{30,10,-110},	{30,10,10},	{30,10,50},	{30,70,100}, {60,90,140}, {80,80,100},
	{70,80,70}, {0,50,80}, {-20,30,80},{-45, 25, 60}, {-70,20,50}, {-40,10,30}, {-30,30,10},
	{-90,30,20}, {-120,130,60}, {-115,160,75}, {-110, 200, 130}, {-100, 160, 200}, {-90,130,250},
	{-50,150,260}, {-25,150,260}, {-5,140,260}, {25,160,260}, {40,130,230}, {55,110,210},
	{70, 90, 160}, {65, 100,140}, {45, 110, 110}, {25, 120, 90}, {-50, 140, 100}, {-100, 150, 100},
	{-150, 130, 100},{-170,120,110}, {-175,120, 180 },{-120,90,150}, {-170, 110, 120}, {-190, 80,  140},
	{-170, 60, 150},/**/  {-160, 50, 160},{-100, 25, 170},{-15, 1.5, 170},{50, 0, 170}, {100, 0, 170},
	{160, 0, 170},{200, 20, 170}, {260, 50, 170},{290, 50, 150}, {320, 65, 110},{330, 65, 80},
	{340, 65, 60}, {350, 80, 30}, {350, 130, 0},{350, 100, -60},{330, 70, -100},{310, 100, -170},
	{280, 80, -210},{250, 60, -250},{230, 30, -280}, {200, 55, -290}, {170, 35, -270}, {150, 22, -250},
	{100, 20, -230},{80, 35, -200},{60, 30, -170}, {35, 20, -150}, {30,10,-115}, {30,10,-105},
	{30,10,-105}, {30,10,-105}
};

void init()
{
    glClearColor(0.0,0.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    glOrtho(0,50,0,50,0,10);
}
void timer(int);

//float x_pos = 0;
//int state = 1;

void mymouse(int, int, int ,int);
void mymouse2(int, int, int ,int);

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

void button()
{
    glColor3f(0, 0, 0);
    glBegin(GL_QUADS);
    //glColor3f(0, 0, 1);
    glVertex2f(21.5,8);
    glVertex2f(21.5,6);
    //glColor3f(1, 0, 0);
    glVertex2f(27,6);
    glVertex2f(27,8);
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
    glVertex2d(x_pos-0.45, 0.4);
    glVertex2d(x_pos-0.45, -0.4);
    glEnd();
    glPopMatrix();

    //line2
    glPushMatrix();
    glColor3f(0.45f, 0.45f, 0.45f);
    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex2d(x_pos-0.4, 0.4);
    glVertex2d(x_pos-0.4, -0.4);
    glEnd();
    glPopMatrix();

    //line3
    glPushMatrix();
    glColor3f(0.45f, 0.45f, 0.45f);
    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex2d(x_pos-0.35, 0.4);
    glVertex2d(x_pos-0.35, -0.4);
    glEnd();
    glPopMatrix();

    //line4
    glPushMatrix();
    glColor3f(0.45f, 0.45f, 0.45f);
    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex2d(x_pos-0.3, 0.4);
    glVertex2d(x_pos-0.3, -0.4);
    glEnd();
    glPopMatrix();

    //line5
    glPushMatrix();
    glColor3f(0.45f, 0.45f, 0.45f);
    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex2d(x_pos-0.25, 0.4);
    glVertex2d(x_pos-0.25, -0.4);
    glEnd();
    glPopMatrix();

    //line6
    glPushMatrix();
    glColor3f(0.45f, 0.45f, 0.45f);
    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex2d(x_pos-0.2, 0.4);
    glVertex2d(x_pos-0.2, -0.4);
    glEnd();
    glPopMatrix();

    //line7
    glPushMatrix();
    glColor3f(0.45f, 0.45f, 0.45f);
    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex2d(x_pos-0.15, 0.4);
    glVertex2d(x_pos-0.15, -0.4);
    glEnd();
    glPopMatrix();

    //line8
    glPushMatrix();
    glColor3f(0.45f, 0.45f, 0.45f);
    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex2d(x_pos-0.1, 0.4);
    glVertex2d(x_pos-0.1, -0.4);
    glEnd();
    glPopMatrix();

    //line9
    glPushMatrix();
    glColor3f(0.45f, 0.45f, 0.45f);
    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex2d(x_pos-0.05, 0.4);
    glVertex2d(x_pos-0.05, -0.4);
    glEnd();
    glPopMatrix();

    //line10
    glPushMatrix();
    glColor3f(0.45f, 0.45f, 0.45f);
    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex2d(x_pos-0, 0.4);
    glVertex2d(x_pos-0, -0.4);
    glEnd();
    glPopMatrix();

    //line11
    glPushMatrix();
    glColor3f(0.45f, 0.45f, 0.45f);
    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex2d(x_pos-0.45, 0.4);
    glVertex2d(x_pos, 0.4);
    glEnd();
    glPopMatrix();

    //line12
    glPushMatrix();
    glColor3f(0.45f, 0.45f, 0.45f);
    glLineWidth(7);
    glBegin(GL_LINES);
    glVertex2d(x_pos-0.45, -0.4);
    glVertex2d(x_pos, -0.4);
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
    glTranslated(x_position,y_position,0);
    glScaled(0.09,0.09,0.1);
    glColor3f(1.0,1.0,1.0);
    circle(0.6,0.8);
    glPopMatrix();

    //body
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glLineWidth(6);
    glBegin(GL_LINES);
    glVertex2d(x_position, y_position);
    glVertex2d(x_position, y_position-0.3);
    glEnd();
    glPopMatrix();

    //left hand
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(6);
    glBegin(GL_LINES);
    glVertex2d(x_position,y_position-0.2);
    glVertex2d(x_position+0.1,y_position-0.1);
    glEnd();
    glPopMatrix();

    //right hand
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(6);
    glBegin(GL_LINES);
    glVertex2d(x_position,y_position-0.2);
    glVertex2d(x_position-0.1,y_position-0.1);
    glEnd();
    glPopMatrix();

    //left leg
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(6);
    glBegin(GL_LINES);
    glVertex2d(x_position,y_position-0.3);
    glVertex2d(x_position-0.1,y_position-0.4);
    glEnd();
    glPopMatrix();

    //right leg
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(6);
    glBegin(GL_LINES);
    glVertex2d(x_position,y_position-0.3);
    glVertex2d(x_position+0.1,y_position-0.4);
    glEnd();
    glPopMatrix();


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
void grassMain()
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




void draw_bezier();
void moveToBezier(double);
double bezier(double, double, double, double, double);
void draw_cyl(float x1, float y1, float z1, float x2,float y2, float z2, float radius,int subdivisions);


void set_material(int m)
{
	if(m==0)
	{
		float materialGrey[]={0.8,0.8,0.8},materialWhite[]={0.2,0.2,0.2};
		//float materialDarkGreen[]={0.33,0.69,0.0}, materialLightGreen[]={0.48,0.98,0.0};
		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,materialGrey);
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,materialWhite);
	}

	if(m==ROLLER_BODY)
	{	float materialColours[][3]={{0.6,0.6,0.6},{1,0.6,0.3}, {0.2,0.2,0.2},  {0.75,0.164,0.164},{0.601,0.19,1.0}, {1,1,0}},materialLightBr[]={1,0.0,0.0};
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,materialLightBr);
		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,materialColours[1]);
	}
}

//Lighting is ready
void initLights()
{

	GLfloat whiteSpecularMaterial[] = {1.0,1.0,1.0},light_post0[]={0.0,0.0,10.0,1.0},whiteSpecularLight[] = {1.0, 1.0, 1.0},blackAmbientLight[] = {0.3, 0.3, 0.3},whiteDiffuseLight[] = {1.0, 1.0, 1.0},mShininess[] = {50},twoModel[]={GL_TRUE};
	glEnable (GL_DEPTH_TEST);
    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, whiteSpecularLight);
   	glLightfv(GL_LIGHT0, GL_AMBIENT, blackAmbientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteDiffuseLight);
	glLightfv(GL_LIGHT0, GL_POSITION, light_post0);
	glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, twoModel);
 	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, whiteSpecularMaterial);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mShininess);
}


void Draw_Skybox(float x, float y, float z, float width, float height, float length)
{

        float materialBlue[]={0,0.8,1}, materialWhite[]={1,1,1};
		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,materialWhite);
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,materialBlue);
		//glMaterialfv(GL_FRONT_AND_BACK,GL_TEXTURE_COMPONENTS,materialWhite);


	glDisable(GL_DEPTH_TEST);
	x = x - width  / 2;
	y = y - height / 2;
	z = z - length / 2;
	glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D,skybox[SKY_UP]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y+height, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y+height, z+length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y+height,	z+length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y+height,	z);
	glEnd();

	//glBindTexture(GL_TEXTURE_2D,skybox[SKY_FRONT]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y,		z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y,		z+length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y+height,	z+length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y+height,	z);
	glEnd();

	//glBindTexture(GL_TEXTURE_2D,skybox[SKY_BACK]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y+height,	z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y+height,	z+length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y,		z+length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y,		z);
	glEnd();

	//glBindTexture(GL_TEXTURE_2D,skybox[SKY_RIGHT]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y,		z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y+height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y+height,	z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y,		z);
	glEnd();

	//glBindTexture(GL_TEXTURE_2D,skybox[SKY_LEFT]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y,		z+length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y+height, z+length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y+height, z+length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y,		z+length);
	glEnd();

	//glBindTexture(GL_TEXTURE_2D,skybox[SKY_DOWN]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y,		z+length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y,		z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y,		z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y,		z+length);
	glEnd();
 	glDisable(GL_TEXTURE_2D);


}


void draw_ground()
{
	float materialDarkGreen[]={0.33,0.69,0.0}, materialLightGreen[]={0.48,0.98,0.0};
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,materialDarkGreen);
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,materialLightGreen);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(5000,-10,5000);
	glTexCoord2f(800.0f, 0.0f); glVertex3f(5000,-10,-5000);
	glTexCoord2f(800.0f, 800.0f); glVertex3f(-5000,-10,-5000);
	glTexCoord2f(0.0f, 800.0f); glVertex3f(-5000,-10,5000);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glLineWidth(5.0);
	glTranslatef(0.0, -2, 0.0);
	draw_bezier();
	glTranslatef(0.0, 2, 0.0);
}

void idle()
{
	double bez_offset=0.000;

	if(roll)
	{
		if(ni==bezno-2)
		{
			roll=0;
			bez_prog=0.0;
			ni=0.0;
			viewer[0]=1.0;
			viewer[1]=viewer[2]=camera[0]=camera[1]=camera[2]=x_r=0.0;
			return;
		}
		if(bez_prog>=1.0)
		{
			ni++;
			bez_prog=0.0;
		}
		bez_prog+=roller_speed;
		moveToBezier(bez_prog+bez_offset);
	}
	display();
}

void draw_seat()
{

glPushMatrix();
//glEnable(GL_LIGHTING);
glTranslatef(1.0, 0.0, -1.0);
glRotatef(90.0, 0.0, 0.0, 1.0);
glTranslatef(0.0, 0.5, 0.0);
draw_cyl(-2.5,0.0,0.0,2.5,0.0,0.0,0.05,6);
glTranslatef(0.0,-0.5,0.0);
glNormal3f(0.0,1.0,0.0);
glScalef(4.0, 0.1, 1.0);
glutSolidCube(1.0);
glScalef(1/4.0, 1/0.1, 1.0);
glTranslatef(0.0, 0.5, -1.0);
glRotatef(80.0, 1.0, 0.0, 0.0);
glScalef(4.0, 0.1, 1.0);
glNormal3f(0.0,1.0,0.0);
glutSolidCube(1.0);
glScalef(1/4.0, 1/0.1, 1.0);
glPopMatrix();

}


void draw_wheels()
{
	int i=0;
	glPushMatrix();
		glRotatef(90.0,1.0,0.0,0.0);
		for(i=0;i<4;i++)
		{
	glutSolidTorus(0.2,0.3,4,16);
	glTranslatef(0.0,2.0,0.0);
		}
	glPopMatrix();
}


void draw_loco()
{
	int i;
	double eqn[]={1.0, 0.0, 0.0, -0.5};
	double eqnt[]={-1.0, 0.0, 0.0, 1.6};
	glPushMatrix();
	set_material(ROLLER_BODY);
	glEnable (GL_LIGHTING);
	glEnable(GL_CLIP_PLANE0);
	glClipPlane(GL_CLIP_PLANE0, eqn);
	glScalef(1.3, 2.0, 1.5);
	glutSolidCube(3.0);
	glScalef(1/1.3, 1/2.0, 1/1.5);
	glDisable(GL_CLIP_PLANE0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glEnable(GL_CLIP_PLANE1);
	glClipPlane(GL_CLIP_PLANE1, eqnt);
	glTranslatef(0.0, 0.0, 3.0);
	glutSolidTorus(0.2, 3.0, 10, 10);
	draw_seat();
	glTranslatef(0.0, 0.0, -1.5);
	glutSolidTorus(0.2, 3.0, 10, 10);
	glTranslatef(0.0, 0.0, -1.5);
	glutSolidTorus(0.2, 3.0, 10, 10);
	draw_seat();
	glTranslatef(0.0, 0.0, -1.5);
	glutSolidTorus(0.2, 3.0, 10, 10);
	glTranslatef(0.0, 0.0, -1.5);
	glutSolidTorus(0.2, 3.0, 10, 10);
	glDisable(GL_CLIP_PLANE1);
	set_material(0);
	glTranslatef(2.5,1.0,0);
	draw_wheels();
	glTranslatef(-2.5,-1.0,0);
	glTranslatef(2.5,-1.0,0);
	draw_wheels();

    glPopMatrix();


}

void draw_tank()
{
	GLdouble cuteqn[]={0.0,-1.0,0.0,0.0};
	glPushMatrix();
	float materialGrey[]={0.8,0.8,0.8},materialWhite[]={0.2,0.2,0.2};
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,materialGrey);
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,materialWhite);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_CLIP_PLANE1);
	glClipPlane(GL_CLIP_PLANE1, cuteqn);
	glScalef(10.0,1.0,2.0);
	glutSolidCube(20.0);
	glDisable(GL_CLIP_PLANE1);
	glDisable(GL_LIGHTING);
	glColor3f(0.7921,0.8824,0.9);
	glBegin(GL_POLYGON);
	glVertex3f(10,-3,10);
	glVertex3f(10,-3,-10);
	glVertex3f(-10,-3,-10);
	glVertex3f(-10,-3,10);

	glEnd();
	glPopMatrix();
}

void getCurveAt(GLdouble *ax,GLdouble *ay,GLdouble *az,int index,GLdouble atpoint)
{
	if(ax) *ax=-bezier(bez[0+index][0],bez[1+index][0],bez[2+index][0],bez[3+index][0],atpoint);
	if(ay) *ay=-bezier(bez[0+index][1],bez[1+index][1],bez[2+index][1],bez[3+index][1],atpoint);
	if(az) *az=-bezier(bez[0+index][2],bez[1+index][2],bez[2+index][2],bez[3+index][2],atpoint);

}

void ride3d(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glColor4f(1.0,1.0,1.0,1.0);
	glColor4f(0.0,0.0,0.0,0.0);
	glLoadIdentity();
	gluLookAt(viewer[0], viewer[1], viewer[2],camera[0], camera[1], camera[2],0, 1, 0);
	glRotatef(x_r, 0, 1, 0);
	Draw_Skybox(viewer[0]+(0.05*movcord[0]),viewer[1]+(0.05*movcord[1]),viewer[2]+(0.05*movcord[2]),250,250,250);

	glTranslatef(movcord[0],movcord[1],movcord[2]);
	draw_ground();
	glPushMatrix();
	glTranslatef(80,0,165);
	draw_tank();
	glPopMatrix();
	double tx,ty,tz,nx,ny,nz;
	getCurveAt(&tx,&ty,&tz,ni,bez_prog+0.058);
	getCurveAt(&nx,&ny,&nz,ni,bez_prog+0.070);
	gy=ny;
	float bz1=bezier(bez[0+ni][2],bez[1+ni][2],bez[2+ni][2],bez[3+ni][2],bez_prog+0.02)-1*fabs(cos(angle*3.14/180.0));
	float bx1=bezier(bez[0+ni][0],bez[1+ni][0],bez[2+ni][0],bez[3+ni][0],bez_prog+0.02)-1*fabs(sin(angle*3.14/180.0));
	float bz2=bezier(bez[0+ni][2],bez[1+ni][2],bez[2+ni][2],bez[3+ni][2],bez_prog+0.02)+1*fabs(cos(angle*3.14/180.0));
	float bx2=bezier(bez[0+ni][0],bez[1+ni][0],bez[2+ni][0],bez[3+ni][0],bez_prog+0.02)+1*fabs(sin(angle*3.14/180.0));
	double degreer = atan2(1,bx2-bx1)*fabs(sin(angle*3.14/180.0))* 180 / 3.14+fabs(cos(angle*3.14/180.0))*atan2(1,bz2-bz1)* 180 / 3.14;
	double angler = degreer ;
	double degree= atan2(nz-tz, nx-tx);
	angle = degree * 180 / 3.14;
	double degreey= atan2(ny-ty,1);
	double angley = degreey * 180 / 3.14;
	glPushMatrix();
	glTranslatef(-nx,-ny,-nz);
	glRotatef(-angle, 0.0, 1.0, 0.0);
	glRotatef(angley-90, 0, 0, 1.0);
	glRotatef(angler-45, 0.0, 1.0, 0.0);
	if(camw==0) angle=90.0;
	glTranslatef(-2.5, 3.0, 0.0);
	draw_loco();
	glPopMatrix();

	glutSwapBuffers();

}

void displayReshape(int width,int height)
{
	glViewport(0,0,width,height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65,(GLfloat)width/(GLfloat)height,0.01f,1000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

double bezier(double x0, double x1, double x2, double x3, double t)
{
	return	0.5*((2.0f*x1)+(-x0+x2)*t+(2.0f*x0-5.0f*x1+4*x2-x3)*t*t+(-x0+3.0f*x1-3.0f*x2+x3)*t*t*t);
}

void moveToBezier( double t){


    int n=0.0;
			viewer[0]=1.0;
			viewer[1]=0.0;
			viewer[2]=0.0;

			if(camw==1)
			{


				getCurveAt(&movcord[0],&movcord[1], &movcord[2], ni, t);
				movcord[0]+=1.0;
				movcord[1]-=3.5;

				camera[0]=bezier(bez[0+ni][0],bez[1+ni][0],bez[2+ni][0],bez[3+ni][0],t+0.1)-bezier(bez[0+ni][0],bez[1+ni][0],bez[2+ni][0],bez[3+ni][0],t);
	            camera[1]=bezier(bez[0+ni][1],bez[1+ni][1],bez[2+ni][1],bez[3+ni][1],t+0.1)-bezier(bez[0+ni][1],bez[1+ni][1],bez[2+ni][1],bez[3+ni][1],t);
	            camera[2]=bezier(bez[0+ni][2],bez[1+ni][2],bez[2+ni][2],bez[3+ni][2],t+0.1)-bezier(bez[0+ni][2],bez[1+ni][2],bez[2+ni][2],bez[3+ni][2],t);

			if(gy<movcord[1]+2.5)
				 movcord[1]=gy-2.5;
			display();
			}
}



void renderCylinder(float x1, float y1, float z1, float x2,float y2, float z2, float radius,int subdivisions, GLUquadricObj *quadric)
{

float vx = x2-x1,vy = y2-y1,vz = z2-z1;
if(vz == 0) vz = .0001;
float v = sqrt( vx*vx + vy*vy + vz*vz );
float ax = 57.2957795*acos( vz/v );
if ( vz < 0.0 )
    ax = -ax;
float rx = -vy*vz;
float ry = vx*vz;
glPushMatrix();
glTranslatef( x1,y1,z1 );
glRotatef(ax, rx, ry, 0.0);
gluQuadricOrientation(quadric,GLU_OUTSIDE);
gluCylinder(quadric, radius, radius, v, subdivisions, 1);
gluQuadricOrientation(quadric,GLU_INSIDE);
gluDisk( quadric, 0.0, radius, subdivisions, 1);
glTranslatef( 0,0,v );
gluQuadricOrientation(quadric,GLU_OUTSIDE);
gluDisk( quadric, 0.0, radius, subdivisions, 1);
glPopMatrix();
}

void draw_cyl(float x1, float y1, float z1, float x2,float y2, float z2, float radius,int subdivisions)
{
GLUquadricObj *quadric=gluNewQuadric();
gluQuadricNormals(quadric, GLU_SMOOTH);

float materialGrey[]={0.8,0.8,0.8},materialWhite[]={0.2,0.2,0.2};
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,materialGrey);
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,materialWhite);

renderCylinder(x1,y1,z1,x2,y2,z2,radius,subdivisions,quadric);
gluDeleteQuadric(quadric);
}



void draw_bezier()
{
    //TRACK//
	glPushMatrix();
      GLfloat bx,by,bz,bx1,by1,bz1,bx2,by2,bz2,i=0.0;
	  int n=0;
      glColor3f(0.0,0.0,0.0);
	  glColor3f(1.0,1.0,0.0);
	  glDisable(GL_LIGHTING);
	  glEnable(GL_DEPTH_TEST);
	   for(n=0; n<bezno-2; n++)
	   {

        for(i=0.0;i<=1.0;i+=0.02)
       {	glBegin(GL_LINES);
			bx1=bezier(bez[0+n][0],bez[1+n][0],bez[2+n][0],bez[3+n][0],i)-1.3*fabs(sin(angle*3.14/180.0));
            by1=bezier(bez[0+n][1],bez[1+n][1],bez[2+n][1],bez[3+n][1],i);
            bz1=bezier(bez[0+n][2],bez[1+n][2],bez[2+n][2],bez[3+n][2],i)-1.3*fabs(cos(angle*3.14/180.0));
            glVertex3f(bx1,by1,bz1);
			bx2=bezier(bez[0+n][0],bez[1+n][0],bez[2+n][0],bez[3+n][0],i)+1.3*fabs(sin(angle*3.14/180.0));
            by2=bezier(bez[0+n][1],bez[1+n][1],bez[2+n][1],bez[3+n][1],i);
            bz2=bezier(bez[0+n][2],bez[1+n][2],bez[2+n][2],bez[3+n][2],i)+1.3*fabs(cos(angle*3.14/180.0));
			glVertex3f(bx2,by2,bz2);
			glEnd();
		}
		glBegin(GL_LINE_STRIP);
		for(i=0.0;i<=1.00;i+=0.02)
       {
       		bz1=bezier(bez[0+n][2],bez[1+n][2],bez[2+n][2],bez[3+n][2],i+0.02)-1.0*fabs(cos(angle*3.14/180.0));
			bx1=bezier(bez[0+n][0],bez[1+n][0],bez[2+n][0],bez[3+n][0],i+0.02)-1.0*fabs(sin(angle*3.14/180.0));
			by1=bezier(bez[0+n][1],bez[1+n][1],bez[2+n][1],bez[3+n][1],i+0.02);
			glVertex3f(bx1,by1,bz1);
		}
		glEnd();
		glBegin(GL_LINE_STRIP);
        for(i=0.0;i<=1.0;i+=0.02)
       {
            bz1=bezier(bez[0+n][2],bez[1+n][2],bez[2+n][2],bez[3+n][2],i+0.02)+1.0*fabs(cos(angle*3.14/180.0));
			bx1=bezier(bez[0+n][0],bez[1+n][0],bez[2+n][0],bez[3+n][0],i+0.02)+1.0*fabs(sin(angle*3.14/180.0));
		    by1=bezier(bez[0+n][1],bez[1+n][1],bez[2+n][1],bez[3+n][1],i+0.02);
			glVertex3f(bx1,by1,bz1);
		}
		glEnd();
		glLineWidth(2.0);
		glEnable(GL_LIGHTING);
		glEnable(GL_DEPTH_TEST);
		for(i=0.0;i<=1.0;i+=1.00)
       {	  bx=bezier(bez[0+n][0],bez[1+n][0],bez[2+n][0],bez[3+n][0],i);
              by=bezier(bez[0+n][1],bez[1+n][1],bez[2+n][1],bez[3+n][1],i);
              bz=bezier(bez[0+n][2],bez[1+n][2],bez[2+n][2],bez[3+n][2],i);
			  draw_cyl(bx,by-0.5,bz,bx,-10.0,bz,0.5,12);
		}
		glDisable(GL_LIGHTING);
	   	glLineWidth(2.0);

	   }
        glFlush();
		glPopMatrix();
}

void windowSpecial(int key,int x,int y)
{

	if(key==GLUT_KEY_UP)
	{
		movcord[0]+=5*cos(-1*x_r*3.14/180.0);
		movcord[2]+=5*sin(1*x_r*3.14/180.0);
	}
	if(key== GLUT_KEY_DOWN)
	{
		movcord[0]-=5*cos(-1*x_r*3.14/180.0);
		movcord[2]-=5*sin(1*x_r*3.14/180.0);
	}
	if(key==GLUT_KEY_RIGHT) x_r+=3;
	if(key==GLUT_KEY_LEFT) x_r-=3;
	display();

}


void  kb(unsigned char key, int x, int y)
{   if(key=='+') movcord[1]--;
	if(key=='-') movcord[1]++;

	if(key=='w') place_camera(camw=(++camw)%2);

    if(key=='q' || key=='Q')
        exit(0);
	if(key=='r')
	{	roll==0?(roll=1):(roll=0);
		viewer[0]=1.0;
		viewer[1]=viewer[2]=camera[0]=camera[1]=camera[2]=x_r=0.0;
	}
	display();
}

void handleMouse(int x,int y)
{
	if((x-prevx)>=0)
	x_r+=1;
	else
	x_r-=1;
	prevx=x;
}

void passiveMouse(int x, int y)
{
	prevx=x;
}

void place_camera(int action)
{

	if(camw==1)
		x_r=0;
	camw=action;
	if(camw==1)
	{	moveToBezier(bez_prog);
		viewer[0]=1.0;
		viewer[1]=viewer[2]=camera[0]=camera[1]=camera[2]=0.0;
		x_r=-45;
	}

	if(camw==0)
		viewer[1]=viewer[2]=camera[0]=camera[1]=camera[2]=0.0;
}



void handle_roller(int action)
{
	if(action==0) {
		roll==0?(roll=1):(roll=0);
		viewer[0]=1.0;
		viewer[1]=viewer[2]=camera[0]=camera[1]=camera[2]=x_r=0.0;
	}
}


void coaster()
{
        bezno=(sizeof(bez)/24)-2;

		glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
		glutInitWindowSize(1400,950);
		glutCreateWindow("Rollercoaster Ride");
		initLights();

  		glutDisplayFunc(ride3d);
	 	glutReshapeFunc(displayReshape);
	 	glutKeyboardFunc(kb);
		glutMotionFunc(handleMouse);
		glutPassiveMotionFunc(passiveMouse);
		glutIdleFunc(idle);
		glutSpecialFunc(windowSpecial);

		glutMainLoop();

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
    grassMain();
    glutMouseFunc(mymouse2);
    glEnd();
    glFlush();
}

void starter()
{

    glClear(GL_COLOR_BUFFER_BIT);


    /////////BACKGROUND/////////
    glBegin(GL_QUADS);
    //red color
    glColor3f(1.0,0.0,0.0);
    glVertex2f(0.0, 50.0);
    glVertex2f(0.0,0.0);
    //blue color
    glColor3f(0.0,0.0,1.0);
    glVertex2f(50.0,0.0);
    glVertex2f(50.0, 50.0);
    glEnd();


    glColor3f(1.0,1.0,1.0);
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


    //button
    button();

    glColor3f(1.0,1.0,1.0);
    glRasterPos3f(23,6.5,0);
    Display_on_screen("NEXT");

    // top line
    glColor3f(0.0,0.0,0.0);
    glLineWidth(5.5);
    glBegin(GL_LINES);
    //glColor3f(0.0,0.0,1.0);
    glVertex2i(20.5,42.7);
    //glColor3f(1.0,0.0,0.0);
    glVertex2i(34.5,42.7);
    glEnd();

    // bottom line
    //glColor3f(1.0,0.0,0.0);
    glLineWidth(5);
    glBegin(GL_LINES);
    //glColor3f(0.0,0.0,1.0);
    glVertex2i(14.5,39);
    //glColor3f(1.0,0.0,0.0);
    glVertex2i(28.5,39);

    glutMouseFunc(mymouse);
    glEnd();
    glFlush();

}

void mymouse2(int button,int state,int x,int y)
{
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
	    glLoadIdentity();
	    //glOrtho(-20.0, 20.0, -10.0, 10.0, -15.0, 15.0);
	    //glutTimerFunc(0, timer, 0);
	    glutCreateWindow("Rollercoaster");
	    glutDisplayFunc(coaster);
	    glutMainLoop();
	}
	//glutPostRedisplay();
}

void mymouse(int button,int state,int x,int y)
{
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
	    glLoadIdentity();
	    glOrtho(-20.0, 20.0, -10.0, 10.0, -15.0, 15.0);
	    glutTimerFunc(0, timer, 0);
	    glutDisplayFunc(display);
	}
	glutPostRedisplay();
}

int main(int argc,char ** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(1,1);
    glutInitWindowSize(1400, 950);
    glutCreateWindow("CG Project");
    glutDisplayFunc(starter);
    init();
    glutMainLoop();
    return 0;
}

void timer(int)
{
    glutPostRedisplay();
    glutTimerFunc(12000/60,timer,0);
    switch(state)
    {
    case 1:
        if(x_position<0.71 && y_position<-0.09)
           {
            x_position+=0.075;
            y_position+=0.1;
           }
        else
            state=-1;
        break;
    case -1:
        if(x_position>0.49 && y_position<0)
            {x_position-=0.075;
            y_position+=0.05;
            }
        else
            if(x_pos>-0.04)
            x_pos-=0.1;
        break;
    }
}

/*
void timer2(int)
{
    glutPostRedisplay();
    glutTimerFunc(10000/60, timer, 0);

    switch(state)
    {
    case 1:
        if(x_pos>-20)
            x_pos -= 0.15;
        else
            state = -1;
        break;

    case -1:
        if(x_pos<-0.5)
            x_pos += 0.15;
        else
            state = 1;
        break;
    }
}
*/

