#pragma once
#include <vector>
#include <raylib.h>


class Ball {
    private:
        Vector3 position;
        Vector3 bestPersonal;
        // Vector3 bestGlobal;
        Vector3 speed;
        float radius;
        bool isNewBest;

    public:
        Ball(Vector3 ballPosition, Vector3 bestPersonal, Vector3 ballSpeed,float ballRadius);
        Ball() = default;
        
        void updatePosition(float dt);
        void updateVelocity(Vector3 g_best,Vector3 r_p,Vector3 r_g,float c0,float c1,float w);
        Vector3 updateFitness(Vector3 global_best);

        // void avoidCube(Vector3 cubePos,Vector3 cubeDim);
        // void collideWithCube(Vector3 cubePos,Vector3 cubeDim);

        bool getIsNewBesst();
        Vector3 getPosition();
        Vector3 getBestPosition();
        float getRadius();
        Vector3 getVelocity();
        
};