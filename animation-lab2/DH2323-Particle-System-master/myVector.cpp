#include "MyVector.h"
#include <iostream>

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
	//add this vector to other and return the result
	MyVector result;
	result.x = this->x + other.x;
	result.y = this->y + other.y;
	result.z = this->z + other.z;
	return result;
}

MyVector MyVector::subtractFrom(const MyVector &other) const
{
	//subtract this vector from other and return the result
	MyVector result;
	result.x = other.x - this->x;
	result.y = other.y - this->y;
	result.z = other.z - this->z;
	return result;
}
		
float MyVector::getMagnitude(void) const
{
	//get the length of the vector
	float result;
	result = sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
	return result;
}

void MyVector::uniformScale(const float m)
{
	//set the length of the vector
	this->x *= m;
	this->y *= m;
	this->z *= m;
}

void MyVector::normalise(void)
{
	setMagnitude(1.0);
}

void MyVector::setMagnitude(const float m)
{
	//set the length of the vector
	float curLength = getMagnitude();
	this->x *= m / curLength;
	this->y *= m / curLength;
	this->z *= m / curLength;
}
	
float MyVector::getDotProduct(const MyVector &other) const
{
	//return the dot product between this vector and other
	float result = 0;
	result += this->x * other.x;
	result += this->y * other.y;
	result += this->z * other.z;
	return result;
}

MyVector MyVector::getCrossProduct(const MyVector &other) const
{
	//return the cross product between this vector and other
	MyVector result;
	result.x = this->y * other.z - this->z * other.y;
	result.x = this->z * other.x - this->x * other.z;
	result.x = this->x * other.y - this->y * other.x;
	return result;
}

MyVector MyVector::multiplyScalar(const float scalar) const
{
	MyVector result;
	result.x = this->x * scalar;
	result.y = this->y * scalar;
	result.z = this->z * scalar;
	return result;
}

MyVector MyVector::operator + ( const MyVector &other )
{
    MyVector vResult(0.0f, 0.0f, 0.0f);

    vResult.x = x + other.x;
    vResult.y = y + other.y;
    vResult.z = z + other.z;

    return vResult;
}

MyVector MyVector::operator + ( void ) const
{
    return *this;
}

MyVector MyVector::operator - ( const MyVector &other )
{
    MyVector vResult(0.0f, 0.0f, 0.0f);

    vResult.x = x - other.x;
    vResult.y = y - other.y;
    vResult.z = z - other.z;

    return vResult;
}

MyVector MyVector::operator - ( void ) const
{
    MyVector vResult(-x, -y, -z);

    return vResult;
}

MyVector MyVector::operator * ( const MyVector &other )
{
    MyVector vResult(0.0f, 0.0f, 0.0f);

    vResult.x = x * other.x;
    vResult.y = y * other.y;
    vResult.z = z * other.z;

    return vResult;
}

MyVector MyVector::operator * ( const float scalar )
{
    MyVector vResult(0.0f, 0.0f, 0.0f);

    vResult.x = x * scalar;
    vResult.y = y * scalar;
    vResult.z = z * scalar;

    return vResult;
}

MyVector operator * ( const float scalar, const MyVector &other )
{
    MyVector vResult(0.0f, 0.0f, 0.0f);

    vResult.x = other.x * scalar;
    vResult.y = other.y * scalar;
    vResult.z = other.z * scalar;

    return vResult;
}

MyVector MyVector::operator / ( const MyVector &other )
{
    MyVector vResult(0.0f, 0.0f, 0.0f);

    vResult.x = x / other.x;
    vResult.y = y / other.y;
    vResult.z = z / other.z;

    return vResult;
}

MyVector& MyVector::operator = ( const MyVector &other )
{
	x = other.x;
	y = other.y;
	z = other.z;

    return *this;
}

MyVector& MyVector::operator += ( const MyVector &other )
{
    x += other.x;
    y += other.y;
    z += other.z;

    return *this;
}

MyVector& MyVector::operator -= ( const MyVector &other )
{
    x -= other.x;
    y -= other.y;
    z -= other.z;

    return *this;
}

void MyVector::printOut() const {
	std::cout << "v: (" << x << ", " << y << ", " << z << ")" << std::endl;
}