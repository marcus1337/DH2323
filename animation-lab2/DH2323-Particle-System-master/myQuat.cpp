#include "MyQuat.h"

#define PI 3.14159265

MyQuat::MyQuat(void) {
}
MyQuat::MyQuat(float angleDeg, MyVector &axis) {
	float angleRad = angleDeg * PI / 180.0;
	this->w = cos(angleRad / 2.0);
	this->v = axis;
	this->v.normalise();
	this->v = this->v.multiplyScalar(sin(angleRad / 2.0));
}
MyQuat::MyQuat(MyPosition &p) {
	this->w = 0.0;
	this->v.x = p.x;
	this->v.y = p.y;
	this->v.z = p.z;
	this->v.normalise();
}
MyQuat::MyQuat(const MyQuat * q) {
	this->w = q->w;
	this->v = MyVector(q->v);
}

MyQuat MyQuat::addTo(const MyQuat &other) const {
	MyQuat sum;
	sum.w = w + other.w;
	sum.v = v.addTo(other.v);
	return sum;
}

MyQuat MyQuat::multiplyBy(const MyQuat &other) const {
	MyQuat prod;
	prod.w = this->w * other.w - this->v.getDotProduct(other.v);
	prod.v = this->v.getCrossProduct(other.v).addTo(other.v.multiplyScalar(this->w).addTo(this->v.multiplyScalar(other.w)));
	return prod;
}

float MyQuat::getMagnitude(void) const {
	return sqrt(w*w + pow(v.getMagnitude(), 2));
}

void MyQuat::normalise(void) {
	float magnitude = getMagnitude();
	w /= magnitude;
	v = v.multiplyScalar(1.0 / magnitude);
}

MyQuat MyQuat::getConjugate(void) const {
	MyQuat conj;
	conj.w = this->w;
	conj.v = v.multiplyScalar(-1.0);
	return conj;
}

MyQuat MyQuat::getInverse(void) const {
	float denom = pow(getMagnitude(), 2);
	MyQuat inverse;
	inverse.w = w / denom;
	inverse.v = v.multiplyScalar(-1.0 / denom);
	return inverse;
}

MyMatrix MyQuat::convertToRotationMatrix(void) const {
	MyQuat normalized(this);
	normalized.normalise();
	float coeffs[16] = {
		pow(normalized.w, 2) + pow(normalized.v.x, 2) - pow(normalized.v.y, 2) - pow(normalized.v.z, 2),
		2.0 * normalized.v.x * normalized.v.y - 2.0 * normalized.w * normalized.v.z,
		2.0 * normalized.v.x * normalized.v.z + 2.0 * normalized.w * normalized.v.y,
		0.0,
		2.0 * normalized.v.x * normalized.v.y + 2.0 * normalized.w * normalized.v.z,
		pow(normalized.w, 2) - pow(normalized.v.x, 2) + pow(normalized.v.y, 2) - pow(normalized.v.z, 2),
		2.0 * normalized.v.y * normalized.v.z - 2.0 * normalized.w * normalized.v.x,
		0.0,
		2.0 * normalized.v.x * normalized.v.z - 2.0 * normalized.w * normalized.v.y,
		2.0 * normalized.v.y * normalized.v.z + 2.0 * normalized.w * normalized.v.x,
		pow(normalized.w, 2) - pow(normalized.v.x, 2) - pow(normalized.v.y, 2) + pow(normalized.v.z, 2),
		0.0,
		0.0, 0.0, 0.0, 1.0
	};
	MyMatrix matrix(coeffs);
	return matrix;
}