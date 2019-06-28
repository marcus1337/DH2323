#include <math.h>
#include <string>

namespace MyMathLab
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

        float getDotProduct(const MyVector &other) const;

        void normalise(void);
        std::string getStr() {
            return "(" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + ")";
        }

        MyPosition toPos() {
            return MyPosition(x, y, z);
        }

        float x;
        float y;
        float z;
    };


}