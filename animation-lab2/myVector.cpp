#include "MyVector.h"

using namespace MyMathLab;

MyVector::MyVector(void)
{
	this->x = this->y = this->z = 0.0;
}

MyVector::MyVector(float x, float y, float z)
{
	this->x = x; this->y = y; this->z = z;
}

MyVector::MyVector(MyPosition& start, MyPosition& end)
{
	this->x = end.x - start.x;
	this->y = end.y - start.y;
	this->z = end.z - start.z;
}

MyVector MyVector::addTo(const MyVector &other) const
{
	MyVector result;
	//your code here
	return result;
}

MyVector MyVector::subtractFrom(const MyVector &other) const
{
	MyVector result;
	//your code here
	return result;
}
		
float MyVector::getMagnitude(void) const
{
	float result;
	//your code here
	return result;
}

void MyVector::uniformScale(const float m)
{
	//your code here
}

void MyVector::normalise(void)
{
	//your code here
}

void MyVector::setMagnitude(const float m)
{
	if (this->getMagnitude() > 0.0)
	{
		this->normalise();
		this->uniformScale(m);
	}
}
	
float MyVector::getDotProduct(const MyVector &other) const
{
	float result;
	//your code here
	return result;
}

MyVector MyVector::getCrossProduct(const MyVector &other) const
{
	MyVector result;
	//your code here
	return result;
}
