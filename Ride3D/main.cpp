
#include<windows.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<stdio.h>
#include<math.h>


void display();
void draw_wagon();
void draw_seat();
void place_camera(int);
void set_material(int material);

//* LEFT and RIGHT arrow: Look Around 360 degrees"
//* UP and DOWN arrow: Move forward and backward"
//* + : Move up"
//* - : Move down"

const int SKY_FRONT=0,SKY_RIGHT=1,SKY_LEFT=2,SKY_BACK=3,SKY_UP=4,SKY_DOWN=5, ROLLER_BODY=6, ROLLER_FRAME=7;
int ni=0, prevx=0, rcam=1,bezno,camw=1, roll=0, background=0;
GLint skybox[6], grass,help=0,x_r=0, y_r=0, z_r=0;
GLfloat viewer[3] = {1.0f, 0.0f, 0.0f},camera[3] = {0.0f, 0.0, 0.0};
GLdouble curr=0, prev=0,angle=0.0,c_angle=90.0,lx=50.0,ly=50.0,lz=50.0,bez_prog=0.0,roller_speed=0.0050,gy=0,movcord[3]={-150,-10,200};

double bez[][3]={
	{30,10,-200},{30,10,-110},	{30,10,10},	{30,10,50},	{30,70,100}, {60,90,140}, {80,80,100},
	{70,80,70}, {0,50,80}, {-20,30,80},{-45, 25, 60}, {-70,20,50}, {-40,10,30}, {-30,30,10},
	{-90,30,20}, {-120,130,60}, {-115,160,75}, {-110, 200, 130}, {-100, 160, 200}, {-90,130,250},
	{-50,150,260}, {-25,150,260}, {-5,140,260}, {25,160,260}, {40,130,230}, {55,110,210},

	{280, 80, -210},{250, 60, -250},{230, 30, -280}, {200, 55, -290}, {170, 35, -270}, {150, 22, -250},
	{100, 20, -230},{80, 35, -200},{60, 30, -170}, {35, 20, -150}, {30,10,-115}, {30,10,-105},
	{30,10,-105}, {30,10,-105}
};


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


void Draw_Skybox(float x, float y, float z, float width, float height, float length){


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

void display(){

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
}



void handle_roller(int action)
{
	if(action==0) {
		roll==0?(roll=1):(roll=0);
		viewer[0]=1.0;
		viewer[1]=viewer[2]=camera[0]=camera[1]=camera[2]=x_r=0.0;
	}
}

int main(int argc, char** argv)
{
		bezno=(sizeof(bez)/24)-2;
		glutInit(&argc,argv);
		glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);
		glutInitWindowSize(1400,950);
		glutCreateWindow("Rollercoaster Ride");
		initLights();

  		glutDisplayFunc(display);
	 	glutReshapeFunc(displayReshape);
	 	glutKeyboardFunc(kb);
		glutMotionFunc(handleMouse);
		glutPassiveMotionFunc(passiveMouse);
		glutIdleFunc(idle);
		glutSpecialFunc(windowSpecial);

		glutMainLoop();
		return 0;
}

