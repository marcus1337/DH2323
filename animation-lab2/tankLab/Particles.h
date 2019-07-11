#include "particleSystem.h"

class Particles {
public:

    Particles();

    void init();
    void draw(float x, float y, float z);
    void onIdle();

    int g_nActiveSystem = 2;
    CParticleSystem *g_pParticleSystems[7];
    float  g_fElpasedTime;
    double g_dCurTime;
    double g_dLastTime;

    bool activated1;
};