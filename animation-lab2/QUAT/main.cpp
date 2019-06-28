#define WIN32_LEAN_AND_MEAN

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(linker, "/subsystem:console")

#include "windows.h"

#include <gl/gl.h>            // standard OpenGL include
#include <gl/glu.h>           // OpenGL utilties
#include <glut.h>             // OpenGL utilties

#include "myQuat.h"

#include <iostream>

using namespace MyMathLab;

#include "stdlib.h"

//prototypes for our callback functions
void draw(void);    //our drawing routine
void idle(void);    //what to do when nothing is happening
void key(unsigned char k, int x, int y);  //handle key presses
void reshape(int width, int height);      //when the window is resized
void init_drawing(void);                  //drawing intialisation

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
  glutDisplayFunc(draw);

  //request a window size of 600 x 600
  glutInitWindowSize(600,600);
  glutReshapeWindow(600,600);

  //go into the main loop
  //this loop won't terminate until the user exits the 
  //application
  glutMainLoop();

  return 0;
}

using namespace MyMathLab;
void DrawVector(MyPosition& startPos, MyVector& v1, float red = 1.0f, float green = 1.0f, float blue = 1.0f, bool isLine = false)
{
    //draw the vector v1 starting from position startPos
    //this function will only work as long as the z coordinate for both positions is zero
    float length = sqrt((v1.x * v1.x) + (v1.y * v1.y) + (v1.z * v1.z));
    MyVector v;
    if (length > 0.0) { v.x = v1.x / length; v.y = v1.y / length; v.z = v1.z / length; }
    else return;
    float d = (v.x * 0.0) + (v.y * 1.0) + (v.z * 0.0);
    float a = RAD2DEG(acos(d));
    if (v.x > 0.0) a = -a;

    glPushMatrix();
    glTranslatef(startPos.x, startPos.y, startPos.z);
    glRotatef(a, 0.0, 0.0, 1.0);
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

void markPoint(MyPosition& startPos) {
    glPointSize(2);
    glBegin(GL_POINTS);
    glTranslatef(0.0, 0.0, 0.0);
    glVertex3f(startPos.x, startPos.y, startPos.z);
    glEnd();
}

void b2(MyVector given = MyVector(4.0, 2.0, 0)) {
    MyVector other(-2.0, 3.0, 0);
    MyVector res = given.addTo(other);
    MyPosition pos(res.x, res.y, res.z);
    markPoint(pos);
}

float getAngle(MyVector avec, MyVector bvec) {
    float ang = avec.getDotProduct(bvec);
    float mags = avec.getMagnitude()*bvec.getMagnitude();
    if (mags > 0)
        ang /= mags;
    ang = acos(ang);
    ang = RAD2DEG(ang);
    return ang;
}

void draw_square() {
    glBegin(GL_POLYGON);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(-1.0, 1.0, 0.0);
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(-1, -1, 0);
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(1.0, -1.0, 0.0);
        glColor3f(1.0, 1.0, 1.0);
        glVertex3f(1.0, 1.0, 0.0);
    glEnd();
}

//draw callback function - this is called by glut whenever the 
//window needs to be redrawn
float sqRotZ = 0.0f;
float ang2 = 0.0f;
void draw(void)
{
  //clear the current window
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //make changes to the modelview matrix
  glMatrixMode(GL_MODELVIEW);
  //initialise the modelview matrix to the identity matrix
  
/*  glLoadIdentity();
  glTranslatef(-1.5f, 0.0f, -6.0f);
  glBegin(GL_TRIANGLES);
      glVertex3f(0.0f, 0.0f, 0.0f);
      glVertex3f(1.0f, 0.0f, 0.0f);
      glVertex3f(0.0f, 1.0f, 0.0f);
  glEnd();
    */

  glLoadIdentity();
  MyMatrix mat2;
  mat2.myMatrix[0] = cosf(ang2);
  mat2.myMatrix[1] = -sinf(ang2);
  mat2.myMatrix[4] = sinf(ang2);
  mat2.myMatrix[5] = cosf(ang2);
  mat2.multiplyGLMatrix();


  glRotatef(45, 0.0f, 0.f, 1.0f);
  glTranslatef(0.0f, 0.0f, -6.0f);
 /* glBegin(GL_TRIANGLES);
  glVertex3f(0.0f, 0.0f, 0.0f);
  glVertex3f(1.0f, 0.0f, 0.0f);
  glVertex3f(0.0f, 1.0f, 0.0f);
  glEnd(); */

  glLoadIdentity();

  

  MyMatrix mat;
  //glTranslatef(0.0, 0.0, -20.0);
  glMatrixMode(GL_MODELVIEW);
  mat.getGLModelviewMatrix();
  mat.myMatrix[14] -= 25.0f;

  glMatrixMode(GL_MODELVIEW);
  mat.setGLMatrix();

  /*glPushMatrix();
      glTranslatef(0.0, 2.0, 0.0);
      mat2.multiplyGLMatrix();
      glRotatef(sqRotZ, 0, 0, 1.0f);
      glTranslatef(0.0, -2.0, 0.0);
      glTranslatef(1.0, 1.0, -5.0);
      draw_square();
  glPopMatrix();

  glPushMatrix();
      glTranslatef(-1.0, 1.0, -5.0);
      glRotatef(sqRotZ, 0, 0, 1.0f);
      mat2.multiplyGLMatrix();
      draw_square();
  glPopMatrix(); */


  MyPosition p1(0, 0, 0);
  MyVector vec(0,-10,0);
  MyVector axvec(10, 0, 0);
  float angtmp = 45.0f;

  MyQuat q1(angtmp, axvec);
  MyQuat qvec(MyPosition(vec.x, vec.y, vec.z));
  MyQuat q1Conj = q1.getConjugate();

  MyQuat qrA = qvec.multiplyBy(q1Conj);
  MyQuat qr = q1.multiplyBy(qrA);

  MyVector rotatedVec(qr.v.x, qr.v.y, qr.v.z);
  DrawVector(p1,vec);
  DrawVector(p1, axvec, vec.x,vec.y,vec.z);
  rotatedVec.setMagnitude(vec.getMagnitude());
  DrawVector(p1, rotatedVec);
  float nyang = MyVector::getAngle(vec, rotatedVec);
  std::cout << "TEST " << nyang << std::endl;
  std::cout << "Vals: " << rotatedVec.getStr() << std::endl;

  /*MyPosition p1(0, 0, 0);
  MyVector vec(1, 0, 0);
  MyVector axvec(0, 0, 1);
  float angtmp = 90.0f;

  MyQuat q1(angtmp, axvec);
  MyQuat qvec(MyPosition(1, 0, 0));
  MyQuat q1Conj = q1.getConjugate();

  std::cout << "q1: " << q1.getStr() << std::endl;

  MyQuat qrA = qvec.multiplyBy(q1Conj);
  MyQuat qr = q1.multiplyBy(qrA);

  MyVector rotatedVec(qr.v.x, qr.v.y, qr.v.z);
  DrawVector(p1,vec);
 // DrawVector(p1, axvec, 1, 1, 0);
  DrawVector(p1, rotatedVec);
  float nyang = MyVector::getAngle(vec, rotatedVec);
  std::cout << "TEST " << nyang << std::endl;
  std::cout << "Vals: " << rotatedVec.getStr() << std::endl;*/

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

    case 'r':
        sqRotZ += 5.0f;
        glutPostRedisplay();
        break;
    case 't':
        ang2 += DEG2RAD(5.0f);
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
  draw();
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
  glDepthFunc(GL_LEQUAL);
  glEnable(GL_DEPTH_TEST);
}