#define GL_GLEXT_PROTOTYPES

#include "stdlib.h"
#include "stdio.h"
#include "windows.h"
#include <gl/gl.h>            // standard OpenGL include
#include <gl/glu.h>           // OpenGL utilties
#include "glut.h"             // OpenGL utilties
#include "Particles.h"
#include "myVector.h"

#include <iostream>

using namespace MyMathLibrary;

Particles::Particles() : activated1(false) {}

void Particles::init() {
    g_dCurTime = timeGetTime();
    g_fElpasedTime = (float)((g_dCurTime - g_dLastTime) * 0.001);
    g_dLastTime = g_dCurTime;

    g_pParticleSystems[0] = new CParticleSystem();

    //g_pParticleSystems[0]->SetTexture( "..\\particle.bmp" );
    g_pParticleSystems[0]->SetTexture("particle.bmp");
    g_pParticleSystems[0]->SetMaxParticles(100);
    g_pParticleSystems[0]->SetNumToRelease(100);
    g_pParticleSystems[0]->SetReleaseInterval(0.05f);
    g_pParticleSystems[0]->SetLifeCycle(0.5f);
    g_pParticleSystems[0]->SetSize(30.0f);
    g_pParticleSystems[0]->SetColor(MyVector(1.0f, 0.0f, 0.0f));
    g_pParticleSystems[0]->SetPosition(MyVector(0.0f, 5.0f, 0.0f));
    g_pParticleSystems[0]->SetVelocity(MyVector(0.0f, 0.0f, 0.0f));
    g_pParticleSystems[0]->SetGravity(MyVector(0.0f, 0.0f, 0.0f));
    g_pParticleSystems[0]->SetWind(MyVector(0.0f, 0.0f, 0.0f));
    g_pParticleSystems[0]->SetVelocityVar(10.0f);

    g_pParticleSystems[0]->Init();

    //
    // Wind blown fountain
    //

    g_pParticleSystems[1] = new CParticleSystem();

    //    g_pParticleSystems[1]->SetTexture( "..\\particle.bmp" );
    g_pParticleSystems[1]->SetTexture("particle.bmp");
    g_pParticleSystems[1]->SetMaxParticles(500);
    g_pParticleSystems[1]->SetNumToRelease(5);
    g_pParticleSystems[1]->SetReleaseInterval(0.05f);
    g_pParticleSystems[1]->SetLifeCycle(4.0f);
    g_pParticleSystems[1]->SetSize(30.0f);
    g_pParticleSystems[1]->SetColor(MyVector(1.0f, 1.0f, 1.0f));
    g_pParticleSystems[1]->SetPosition(MyVector(0.0f, 0.0f, 0.0f));
    g_pParticleSystems[1]->SetVelocity(MyVector(0.0f, 5.0f, 0.0f));
    g_pParticleSystems[1]->SetGravity(MyVector(0.0f, 0.0f, 0.0f));
    g_pParticleSystems[1]->SetWind(MyVector(2.0f, 0.0f, 0.0f));
    g_pParticleSystems[1]->SetVelocityVar(1.5f);

    g_pParticleSystems[1]->Init();

    //
    // Omni-directiional emission expanding into space with no air resistence
    //

    g_pParticleSystems[2] = new CParticleSystem();

    g_pParticleSystems[2]->SetTexture("particle.bmp");
    g_pParticleSystems[2]->SetMaxParticles(2048);
    g_pParticleSystems[2]->SetNumToRelease(10);
    g_pParticleSystems[2]->SetReleaseInterval(0.05f);
    g_pParticleSystems[2]->SetLifeCycle(5.0f);
    g_pParticleSystems[2]->SetSize(30.0f);
    g_pParticleSystems[2]->SetColor(MyVector(1.0f, 1.0f, 1.0f));
    g_pParticleSystems[2]->SetPosition(MyVector(0.0f, 0.0f, 0.0f));
    g_pParticleSystems[2]->SetVelocity(MyVector(0.0f, 0.0f, 0.0f));
    g_pParticleSystems[2]->SetGravity(MyVector(0.0f, 0.0f, 0.0f));

    g_pParticleSystems[2]->SetWind(MyVector(0.0f, 0.0f, 0.0f));
    g_pParticleSystems[2]->SetAirResistence(false);

    g_pParticleSystems[2]->SetVelocityVar(2.0f);

    g_pParticleSystems[2]->Init();

    //
    // Fountain particles behave like paint spots when striking a plane as 
    // the wind blowing them towards us
    //

    g_pParticleSystems[3] = new CParticleSystem();

    g_pParticleSystems[3]->SetTexture("particle.bmp");
    g_pParticleSystems[3]->SetMaxParticles(100);
    g_pParticleSystems[3]->SetNumToRelease(10);
    g_pParticleSystems[3]->SetReleaseInterval(0.05f);
    g_pParticleSystems[3]->SetLifeCycle(3.0f);
    g_pParticleSystems[3]->SetSize(30.0f);
    g_pParticleSystems[3]->SetColor(MyVector(1.0f, 1.0f, 1.0f));
    g_pParticleSystems[3]->SetPosition(MyVector(0.0f, 0.0f, 0.0f));
    g_pParticleSystems[3]->SetVelocity(MyVector(0.0f, 5.0f, 0.0f));
    g_pParticleSystems[3]->SetGravity(MyVector(0.0f, 0.0f, 0.0f));
    g_pParticleSystems[3]->SetWind(MyVector(0.0f, 0.0f, -20.0f));
    g_pParticleSystems[3]->SetVelocityVar(2.5f);

    g_pParticleSystems[3]->SetCollisionPlane(MyVector(0.0f, 0.0f, 1.0f),
        MyVector(0.0f, 0.0f, -5.0f),
        1.0f, CR_STICK);

    g_pParticleSystems[3]->Init();

    //
    // Fountain using a single collision plane acting as a floor
    //

    g_pParticleSystems[4] = new CParticleSystem();

    g_pParticleSystems[4]->SetTexture("particle.bmp");
    g_pParticleSystems[4]->SetMaxParticles(200);
    g_pParticleSystems[4]->SetNumToRelease(10);
    g_pParticleSystems[4]->SetReleaseInterval(0.05f);
    g_pParticleSystems[4]->SetLifeCycle(5.0f);
    g_pParticleSystems[4]->SetSize(30.0f);
    g_pParticleSystems[4]->SetColor(MyVector(1.0f, 1.0f, 1.0f));
    g_pParticleSystems[4]->SetPosition(MyVector(0.0f, 0.0f, 0.0f));
    g_pParticleSystems[4]->SetVelocity(MyVector(0.0f, 0.0f, 0.0f));
    g_pParticleSystems[4]->SetGravity(MyVector(0.0f, -9.8f, 0.0f));
    g_pParticleSystems[4]->SetWind(MyVector(0.0f, 0.0f, 0.0f));
    g_pParticleSystems[4]->SetVelocityVar(20.0f);

    g_pParticleSystems[4]->SetCollisionPlane(MyVector(0.0f, 1.0f, 0.0f),
        MyVector(0.0f, 0.0f, 0.0f));

    g_pParticleSystems[4]->Init();

    //
    // Fountain boxed-in by 6 collision planes
    //

    g_pParticleSystems[5] = new CParticleSystem();

    g_pParticleSystems[5]->SetTexture("particle.bmp");
    g_pParticleSystems[5]->SetMaxParticles(100);
    g_pParticleSystems[5]->SetNumToRelease(5);
    g_pParticleSystems[5]->SetReleaseInterval(0.05f);
    g_pParticleSystems[5]->SetLifeCycle(5.0f);
    g_pParticleSystems[5]->SetSize(30.0f);
    g_pParticleSystems[5]->SetColor(MyVector(1.0f, 1.0f, 1.0f));
    g_pParticleSystems[5]->SetPosition(MyVector(0.0f, 0.0f, 0.0f));
    g_pParticleSystems[5]->SetVelocity(MyVector(0.0f, 0.0f, 0.0f));
    g_pParticleSystems[5]->SetGravity(MyVector(0.0f, -9.8f, 0.0f));
    g_pParticleSystems[5]->SetWind(MyVector(0.0f, 0.0f, 0.0f));
    g_pParticleSystems[5]->SetVelocityVar(20.0f);

    // Create a series of planes to collide with
    g_pParticleSystems[5]->SetCollisionPlane(MyVector(0.0f, 1.0f, 0.0f),
        MyVector(0.0f, 0.0f, 0.0f)); // Floor

    g_pParticleSystems[5]->SetCollisionPlane(MyVector(1.0f, 0.0f, 0.0f),
        MyVector(-3.0f, 0.0f, 0.0f)); // Left Wall

    g_pParticleSystems[5]->SetCollisionPlane(MyVector(-1.0f, 0.0f, 0.0f),
        MyVector(3.0f, 0.0f, 0.0f)); // Right Wall

    g_pParticleSystems[5]->SetCollisionPlane(MyVector(0.0f, 0.0f, 1.0f),
        MyVector(0.0f, 0.0f, -3.0f)); // Front Wall

    g_pParticleSystems[5]->SetCollisionPlane(MyVector(0.0f, 0.0f, -1.0f),
        MyVector(0.0f, 0.0f, 3.0f)); // Back Wall

    g_pParticleSystems[5]->SetCollisionPlane(MyVector(0.0f, -1.0f, 0.0f),
        MyVector(0.0f, 5.0f, 0.0f)); // Ceiling

    g_pParticleSystems[5]->Init();


    /////////////////////////////////////////////////////////////////////////////////////

    g_pParticleSystems[6] = new CParticleSystem();
    g_pParticleSystems[6]->SetTexture("particle.bmp");
    g_pParticleSystems[6]->SetMaxParticles(408);
    g_pParticleSystems[6]->SetNumToRelease(10);
    g_pParticleSystems[6]->SetReleaseInterval(0.02f);
    g_pParticleSystems[6]->SetLifeCycle(5.0f);
    g_pParticleSystems[6]->SetSize(50.0f);
    g_pParticleSystems[6]->SetColor(MyVector(0.0f, 1.0f, 0.0f));
    g_pParticleSystems[6]->SetPosition(MyVector(0.5f, 0.5f, 0.0f));
    g_pParticleSystems[6]->SetVelocity(MyVector(5.0f, 0.0f, 0.0f));
    g_pParticleSystems[6]->SetGravity(MyVector(0.0f, 0.0f, 0.0f));
    g_pParticleSystems[6]->SetWind(MyVector(0.0f, 5.0f, 0.0f));
    g_pParticleSystems[6]->SetAirResistence(false);
    g_pParticleSystems[6]->SetVelocityVar(2.0f);

    g_pParticleSystems[6]->SetCollisionPlane(MyVector(-0.3f, 1.0f, 0.0f),
        MyVector(-0.5f, 0.0f, 0.0f)); // Floor

    g_pParticleSystems[6]->SetCollisionPlane(MyVector(0.0f, -1.0f, 0.0f),
        MyVector(0.0f, 3.0f, 0.0f)); // Ceiling

    g_pParticleSystems[6]->SetCollisionPlane(MyVector(1.0f, 0.0f, 0.0f),
        MyVector(-3.0f, 0.0f, 0.0f)); // Left Wall

    g_pParticleSystems[6]->SetCollisionPlane(MyVector(-1.0f, 0.0f, 0.0f),
        MyVector(3.0f, 0.0f, 0.0f)); // Right Wall

    g_pParticleSystems[6]->Init();
}

void Particles::onIdle() {
   // if (!activated1)
    //    return;

    g_dCurTime = timeGetTime();
    g_fElpasedTime = (float)((g_dCurTime - g_dLastTime) * 0.001);
    g_dLastTime = g_dCurTime;
    g_pParticleSystems[g_nActiveSystem]->Update((float)g_fElpasedTime);
}

void Particles::draw(float x, float y, float z) {
    if (!activated1)
        return;
   
    glPushMatrix();
    glScalef(0.1, 0.1, 0.1);
    glTranslatef(x, y, z); //move the camera back to view the scene

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_FALSE);

    bool doTestRender = false;

    if (doTestRender)
    {
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_BLEND);
        g_pParticleSystems[g_nActiveSystem]->RenderSimple();
        glEnable(GL_TEXTURE_2D);
    }
    else
    {
        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_FALSE);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);

       

        glBindTexture(GL_TEXTURE_2D, g_pParticleSystems[g_nActiveSystem]->GetTextureID());
      //  g_pParticleSystems[g_nActiveSystem]->SetPosition(MyVector(x, y, z));
        g_pParticleSystems[g_nActiveSystem]->Render();
        
    }

    //
    // Reset OpenGL states...
    //
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);

    glPopMatrix();
}