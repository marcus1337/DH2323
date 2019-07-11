#ifndef  VECTOR_H  
#define  VECTOR_H

#include <math.h>
#include <string>

namespace MyMathLibrary
{
    const double M_PI = 3.14159265358979323846;
    const double M_HALF_PI = 1.57079632679489661923;
    const double RAD = (M_PI / 180.0);
    const double PIOVER2 = (3.14159265358979323846 / 2);
    #define DEG2RAD(x) ((x)*M_PI/180.0)
    #define RAD2DEG(x) ((x)*180.0/M_PI)

    struct MyPosition
    {
        float x;
        float y;
        float z;
        MyPosition(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
        MyPosition() {}
    };

    class MyVector
    {
    public:
        MyVector(void);
        MyVector(float x, float y, float z);
        MyVector(MyPosition& start, MyPosition& end);
        ~MyVector(void) { ; }

        MyVector addTo(const MyVector &other) const;
        MyVector subtractFrom(const MyVector &other) const;

        float getMagnitude(void) const;
        void setMagnitude(const float m);
        MyVector getCrossProduct(const MyVector &other) const;

        static float getAngle(MyVector avec, MyVector bvec);
        static float pointDist(MyPosition a, MyPosition b);

        static void sortSwap(MyVector& avec, MyVector& bvec);
        static MyVector closestPointToLine(MyVector p1, MyVector p2, MyVector Q);


        float getDotProduct(const MyVector &other) const;
        void normalise(void);

        std::string getStr();
        MyPosition toPos();
        bool operator==(const MyVector& otherVec);

        MyVector scalarMulti(float scalarTmp);

        float x;
        float y;
        float z;

        MyVector operator + (const MyVector &other);
        MyVector operator - (const MyVector &other);
        MyVector operator * (const MyVector &other);
        MyVector operator / (const MyVector &other);

        MyVector operator * (const float scalar);
        static MyVector multi(const float scalar, const MyVector &other);

        MyVector& operator = (const MyVector &other);
        MyVector& operator += (const MyVector &other);
        MyVector& operator -= (const MyVector &other);

        MyVector operator + (void) const;
        MyVector operator - (void) const;
    };


}

#endif