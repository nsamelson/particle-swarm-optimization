#include "Ball.h"
#include <raymath.h>
#include <rlgl.h>

Ball::Ball(Vector3 position, Vector3 bestPersonal, Vector3 speed,float radius) {
    this->position = position;
    this->bestPersonal = bestPersonal;
    // this->height = height;

    this->speed = speed;
    this->radius = radius;

    this->isNewBest = false;

}

Vector3 Ball::updateFitness(Vector3 g_best){
    float xi = float(position.x / 10.0f) + 1.50f;
    float zi = float(position.z / 10.0f) + 1.50f;
    // float xi = position.x;
    // float zi = position.z;

    float y = pow(xi - 3.14,2)+ pow(zi - 2.72,2) + sin(3*xi + 1.41) + sin(4*zi - 1.73) + 2.0f;
    position.y = y;
    
    if (position.y < bestPersonal.y){
        bestPersonal = position;
        if(bestPersonal.y < g_best.y){
                g_best = bestPersonal;
            }
    }

    return g_best;
    
}
void Ball::updatePosition(float dt){

    position.x += speed.x * dt;
    position.z += speed.z * dt;


}
void Ball::updateVelocity(Vector3 g_best,Vector3 r_p,Vector3 r_g,float c1=2.0f,float c2=2.0f,float w=0.9f){
   
    speed.x  = (w * speed.x + c1 * r_p.x * (bestPersonal.x - position.x ) + c2 * r_g.x  * (g_best.x - position.x));
    speed.z  = (w * speed.z + c1 * r_p.z * (bestPersonal.z - position.z) + c2 * r_g.z  * (g_best.z - position.z ));

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
float Ball::getHeight(){
    return height;
}
void Ball::setHeight(float h){
    height = h;
}
