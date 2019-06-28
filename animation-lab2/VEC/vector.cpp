#include "vector.h"

using namespace MyOGLProg;

Vector::Vector(void)
{
    this->x = this->y = this->z = 0.0;
}

Vector::Vector(float x, float y, float z)
{
    this->x = x; this->y = y; this->z = z;
}

Vector::Vector(Position& start, Position& end)
{
    //initialise this vector from two positions
    this->x = end.x - start.x;
    this->y = end.y - start.y;
    this->z = end.z - start.z;
}

Vector Vector::addTo(const Vector &other) const
{
    Vector result;
    result.x = other.x + this->x;
    result.y = other.y + this->y;
    result.z = other.z + this->z;
    return result;
}

Vector Vector::subtractFrom(const Vector &other) const
{
    Vector result;
    result.x = other.x - this->x;
    result.y = other.y - this->y;
    result.z = other.z - this->z;
    return result;
}

float Vector::getMagnitude(void) const
{
    float result = this->x*this->x + this->y*this->y + this->z*this->z;
    result = sqrtf(result);
    return result;
}

void Vector::setMagnitude(const float m)
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

float Vector::getDotProduct(const Vector &other) const
{
    float result = this->x*other.x+this->y*other.y+this->z*other.z;
    return result;
}

Vector Vector::getCrossProduct(const Vector &other) const
{
    Vector result;
    result.x = y * other.z - z * other.y;
    result.y = z * other.x - x * other.z;
    result.z = x * other.y - y * other.x;
    return result;
}

void Vector::normalise(void)
{
    float mag = getMagnitude();
    if (mag > 0) {
        this->x /= mag;
        this->y /= mag;
        this->z /= mag;
    }

}

