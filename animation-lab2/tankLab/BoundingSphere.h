

#include "ObjLoader.h"
#include <string>

class BoundingSphere {

public:
    float cx, cy, cz, radius; //center coordinates and radius of sphere

    BoundingSphere(): cx(0),cy(0),cz(0),radius(0), lx(0),ly(0),lz(0),transx(0),transy(0),transz(0){}

    void init(ObjMesh* pMesh);

    void printStuff();

    float lx, ly, lz;//bugtest
    float transx, transy, transz;

    bool collision = false;
    void setTrans(float, float, float);
    void addTrans(float, float, float);
    std::string getCoordStr();

    bool checkCollision(float x, float y, float z);
    
    void draw();

};