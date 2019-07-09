#define WIN32_LEAN_AND_MEAN

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(linker, "/subsystem:console")

#include "windows.h"

#include <gl/gl.h>            // standard OpenGL include
#include <gl/glu.h>           // OpenGL utilties
#include <glut.h>             // OpenGL utilties

//#include "myvector.h"
//#include "mymatrix.h"
#include "myQuat.h"
using namespace MyMathLibrary;

#include "stdlib.h"
#include "stdio.h"

#include "objloader.h"

#include <iostream>

#include "BoundingSphere.h"

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

void sphereTests();

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
  sphereTests();

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

/*using namespace MyMathLab;

void DrawVector(MyPosition& startPos, MyVector& v1, float red = 1.0f, float green = 1.0f, float blue = 1.0f, bool isLine = false)
{
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
}*/

BoundingSphere bSphereBody;
BoundingSphere bSphereTurret;
BoundingSphere bSphereGunMain, bSphereGunSecond, bSphereWheel[14];

void sphereTests() {
    bSphereBody.init(tankBody);
    bSphereTurret.init(tankTurret);
    bSphereGunMain.init(tankMainGun);
    bSphereGunSecond.init(tankSecondaryGun);

    for(int i = 0; i < 14; i++)
        bSphereWheel[i].init(tankWheel);
    //std::cout << "X: " << xtmp << " Y: " << ytmp << " Z: " << ztmp << " ::" << bSphereBody.collision << "::" << std::endl;
}

using namespace MyMathLab;
using namespace MyMathLibrary;

float offX = 15;
float offY = 101;
float offZ = 19;

void testCollision(float x, float y, float z) { //xyz should in a real program probably be added LAST, but we assume these to be 0,0,0
    bSphereBody.setTrans(x, y, z);
    bSphereTurret.setTrans(x, y, z);

    bSphereTurret.addTrans(0, 12, 0);

    bSphereGunMain.setTrans(x, y, z);
    bSphereGunMain.addTrans(54+ bSphereGunMain.cx, 0, 13+ bSphereGunMain.cz);
    MyVector gunmainVec(bSphereGunMain.transx, 0, bSphereGunMain.transz);
    gunmainVec = MyQuat::rotate(rotMainTur, MyVector(0, 1, 0), gunmainVec);
    bSphereGunMain.setTrans(gunmainVec.x, 12, gunmainVec.z);
    gunmainVec.y = 0;
    MyVector lodRotVec = MyQuat::rotate(90, MyVector(0, 1, 0), MyVector(gunmainVec.x, gunmainVec.y, gunmainVec.z));
    lodRotVec = MyQuat::rotate(rot1stTur, lodRotVec, gunmainVec);
    lodRotVec.y += 12;
    bSphereGunMain.setTrans(lodRotVec.x, lodRotVec.y, lodRotVec.z);

    bSphereGunSecond.setTrans(0, 0, 0);
    //MyVector rotVec = MyQuat::rotate(rot2ndTur, MyVector(0, 1, 0), MyVector(0, 0, -20));
   // std::cout << "WAT " << rotVec.getStr() << std::endl;
   // bSphereGunSecond.addTrans(-rotVec.x, 0, -rotVec.z);
    // glTranslatef(-12, 17, -6);


    bSphereGunSecond.addTrans(0, 0, 25);
    MyVector gun2ndVec(bSphereGunSecond.transx, 0, bSphereGunSecond.transz);
    gun2ndVec = MyQuat::rotate(rot2ndTur, MyVector(0, 1, 0), gun2ndVec);
    bSphereGunSecond.setTrans(gun2ndVec.x-11, 25, gun2ndVec.z-16);

    MyVector gunmainVec2(bSphereGunSecond.transx, 0, bSphereGunSecond.transz);
    gunmainVec2 = MyQuat::rotate(rotMainTur, MyVector(0, 1, 0), gunmainVec2);
    bSphereGunSecond.setTrans(gunmainVec2.x, 25, gunmainVec2.z);
   
    //std::cout << "TMP " << xtmp << " _ " << ztmp << std::endl;
    // glRotatef(rot2ndTur, 0.0, 1.0, 0.0);


    for (int i = 0; i < 14; i++)
        bSphereWheel[i].setTrans(x, y, z);

    for (int i = 0; i < 7; i++) {
        bSphereWheel[i].addTrans(-24, -11, -56);
        bSphereWheel[i].addTrans(0, 0, 15 * (i));
    }
    for (int i = 7; i < 14; i++) {
        bSphereWheel[i].addTrans(40, -11, 35);
        bSphereWheel[i].addTrans(0, 0, -15 * (i-7));
    }

  //  std::cout << "X: " << xtmp << " Y: " << ytmp << " Z: " << ztmp << " ::" << bSphereBody.collision << "::" << std::endl;

    if (bSphereBody.checkCollision(xtmp, ytmp, ztmp)) {
      //  std::cout << "Outer Bound Hit! " << std::endl;

        if(bSphereTurret.checkCollision(xtmp, ytmp, ztmp)) {
       //    std::cout << "TURRET " << bSphereTurret.getCoordStr() << std::endl;
        }

        if(bSphereGunMain.checkCollision(xtmp, ytmp, ztmp)) {
     //      std::cout << "GUN_1 " << bSphereGunMain.getCoordStr() << std::endl;
        }
        if(bSphereGunSecond.checkCollision(xtmp, ytmp, ztmp)) {
       //     std::cout << "GUN_2 " << bSphereGunSecond.getCoordStr() << std::endl;
        }

        for (int i = 0; i < 14; i++)
            if(bSphereWheel[i].checkCollision(xtmp, ytmp, ztmp)) {
           //     std::cout << "WHEEL_" << i << std::endl;
            }
    }

   // bSphereBody.draw();
   // bSphereTurret.draw();
    //bSphereGunMain.draw();
    bSphereGunSecond.draw();
    //for (int i = 0; i < 14; i++)
     //   bSphereWheel[i].draw();
}

