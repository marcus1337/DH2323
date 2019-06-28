#include "Vector.h"

using namespace MyOGLProg;

VectorA::VectorA(void)
{
    this->x = this->y = this->z = 0.0;
}

VectorA::VectorA(float x, float y, float z)
{
    this->x = x; this->y = y; this->z = z;
}

VectorA::VectorA(Position& start, Position& end)
{
    //initialise this VectorA from two positions
    this->x = end.x - start.x;
    this->y = end.y - start.y;
    this->z = end.z - start.z;
}

VectorA VectorA::addTo(const VectorA &other) const
{
    VectorA result;
    result.x = other.x + this->x;
    result.y = other.y + this->y;
    result.z = other.z + this->z;
    return result;
}

VectorA VectorA::subtractFrom(const VectorA &other) const
{
    VectorA result;
    result.x = other.x - this->x;
    result.y = other.y - this->y;
    result.z = other.z - this->z;
    return result;
}

float VectorA::getMagnitude(void) const
{
    float result = this->x*this->x + this->y*this->y + this->z*this->z;
    result = sqrtf(result);
    return result;
}

void VectorA::setMagnitude(const float m)
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

float VectorA::getDotProduct(const VectorA &other) const
{
    float result = this->x*other.x+this->y*other.y+this->z*other.z;
    return result;
}

VectorA VectorA::getCrossProduct(const VectorA &other) const
{
    VectorA result;
    result.x = y * other.z - z * other.y;
    result.y = z * other.x - x * other.z;
    result.z = x * other.y - y * other.x;
    return result;
}

void VectorA::normalise(void)
{
    float mag = getMagnitude();
    if (mag > 0) {
        this->x /= mag;
        this->y /= mag;
        this->z /= mag;
    }

}

