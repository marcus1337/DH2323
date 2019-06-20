#define WIN32_LEAN_AND_MEAN

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(linker, "/subsystem:console")

#include "windows.h"
#include "vector.h"
#include "glut.h"             // OpenGL utilties

#include <iostream>

using namespace MyOGLProg;

#include "stdlib.h"

//prototypes for our callback functions
void DisplayScene(void);    //our drawing routine
void idle(void);    //what to do when nothing is happening
void key(unsigned char k, int x, int y);  //handle key presses
void reshape(int width, int height);      //when the window is resized
void init_drawing(void);                  //drawing intialisation

void DrawVector(Position& startPos, Vector& v1, float red = 1.0f, float green = 1.0f, float blue = 1.0f, bool isLine = false)
{
	//draw the vector v1 starting from position startPos
	//this function will only work as long as the z coordinate for both positions is zero
	float length = sqrt((v1.x * v1.x) + (v1.y * v1.y) + (v1.z * v1.z));
	Vector v;
	if (length > 0.0){ v.x = v1.x/length; v.y = v1.y/length; v.z = v1.z/length; }
	else return;
	float d = (v.x * 0.0) + (v.y * 1.0) + (v.z * 0.0);
	float a = RAD2DEG(acos(d));
	if (v.x > 0.0) a = -a;

	glPushMatrix();
	glTranslatef(startPos.x, startPos.y, startPos.z);
	glRotatef(a,0.0,0.0,1.0);
	float space = 0.25;

	glBegin(GL_LINES);
        glColor3f(red, green, blue);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, length, 0.0);

        if (!isLine) {
            glVertex3f(0.0, length, 0.0);
            glVertex3f(-space, length - (space * 1.5), 0.0);
            glVertex3f(0.0, length, 0.0);
            glVertex3f(space, length - (space * 1.5), 0.0);
        }

	glEnd();
	glPopMatrix();
}

void markPoint(Position& startPos) {
    glPointSize(2);
    glBegin(GL_POINTS);
    glVertex3f(startPos.x, startPos.y, startPos.z);
    glEnd();
}

//our main routine
int main(int argc, char *argv[])
{
  //Initialise Glut and create a window
  glutInit(&argc, argv);
  //sets up our display mode
  //here we've selected an RGBA display with depth testing 
  //and double buffering enabled
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
  //create a window and pass through the windows title
  glutCreateWindow("Basic Glut Application");

  //run our own drawing initialisation routine
  init_drawing();

  //tell glut the names of our callback functions point to our 
  //functions that we defined at the start of this file
  glutReshapeFunc(reshape);
  glutKeyboardFunc(key);
  glutIdleFunc(idle);
  glutDisplayFunc(DisplayScene);

  //request a window size of 600 x 600
  glutInitWindowSize(600,600);
  glutReshapeWindow(600,600);

  //go into the main loop
  //this loop won't terminate until the user exits the 
  //application
  glutMainLoop();

  return 0;
}


void b1() {
    Vector res(4.0, 2.0, 0);
    Position pos(1.0, 2.0, 0);
    DrawVector(pos, res);
}

void b2(Vector given = Vector(4.0, 2.0, 0)) {
    Vector other(-2.0, 3.0, 0);
    Vector res = given.addTo(other);
    Position pos(res.x, res.y, res.z);
    markPoint(pos);
}

float getAngle(Vector avec, Vector bvec) {
    float ang = avec.getDotProduct(bvec);
    float mags = avec.getMagnitude()*bvec.getMagnitude();
    if (mags > 0)
        ang /= mags;
    ang = acos(ang);
    ang = RAD2DEG(ang);
    return ang;
}

void b3() {
    Vector avec(0, 1.0, 0);
    Vector bvec(0.707, 0.707, 0);
    Position pos(0.0, 0.0, 0);
    DrawVector(pos, avec);
    DrawVector(pos, bvec);
    float ang = avec.getDotProduct(bvec);
    float mags = avec.getMagnitude()*bvec.getMagnitude();
    if(mags > 0)
        ang /= mags;
    ang = acos(ang);
    ang = RAD2DEG(ang);
    std::cout << "TEST " << ang << std::endl;
}

