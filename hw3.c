/* 
	Alexis McBeain
	hw3 - 3D Scene
	
	I used the examples given in Canvas for some functions and as guides for my program 

 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

//view angles
int th = 36;
int ph = -4; 
double zh=0;


float a = 1.0;
float b = 1.0;
float c = 0.0;


//cosine and sine in degrees 
#define Cos(x) (cos((x)*3.1415927/180))
#define Sin(x) (sin((x)*3.1415927/180))

#define LEN 8192  //  Maximum length of text string
void Print(const char* format , ...)
{
   char    buf[LEN];
   char*   ch=buf;
   va_list args;
   va_start(args,format);
   vsnprintf(buf,LEN,format,args);
   va_end(args);
   
   while (*ch)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}



static void Buildings(double x, double y, double z, double dx, double dy, double dz, double th){
	
  
  glPushMatrix();
  
  // Translations
  glTranslated(x, y, z);
  glRotated(th, 0, 1, 0);
  glScaled(dx, dy, dz);

  //buildings
  glBegin(GL_POLYGON);
	//Front
	glColor3f(0.8,0.8,0.8);
	glVertex3f(1,.1, 1);
	glVertex3f(-1,3, 1);
	glVertex3f(-1,.1, 1);
	glVertex3f(1,3, 1);
	//Back
	glColor3f(0.8,0.8,0.8);
	glVertex3f(1,3,-1);
	glVertex3f(1,.1,-1);
	glVertex3f(-1,3,-1);
	glVertex3f(-1,.1,-1);
	//Right
	glColor3f(0.8,0.8,0.8);
	glVertex3f(1,.1,1);
	glVertex3f(1,.1,-1);
	glVertex3f(1,3,1);
	glVertex3f(1,3,-1);
	//Left
	glColor3f(0.8,0.8,0.8);
	glVertex3f(-1,.1,1);
	glVertex3f(-1,.1,-1);
	glVertex3f(-1,3,1);
	glVertex3f(-1,3,-1);
	//Top
	glColor3f(0.8,0.8,0.8);
	glVertex3f(-1,3,1);
	glVertex3f(1,3,1);
	glVertex3f(1,3,-1);
	glVertex3f(-1,3,-1);
	//Bottom
	glColor3f(0.8,0.8,0.8);
	glVertex3f(-1,1,-1);
	glVertex3f(1,.1,-1);
	glVertex3f(1,.1,1);
	glVertex3f(-1,.1,1);
  glEnd();
  
	//triangles are hard :(

  //window
	glBegin(GL_QUADS);
		glColor4f(a, b, c, 0.0f);
		//Front
		glVertex3f(.1,.5,-1);
		glVertex3f(-.3,.5,-1);
		glVertex3f(-.3,1,-1);
		glVertex3f(.1,1,-1);
		//Top
		glVertex3f(.1,1,-1);
		glVertex3f(.1,1,-1);
		glVertex3f(-.1,1,-1);
		glVertex3f(-.1,1,-1);
		//Right
		glVertex3f(.1,1,-1);
		glVertex3f(.1,.5,-1);
		glVertex3f(.1,.5,-1);
		glVertex3f(.1,1,-1);
		//Left
		glVertex3f(-.3,1,-1);
		glVertex3f(-.3,.5,-1);
		glVertex3f(-.3,.5,-1);
		glVertex3f(-.3,1,-1);
	glEnd();
  
   //door
  glBegin(GL_QUADS);
	glColor3f(0.1f, 0.0f, 0.0f);
	//Front
	glVertex3f(.8,0,-1);
	glVertex3f(.3,0,-1);
	glVertex3f(.3,1,-1);
	glVertex3f(.8,1,-1);
	//Top
	glVertex3f(.8,1,-1);
	glVertex3f(.8,1,-1);
	glVertex3f(.3,1,-1);
	glVertex3f(.3,1,-1);
	//Right
	glVertex3f(.8,1,-1);
	glVertex3f(.8,0,-1);
	glVertex3f(.8,0,-1);
	glVertex3f(.8,1,-1);
	//Left
	glVertex3f(.3,1,-1);
	glVertex3f(.3,0,-1);
	glVertex3f(.3,0,-1);
	glVertex3f(.3,1,-1);
  glEnd();

   

  glPopMatrix();
}

void display()
{
   
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   glEnable(GL_DEPTH_TEST);
   glLoadIdentity();
   glOrtho(-3, 3, -3, 3, -10, 10);
   
   glRotatef(ph,1,0,0);
   glRotatef(th,0,1,0);
   
   //build city thing
    Buildings(5,0, 1, .25,.25,.25, -50);
	Buildings(3.5,0,1, .5,.5,.5, -25);
	Buildings(1,0,1 , 1,1,1, 0); 
	Buildings(-3,0,1 , 1.5,1.5,1.5, 25);
	Buildings(-7,0,5 , 2,2,2, 50);
   
  
   
   //ground
	glColor3f(0.0f, 0.1f, 0.0f); //DARK GREEN
	glBegin(GL_QUADS);
		glVertex3f(-50,0,-50);
		glVertex3f(-50,0,50);
		glVertex3f(50,0,50);
		glVertex3f(50,0,-50);
   glEnd();

   glColor3f(1,1,1);
   glWindowPos2i(5,5);
   Print("View Angle=%d,%d",th,ph);
   
   glWindowPos2i(5,25);
   Print("W = Window Lights on");
   
   glWindowPos2i(5, 45);
   Print("S = Window Lights off");
   

   glFlush();
   glutSwapBuffers();
}



void movement(int key,int x,int y)
{
  
   if (key == GLUT_KEY_RIGHT)
      th += 5;

   else if (key == GLUT_KEY_LEFT)
      th -= 5;
   
   else if (key == GLUT_KEY_UP)
      ph += 5;
  
   else if (key == GLUT_KEY_DOWN)
      ph -= 5;
   
   th %= 360;
   ph %= 360;
   
   glutPostRedisplay();
}


void key(unsigned char ch,int x,int y)
{
   //  Exit on ESC
   if (ch == 27)
      exit(0);
   //  Reset w spacebar
   else if (ch == 32){
      th = 36;
      ph = -4;
	  a = 1.0;
	  b = 1.0;
	  c = 0.0;
   }
   //turn off lights
   else if (ch == 's'){
	   a = 0.0;
	   b = 0.0;
	   c = 0.0;
   }
   //turn on lights 
   else if(ch == 'w') {
	   a = 1.0;
	   b = 1.0;
	   c = 0.0;
   }
   
   glutPostRedisplay();
}


void reshape(int width,int height)
{
   const double dim=2.5;
   //  Ratio of the width to the height of the window
   double w2h = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, width,height);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-w2h*dim,+w2h*dim, -dim,+dim, -dim,+dim);
   glMatrixMode(GL_MODELVIEW);
   
   glLoadIdentity();
}


void idle()
{
   double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
   zh = fmod(90*t,360);
   glutPostRedisplay();
}


int main(int argc,char* argv[])
{
   glutInit(&argc,argv);
   glutInitWindowSize(800,800);
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutCreateWindow("Alexis McBeain - Assignment 3");
   glutIdleFunc(idle);
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(movement);
   glutKeyboardFunc(key);
   glutMainLoop();
   
   return 0;
}