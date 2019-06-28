//Introductory quaternion class
#include <math.h>
#include "myVector.h"
#include "mymatrix.h"
#include <string>
#include <iostream>

namespace MyMathLab
{

class MyQuat
{
	public:
		MyQuat(void);
		MyQuat(float angleDeg, MyVector &axis);	//create from axis, angle
		MyQuat(MyPosition &p);	//create from position
		
		~MyQuat(void){;}

		MyQuat addTo(const MyQuat &other) const;
		MyQuat multiplyBy(const MyQuat &other) const;

		float getMagnitude(void) const;	
		void normalise(void);
		MyQuat getConjugate(void) const;	
		MyQuat getInverse(void) const;

		MyMatrix convertToRotationMatrix(void) const; 

		float w;
		MyVector v;

        std::string getStr() {
            return "w: " + std::to_string(w) + " x: " + std::to_string(v.x) + " y: " + std::to_string(v.y) + " z: " + std::to_string(v.z);
        }
};


}