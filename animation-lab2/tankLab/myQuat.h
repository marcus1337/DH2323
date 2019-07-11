//Introductory quaternion class
#include <string>

#include "myMatrix.h"
#include "myVector.h"

namespace MyMathLibrary
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

        static MyVector rotate(float angle, MyVector axis, MyVector vecToRotate);

		float w;
		MyVector v;

        std::string getStr();
};


}