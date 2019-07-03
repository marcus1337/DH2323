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
using namespace MyMathLibrary;

#include "stdlib.h"
#include "stdio.h"

#include "objloader.h"

#include <iostream>

ObjMesh* tankBody;
ObjMesh* tankTurret;
ObjMesh* tankMainGun;
ObjMesh* tankSecondaryGun;
ObjMesh* tankWheel;

void load_tank_objs(void);

float xPos = 0.0;
float zPos = -30.0;
float yRot = 0.0;

float xtmp = 0;
float ytmp = 0;
float ztmp = 0;

float rotMainTur = 0;
float rot1stTur = 0;
float rot2ndTur = 0;

int tankBodyID, mainTurretID, firstTurretID, secondTurretID, WheelID;

//prototypes for our callback functions
void draw(void);    //our drawing routine
void idle(void);    //what to do when nothing is happening
void key(unsigned char k, int x, int y);  //handle key presses
void reshape(int width, int height);      //when the window is resized
void init_drawing(void);                  //drawing intialisation

void customDraw(ObjMesh* pMesh);

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

  load_tank_objs();


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

void load_tank_objs(void)
{
  tankBody = LoadOBJ(".\\tankobjs\\tankbody.obj");
  tankTurret = LoadOBJ(".\\tankobjs\\tankturret.obj");
  tankMainGun = LoadOBJ(".\\tankobjs\\tankmaingun.obj");
  tankSecondaryGun = LoadOBJ(".\\tankobjs\\tanksecondarygun.obj");
  tankWheel = LoadOBJ(".\\tankobjs\\tankwheel.obj");
  SetTextures(tankBody->m_iMeshID, NULL, ".\\tankobjs\\texture.tga");

  tankBodyID = glGenLists(5);
  mainTurretID = tankBodyID + 1;
  firstTurretID = mainTurretID + 1;
  secondTurretID = firstTurretID + 1;
  WheelID = secondTurretID + 1;

  glNewList(tankBodyID, GL_COMPILE);
  DrawOBJ(tankBody->m_iMeshID);
  glEndList();

  glNewList(mainTurretID, GL_COMPILE);
  DrawOBJ(tankTurret->m_iMeshID);
  glEndList();

  glNewList(firstTurretID, GL_COMPILE);
  DrawOBJ(tankMainGun->m_iMeshID);
  glEndList();

  glNewList(secondTurretID, GL_COMPILE);
  DrawOBJ(tankSecondaryGun->m_iMeshID);
  glEndList();

  glNewList(WheelID, GL_COMPILE);
  DrawOBJ(tankWheel->m_iMeshID);
  glEndList();

}

void customDraw(ObjMesh* pMesh) {

    float u, v, nx, ny, nz, vx, vy, vz;
    glScalef(0.1, 0.1, 0.1);

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < pMesh->m_iNumberOfFaces; i++) {
        ObjFace *pf = &pMesh->m_aFaces[i];

        for (int j = 0; j < 3; j++) {
            int k = pf->m_aTexCoordIndicies[j];

            u = pMesh->m_aTexCoordArray[k].u;
            v = pMesh->m_aTexCoordArray[k].v;

            k = pf->m_aVertexIndices[j];
            vx = pMesh->m_aVertexArray[k].x;
            vy = pMesh->m_aVertexArray[k].y;
            vz = pMesh->m_aVertexArray[k].z;

            k = pf->m_aNormalIndices[j];
            nx = pMesh->m_aNormalArray[k].x;
            ny = pMesh->m_aNormalArray[k].y;
            nz = pMesh->m_aNormalArray[k].z;
         
            glTexCoord2f(u, v);
            glNormal3f(nx,ny,nz);
            glVertex3f(vx, vy, vz);
        }
    }
    glEnd();


}

void draw_tank(float x, float y, float z)
{
	glPushMatrix();
	glTranslatef(x,y,z);
	glScalef(0.1,0.1,0.1);

    glCallList(tankBodyID);

    glPushMatrix(); //TURRET
        glRotatef(rotMainTur, 0.0, 1.0, 0.0);
        glTranslatef(0, 12, 0);
        glCallList(mainTurretID);
        glPushMatrix();
            glTranslatef(54, -102, 12);
            glTranslatef(15, 101, 19);
            glRotatef(rot1stTur, 1.0, 0.0, 0.0);
            glTranslatef(-15, -101, -19);
            glCallList(firstTurretID);
            //std::cout << "X: " << xtmp << " Y: " << ytmp << " Z: " << ztmp << std::endl;
        glPopMatrix();  
        glPushMatrix();
            glTranslatef(-12, 17, -6);
            glTranslatef(0, 0, -10);
            glRotatef(rot2ndTur, 0.0, 1.0, 0.0);
            glTranslatef(0, 0, 10);
            glCallList(secondTurretID);
            //std::cout << "X: " << xtmp << " Y: " << ytmp << " Z: " << ztmp << std::endl;
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-24, -11, -56);
        glCallList(WheelID);
        for (int i = 0; i < 6; i++) {
            glTranslatef(0, 0, 15);
            glCallList(WheelID);
        }
        //std::cout << "X: " << xtmp << " Y: " << ytmp << " Z: " << ztmp << std::endl;
    glPopMatrix();
    glPushMatrix();
        glRotatef(180, 0.0, 1.0, 0.0);
        glTranslatef(-24, -11, 56);
        glCallList(WheelID);
        for (int i = 0; i < 6; i++) {
            glTranslatef(0, 0, -15);
            glCallList(WheelID);
        }
        //std::cout << "X: " << xtmp << " Y: " << ytmp << " Z: " << ztmp << std::endl;
    glPopMatrix();

	glPopMatrix();
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

  glTranslatef(0.0,0.0,zPos);

  glRotatef(yRot,0.0,1.0,0.0);
  glRotatef(xPos, 1.0, 0.0, 0.0);

  //draw the tank on screen at a position
  //draw_tank(0.0, 0.0, 0.0);
  customDraw(tankBody);

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
  case '1':
      xtmp++;
      break;

  case '2':
      xtmp--;
      break;

  case '3':
      ytmp++;
      break;

  case '4':
      ytmp--;
      break;

  case '5':
      ztmp++;
      break;

  case '6':
      ztmp--;
      break;

    case 'd':
	  zPos--;
	  break;
	case 'e':
	  zPos++;
	  break;
    case 't':
        xPos++;
        break;
    case 'y':
        xPos--;
        break;
	case 'r':
	  yRot++;
	  break;

    case 'j':
        rotMainTur++;
        break;
    case 'J':
        rotMainTur--;
        break;
    case 'k':
        rot1stTur++;
        break;
    case 'K':
        rot1stTur--;
        break;
    case 'l':
        rot2ndTur++;
        break;
    case 'L':
        rot2ndTur--;
        break;

    case 27: //27 is the ASCII code for the ESCAPE key
      exit(0);
      break;
  }
  glutPostRedisplay();
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

  GLfloat specular[] = {0.2,0.2,0.2,1.0};
  GLfloat ambient[] = {1.0,1.0,1.0,1.0};
  GLfloat diffuse[] = {1.0,1.0,1.0,1.0};
  GLfloat position[] = {0.0,30.0,0.0,1.0};
  glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, position);
  glEnable(GL_LIGHTING);

  GLfloat position1[] = {10.0,30.0,0.0,1.0};
  glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
  glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
  glLightfv(GL_LIGHT1, GL_POSITION, position1);
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHTING);



  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_TEXTURE_2D);
}