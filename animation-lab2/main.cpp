#define WIN32_LEAN_AND_MEAN

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(linker, "/subsystem:console")

#include "windows.h"

#include <gl/gl.h>            // standard OpenGL include
#include <gl/glu.h>           // OpenGL utilties
#include <glut.h>             // OpenGL utilties

#include "myvector.h"
#include "mymatrix.h"
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

//draw callback function - this is called by glut whenever the 
//window needs to be redrawn
void draw(void)
{
  //clear the current window
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  //make changes to the modelview matrix
  glMatrixMode(GL_MODELVIEW);
  //initialise the modelview matrix to the identity matrix
  glLoadIdentity();
  
  //***DO ALL YOUR DRAWING HERE****//






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