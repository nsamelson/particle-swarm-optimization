#include "Ball.h"
#include <raymath.h>
#include <rlgl.h>
#include "Particles.h"
#include <string>
#include <iostream>

using namespace std;

Particles::Particles(int ball_quantity) {
    this->particles = std::vector<Ball>();
    // this->number_of_particles = ball_quantity;
    this->number_of_particles = 0;

    //this->velocities = velocities;
    this->w = 0.9f;
    this->c1 = 2.0f;
    this->c2 = 2.0f;

    //push particles
    this->global_best = {5.0f,30.0f,5.0f};

}
void Particles::empty_vector(){
    particles.clear();
    number_of_particles = 0;
    global_best = {5.0f,10.0f,5.0f};
    w = 0.9f;
}
void Particles::init_position(float x, float y, float z){
    
    float r1 = 4 + static_cast <float> (rand()) / static_cast <float> (RAND_MAX/(-4-4));
    float r2 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/4));
    float r3 = 4 + static_cast <float> (rand()) / static_cast <float> (RAND_MAX/(-4-4));

    float factor = 3.0f;
    Vector3 speed = {r1 * factor,r2*factor,r3*factor};
    Vector3 position = {x,y,z};
    
    if(position.y < global_best.y){
            global_best = position;
        }

    Ball ball = Ball(position,position,speed,0.1f);
    this->particles.push_back(ball); 
    number_of_particles += 1;

}


void Particles::move_particles(float dt){
    for (int i =0;i<number_of_particles;i++){
        float rp1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float rp2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float rp3 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

        float rg1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float rg2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float rg3 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

        Vector3 random_personal = {rp1,rp2,rp3};
        Vector3 random_global = {rg1,rg2,rg3};

        
        global_best = particles[i].updateFitness(global_best);
        particles[i].updateVelocity(global_best,random_personal, random_global,c1,c2,w);        
        particles[i].updatePosition(dt);
    }
    if(w > 0.0f){
        w-= 0.001f;
    }
}

std::vector<Ball> Particles::get_particles(){
    return particles;
}
int Particles::get_quantity(){
    return number_of_particles;
}
std::vector<Ball> get_particles();
std::vector<Vector3> get_velocities();
std::vector<Vector3> get_positions();