void b4() {
    Vector avec(4.0, 4.0, 0);
    Vector bvec(-2.0, 3.0, 0);
    Position pos(0.0, 0.0, 0);
    DrawVector(pos, avec,1.0f,1.0f,0);
    DrawVector(pos, bvec, 1.0f, 1.0f, 0);
    float dotprod = avec.getDotProduct(bvec);
    bool sameDir = dotprod >= 0;
    std::cout << "SAME DIR: " << sameDir << std::endl;
}

void b5() {
    Position point(5, 4, 0);
    Vector ap(5, 4, 0);
    Vector ab(3, 9, 0);
    Position abOld(3, 9, 0);
    DrawVector(Position(0, 0, 0), ab, 0, 1, 1);
    float apab = ap.getDotProduct(ab);
    float abdot = ab.getDotProduct(ab);
    float res = apab / abdot;
    ab.x *= res;
    ab.y *= res;

    DrawVector(Position(0, 0, 0), ap, 1, 1, 0);
    DrawVector(Position(0,0,0), ab, 1,1,0);

   // DrawVector(point, ab, 1, 0.5, 0.2,true);

    /*glBegin(GL_LINES);
    glColor3f(1, 0.5, 0.2);
    glVertex3f(ab.x, ab.y, ab.z);
    glVertex3f(abOld.x, abOld.y, abOld.z);
    glEnd();*/

    glLineStipple(1, 0xAAAA);
    glEnable(GL_LINE_STIPPLE);
    glBegin(GL_LINES);
    glColor3f(1, 0.5, 0.2);
    glVertex3f(ab.x, ab.y, ab.z);
    glVertex3f(ap.x, ap.y, ap.z);
    glEnd();

}

void b6() {
    Position p1(1,8,0);
    Position p2(3, 0, 0);

    Vector vec1(5,4,0);
    Vector vec2(-6, 0, 0);

    DrawVector(p1, vec1);
    DrawVector(p2, vec2);
    float ang = getAngle(vec1, vec2);
    std::cout << "ANGLE: " << ang << std::endl;
}

Position targ(8, 3, 0);

void b7() {
    using namespace std;
    Position pv(-2.5, 10, 0);
    Vector vec1(5, -2, 0);

    markPoint(targ);
    glLineStipple(1, 0xAAAA);
    glEnable(GL_LINE_STIPPLE);
    glBegin(GL_LINES);
    glColor3f(1, 0.5, 0.2);
    glVertex3f(pv.x, pv.y, pv.z);
    glVertex3f(vec1.x, vec1.y, vec1.z);
    glEnd();


    Vector b(5, -2, 0);
    Vector a(-2.5, 10, 0);
    Vector c(targ.x, targ.y, targ.z);
    Vector T = a.subtractFrom(b);

    float t = (a.subtractFrom(c)).getDotProduct(a.subtractFrom(b));
    float magab = a.subtractFrom(b).getMagnitude();
    magab *= magab;
    t /= magab;
    if (t >= 1.0f) {
        cout << b.getStr() << endl;
        DrawVector(b.toPos(), b.subtractFrom(c), 1, 1, 0, true);
    }
    else if (t <= 0) {
        cout << a.getStr() << endl;
        DrawVector(a.toPos(), a.subtractFrom(c), 1, 1, 0, true);
    }
    else {
        Vector tmp(a.x + b.x*t, a.y + b.y * t, a.z + b.z*t);
        cout << tmp.getStr() << endl;
        Vector res(a.x + T.x*t, a.y + T.y*t, 0);
        cout << "RES " << res.getStr() << " _ " << T.getStr() << endl;
        DrawVector(res.toPos(), res.subtractFrom(c), 1, 1, 0, true);
    }

    std::cout << "T: " << t << " TARGET: " << c.getStr() <<  std::endl;

}

/*****************************************************************************
 DisplayScene()

 The work of the application is done here. This is called by glut whenever the 
//window needs to be redrawn
*****************************************************************************/

