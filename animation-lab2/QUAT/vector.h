#include <math.h>
#include <string>

namespace MyOGLProg
{

	const double M_PI = 3.14159265358979323846;
	const double M_HALF_PI = 1.57079632679489661923;

	const double RAD = (M_PI/180.0);
	const double PIOVER2 = (3.14159265358979323846 / 2);
	#define DEG2RAD(x) ((x)*M_PI/180.0)
	#define RAD2DEG(x) ((x)*180.0/M_PI)


struct Position
{
	float x;
	float y;
	float z;
    Position(float _x, float _y, float _z): x(_x), y(_y), z(_z){}
    Position(){}
};

class VectorA
{
	public:
        VectorA(void);
        VectorA(float x, float y, float z);
        VectorA(Position& start, Position& end);
		~VectorA(void){;}

		VectorA addTo(const VectorA &other) const;
		VectorA subtractFrom(const VectorA &other) const;
		
		float getMagnitude(void) const;
		void setMagnitude(const float m);
		VectorA getCrossProduct(const VectorA &other) const;

		float getDotProduct(const VectorA &other) const;
		
		void normalise(void);		
        std::string getStr() {
            return "(" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + ")";
        }

        Position toPos() {
            return Position(x, y, z);
        }

		float x;
		float y;
		float z;
};


}