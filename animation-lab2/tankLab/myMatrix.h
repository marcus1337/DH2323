//Introductory matrix class
#ifndef  MATRIX_H  
#define  MATRIX_H

#include <math.h>
#include "windows.h"
#include <gl/gl.h>            // standard OpenGL include
#include <gl/glu.h>           // OpenGL utilties
#include <glut.h>             // OpenGL utilties


namespace MyMathLibrary
{

class MyMatrix
{
	public:
		MyMatrix(void);
		~MyMatrix(void){;}

		void loadIdentity(void);

		void getGLModelviewMatrix(void);
		void getGLProjectionMatrix(void);

		void multiplyGLMatrix(void);
		void setGLMatrix(void);

		void getGLMatrix(GLenum pname);
		GLfloat myMatrix[16];

private:
};

}

#endif