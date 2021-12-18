#include "Ball.h"
#include <raymath.h>
#include <rlgl.h>

Ball::Ball(Vector3 position, Vector3 bestPersonal, Vector3 speed,float radius) {
    this->position = position;
    this->bestPersonal = bestPersonal;

    this->speed = speed;
    this->radius = radius;

    this->isNewBest = false;

}


void Ball::updatePosition(float dt){

    position.x += speed.x * dt;
    position.y += speed.y * dt; 
    position.z += speed.z * dt;

    if (position.y < bestPersonal.y){
        bestPersonal = position;
        isNewBest = true;
    }
    else{
        isNewBest = false;
    }

}
void Ball::updateVelocity(Vector3 g_best,Vector3 r_p,Vector3 r_g,float c0=2.0f,float c1=2.0f,float w=0.9f){
    float slow = 0.6f;
   
    speed.x  = (w * speed.x + c0 * r_p.x * (bestPersonal.x - position.x) + c1 * r_g.x * (g_best.x - position.x)) * slow;
    speed.y = (w * speed.y + c0 * r_p.y * (bestPersonal.y - position.y) + c1 * r_g.y * (g_best.y - position.y)) * slow;
    speed.z  = (w * speed.z + c0 * r_p.z * (bestPersonal.z - position.z) + c1 * r_g.z * (g_best.z - position.z)) * slow;

}

Vector3 Ball::getBestPosition(){
    return bestPersonal;
}
Vector3 Ball::getPosition(){
    return position;
}
float Ball::getRadius(){
    return radius;
}
Vector3 Ball::getVelocity(){
    return speed;
}
bool Ball::getIsNewBesst(){
    return isNewBest;
}
