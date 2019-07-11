#include "windows.h"
#include <gl/gl.h>            // standard OpenGL include
#include <gl/glu.h>           // OpenGL utilties
#include <glut.h>             // OpenGL utilties

#include "BoundingSphere.h"
#include <iostream>

#include "myVector.h"

using namespace MyMathLibrary;
using namespace std;

void BoundingSphere::printStuff() {
    cout << "X: " << cx << " Y: " << cy << " Z: " << cz << endl;
}

void BoundingSphere::init(ObjMesh* pMesh) {
    int numVerts = pMesh->m_iNumberOfVertices;
    if (numVerts == 0)
        return;

    cx = cy = cz = 0;
    radius = 0;

    for (int i = 0; i < numVerts; i++) { //average coordinate
        cx += pMesh->m_aVertexArray[i].x;
        cy += pMesh->m_aVertexArray[i].y;
        cz += pMesh->m_aVertexArray[i].z;
    }
    cx /= (float) numVerts;
    cy /= (float) numVerts;
    cz /= (float) numVerts;

   // printStuff();

    for (int i = 0; i < numVerts; i++) {
        float tmpx = pMesh->m_aVertexArray[i].x;
        float tmpy = pMesh->m_aVertexArray[i].y;
        float tmpz = pMesh->m_aVertexArray[i].z;

        float tmpDist = MyVector::pointDist(MyPosition(cx, cy, cz), MyPosition(tmpx, tmpy, tmpz));
        if (tmpDist > radius) {
            radius = tmpDist;
         //   cout << "X: " << cx << " Y: " << cy << " Z: " << cz << " RAD: " << radius << endl;
          //  cout << "X: " << tmpx << " Y: " << tmpy << " Z: " << tmpz << " RAD: " << radius << endl;
            lx = tmpx;
            ly = tmpy;
            lz = tmpz;
        }
    }

  //  std::cout << "TEST " << radius << std::endl;

}



bool BoundingSphere::checkCollision(float x, float y, float z) {
    float tmpDist = MyVector::pointDist(MyPosition(x, y, z), MyPosition(transx, transy, transz));
    tmpDist <= radius ? collision = true : collision = false;
    return collision;
}

void BoundingSphere::setTrans(float x, float y, float z) {
    transx = x;
    transy = y;
    transz = z;
}

void BoundingSphere::addTrans(float x, float y, float z) {
    transx += x;
    transy += y;
    transz += z;
}

void BoundingSphere::draw() {
//    if (!collision)
 //       return;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1, 1, 0.5, 0.5);
    if(collision)
        glColor4f(1, 0, 0, 0.5);
    glPushMatrix();
    glScalef(0.1, 0.1, 0.1);
   // glTranslatef(cx, cy, cz);
    glTranslatef(transx, transy, transz); //can be uncommented depending on how this class is used
    
    glutSolidSphere(radius, 55, 55);
    glPopMatrix();
    glColor4f(1, 1, 1, 0);
    glDisable(GL_BLEND);
}

std::string BoundingSphere::getCoordStr() {
    return "X: " + std::to_string(cx) + " Y: " + std::to_string(cy) + " Z: " + std::to_string(cz) + " RAD: " + std::to_string(radius) +  "\n";
}