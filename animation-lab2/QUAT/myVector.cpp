#include "myVector.h"

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
    //initialise this MyVector from two MyPositions
    this->x = end.x - start.x;
    this->y = end.y - start.y;
    this->z = end.z - start.z;
}

MyVector MyVector::addTo(const MyVector &other) const
{
    MyVector result;
    result.x = other.x + this->x;
    result.y = other.y + this->y;
    result.z = other.z + this->z;
    return result;
}

MyVector MyVector::subtractFrom(const MyVector &other) const
{
    MyVector result;
    result.x = other.x - this->x;
    result.y = other.y - this->y;
    result.z = other.z - this->z;
    return result;
}

float MyVector::getMagnitude(void) const
{
    float result = this->x*this->x + this->y*this->y + this->z*this->z;
    result = sqrtf(result);
    return result;
}

void MyVector::setMagnitude(const float m)
{
    float mag = getMagnitude();
    this->x *= m;
    this->y *= m;
    this->z *= m;
    if (mag > 0) {
        this->x /= mag;
        this->y /= mag;
        this->z /= mag;
    }
}

float MyVector::getDotProduct(const MyVector &other) const
{
    float result = this->x*other.x + this->y*other.y + this->z*other.z;
    return result;
}

MyVector MyVector::getCrossProduct(const MyVector &other) const
{
    MyVector result;
    result.x = y * other.z - z * other.y;
    result.y = z * other.x - x * other.z;
    result.z = x * other.y - y * other.x;
    return result;
}

void MyVector::normalise(void)
{
    float mag = getMagnitude();
    if (mag > 0) {
        this->x /= mag;
        this->y /= mag;
        this->z /= mag;
    }

}

float MyVector::getAngle(MyVector avec, MyVector bvec) {
    float ang = avec.getDotProduct(bvec);
    float mags = avec.getMagnitude()*bvec.getMagnitude();
    if (mags > 0)
        ang /= mags;
    ang = acos(ang);
    ang = RAD2DEG(ang);
    return ang;
}