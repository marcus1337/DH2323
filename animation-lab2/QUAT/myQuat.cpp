#include "MyQuat.h"

using namespace MyMathLab;

MyQuat::MyQuat() {
    w = 0;
}

MyQuat::MyQuat(MyPosition &p) {
    w = 0;
    v.x = p.x;
    v.y = p.y;
    v.z = p.z;
    v.normalise();
}

MyQuat::MyQuat(float angleDeg, MyVector &axis) {
    float angleDegDiv = angleDeg / 2;
    angleDegDiv = DEG2RAD(angleDegDiv);
    w = cosf(angleDegDiv);  
    v = axis;
    v.normalise();
    v.x *= sinf(angleDegDiv);
    v.y *= sinf(angleDegDiv);
    v.z *= sinf(angleDegDiv);
}

MyQuat MyQuat::multiplyBy(const MyQuat &other) const {
    MyQuat tmp = *this;
    float wtmp = tmp.w * other.w;
    wtmp -= v.getDotProduct(other.v);
    tmp.v = tmp.v.getCrossProduct(other.v);
    MyVector w1v2(other.v.x*w, other.v.y*w, other.v.z*w);
    MyVector w2v1(v.x*other.w, v.y*other.w, v.z*other.w);
    tmp.v = tmp.v.addTo(w1v2);
    tmp.v = tmp.v.addTo(w2v1);
    return tmp;
}

MyQuat MyQuat::addTo(const MyQuat &other) const {
    MyQuat tmp = *this;
    tmp.w += other.w;
    tmp.v = tmp.v.addTo(other.v);
    return tmp;
}

float MyQuat::getMagnitude(void) const {
    return sqrt(w*w + v.x*v.x + v.y*v.y + v.z*v.z);
}

void MyQuat::normalise(void) {
    float mag = getMagnitude();
    if (mag == 0)
        return;
    w /= mag;
    v.x /= mag;
    v.y /= mag;
    v.z /= mag;
}

MyQuat MyQuat::getConjugate(void) const {
    MyQuat tmp = *this;
    tmp.v.x *= -1;
    tmp.v.y *= -1;
    tmp.v.z *= -1;
    return tmp;
}

MyQuat MyQuat::getInverse(void) const {
    MyQuat tmp = *this; //assuming unit quaternion, (see http://www.utdallas.edu/~sxb027100/dock/quaternion.html)
    float len = w * w + v.x*v.x + v.y*v.y + v.z*v.z;
    tmp = tmp.getConjugate();
    if (len > 0) {
        tmp.v.x /= len;
        tmp.v.y /= len;
        tmp.v.z /= len;
    }
    return tmp;
}

MyMatrix MyQuat::convertToRotationMatrix(void) const { //assume unit quaternion
    MyMatrix tmp;
    float z = v.z;
    float x = v.x;
    float y = v.y;
    tmp.myMatrix[0] = 1 - 2 * y*y - 2 * z*z;
    tmp.myMatrix[1] = 2 * x*y - 2 * z*w;
    tmp.myMatrix[2] = 2 * x*z + 2 * y*w;

    tmp.myMatrix[4] = 2 * x*y + 2 * z*w;
    tmp.myMatrix[5] = 1 - 2 * x*x - 2 * z*z;
    tmp.myMatrix[6] = 2 * y*z - 2 * x*w;

    tmp.myMatrix[8] = 2 * x*z - 2 * y*w;
    tmp.myMatrix[9] = 2 * y*z + 2 * x*w;
    tmp.myMatrix[10] = 1 - 2 * x*x - 2 * y*y;

    return tmp;
}