void drawProjectile() {
    glColor4f(0, 1, 0, 0);
    glPushMatrix();
    glScalef(0.1, 0.1, 0.1);
    glTranslatef(xtmp, ytmp, ztmp);
    glutSolidSphere(2, 25, 25);
    glPopMatrix();
    glColor4f(1, 1, 1, 0);
}

void draw_tank(float x, float y, float z)
{
	glPushMatrix();
	glTranslatef(x,y,z);
	glScalef(0.1,0.1,0.1);
    glCallList(tankBodyID);
    //bSphereBody.draw();

    glPushMatrix(); //TURRET
        glRotatef(rotMainTur, 0.0, 1.0, 0.0);
        glTranslatef(0, 12, 0);
        glCallList(mainTurretID);
       // bSphereTurret.draw();

        glPushMatrix();
            glTranslatef(54, -102, 12);
            glTranslatef(15, 101, 19);
            glRotatef(rot1stTur, 1.0, 0.0, 0.0);
            glTranslatef(-15, -101, -19);
            glCallList(firstTurretID);
          //  bSphereGunMain.draw();
            //std::cout << "X: " << xtmp << " Y: " << ytmp << " Z: " << ztmp << std::endl;
        glPopMatrix();  
        glPushMatrix();
            glTranslatef(-12, 17, -6);
            glTranslatef(0, 0, -10);
            glRotatef(rot2ndTur, 0.0, 1.0, 0.0);
            glTranslatef(0, 0, 10);
            glCallList(secondTurretID);
          //  bSphereGunSecond.draw();
            //std::cout << "X: " << xtmp << " Y: " << ytmp << " Z: " << ztmp << std::endl;
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-24, -11, -56);
        glCallList(WheelID);
        //bSphereWheel[0].draw();
        for (int i = 0; i < 6; i++) {
            glTranslatef(0, 0, 15);
            glCallList(WheelID);
         //   bSphereWheel[i].draw();
        }
        //std::cout << "X: " << xtmp << " Y: " << ytmp << " Z: " << ztmp << std::endl;
    glPopMatrix();
    glPushMatrix();
        glRotatef(180, 0.0, 1.0, 0.0);
        glTranslatef(-24, -11, 56);
        glCallList(WheelID);
       // bSphereWheel[0].draw();
        for (int i = 0; i < 6; i++) {
            glTranslatef(0, 0, -15);
            glCallList(WheelID);
          //  bSphereWheel[i].draw();
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

  testCollision(0, 0, 0);
  drawProjectile();
  draw_tank(0.0, 0.0, 0.0);
  //customDraw(tankMainGun);

  glFlush();
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
    case 'R':
        yRot--;
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

    case 'm':
        offZ++;
        break;
    case 'M':
        offZ--;
        break;
    case 'n':
        offY++;
        break;
    case 'N':
        offY--;
        break;
    case 'b':
        offX++;
        break;
    case 'B':
        offX--;
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
  gluPerspective(45.0, (float) width / (float) height, 1.0, 500.0);
  //redraw the view during resizing
  draw();
}

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

    GLfloat specular[] = { 0.2,0.2,0.2,1.0 };
    GLfloat ambient[] = { 1.0,1.0,1.0,1.0 };
    GLfloat diffuse[] = { 1.0,1.0,1.0,1.0 };
    GLfloat position[] = { 0.0,30.0,0.0,1.0 };
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glEnable(GL_LIGHTING);

    GLfloat position1[] = { 10.0,30.0,0.0,1.0 };
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, position1);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHTING);

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);
}