void DisplayScene(void)
{
  //clear the current window
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //make changes to the modelview matrix
  glMatrixMode(GL_MODELVIEW);
  //initialise the modelview matrix to the identity matrix
  glLoadIdentity();

  glTranslatef(-6.0,-6.0,-20.0);
  
  /*glColor3f(1.0,0.0,0.0);
  glBegin(GL_POINTS);
	glVertex3f(0.0,0.0,-5.0);
  glEnd();*/

  GLfloat yellow[4] = { 1.0f, 1.0f, 0.2f, 1.0f };
  GLfloat blue[4] = { 0.2f, 0.2f, 1.0f, 1.0f };
  GLfloat green[4] = { 0.2f, 1.0f, 0.2f, 1.0f };
  Position origin;
  origin.x = origin.y = origin.z = 0.0;

  //define a position and a vector
  Position p1;
  p1.x = 1.0; p1.y = 1.0; p1.z = 0.0;
  Vector v1(4.0, 4.0, 0.0);

  //draw the vector at position
  glDisable(GL_LINE_STIPPLE);
  glLineWidth(1.0);
  glColor3f(1.0,1.0,0.0);
  DrawVector(p1,v1);

  //draw a red horizontal line, one unit long
  glLineWidth(3.0);
  glColor3f(1.0,0.0,0.0);
  glPushMatrix();
	  glTranslatef(0.0, 0.0, 0.0);
	  glBegin(GL_LINES);
		glVertex2f(0.0,0.0);
		glVertex2f(1.0,0.0);
	  glEnd();
  glPopMatrix();

  //draw a green vertical line, one unit high
  glLineWidth(3.0);
  glColor3f(0.0,0.0,1.0);
  glPushMatrix();
	  glBegin(GL_LINES);
		glVertex2f(0.0,0.0);
		glVertex2f(0.0,1.0);
	  glEnd();
  glPopMatrix();

  //draw a white point at the origin
  glPointSize(2.0);
  glColor3f(1.0,1.0,1.0);
  glPushMatrix();
	  glTranslatef(0.0, 0.0, 0.0);
	  glBegin(GL_POINTS);
		glVertex2f(0.0,0.0);
	  glEnd();
  glPopMatrix();

  //b1();
  //b2();
  //b3();
  //b4();
  //b5();
  //b6();
  b7();

  //flush what we've drawn to the buffer
  glFlush();
  //swap the back buffer with the front buffer
  glutSwapBuffers();
}

//idle callback function - this is called when there is nothing 
//else to do
void idle(void)
{
  //this is a good place to do animation
  //since there are no animations in this test, we can leave 
  //idle() empty
}

//key callback function - called whenever the user presses a 
//key
void key(unsigned char k, int x, int y)
{
  switch(k)
  {
    case 27: //27 is the ASCII code for the ESCAPE key
     exit(0);
      break;

    case 'a':
        targ.x -= 0.5;
        std::cout << "a" << std::endl;
        glutPostRedisplay();
        break;

    case 's':
        targ.x += 0.5;
        std::cout << "s" << std::endl;
        glutPostRedisplay();
        break;

    case 'z':
        targ.y += 0.5;
        std::cout << "z" << std::endl;
        glutPostRedisplay();
        break;

    case 'x':
        targ.y -= 0.5;
        std::cout << "x" << std::endl;
        glutPostRedisplay();
        break;
  }
}

//reshape callback function - called when the window size changed
void reshape(int width, int height)
{
  //set the viewport to be the same width and height as the window
  glViewport(0,0,width, height);
  //make changes to the projection matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  //set up our projection type
  //we'll be using a perspective projection, with a 90 degree 
  //field of view
  gluPerspective(45.0, (float) width / (float) height, 1.0, 100.0);
  //redraw the view during resizing
  DisplayScene();
}

//set up OpenGL before we do any drawing
//this function is only called once at the start of the program
void init_drawing(void)
{
  //blend colours across the surface of the polygons
  //another mode to try is GL_FLAT which is flat shading
  glShadeModel(GL_SMOOTH);
  //turn lighting off
  glDisable(GL_LIGHTING);
  //enable OpenGL hidden surface removal
  //glDepthFunc(GL_LEQUAL);
  //glEnable(GL_DEPTH_TEST);

  //glClearColor(1.0,0.0,0.0,0.0);
}
