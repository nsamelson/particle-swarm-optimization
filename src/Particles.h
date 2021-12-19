#pragma once
#include <vector>
#include <raylib.h>
#include "Ball.h"

class Particles{
    private:
        std::vector<Ball> particles;
        std::vector<Vector3> velocities;

        // std::vector<Ball> personal_bests;
        // std::vector<Ball> personal_best_values;

        Vector3 global_best;
        Vector3 prev_p_best;
        // Ball global_best_value;
        float wMax;
        float wMin;
        
        float cMax;
        float cMin;

        float w;
        float c1;
        float c2;

        int number_of_particles;
        int iterations;

        

    public:
        Particles(int ball_quantity);

        

        void init_position(float x, float y, float z);
        void move_particles(float dt,int iteration);
        void update_bests();
        void empty_vector();

        int get_quantity();
        float get_w();
        float get_c1();
        float get_c2();

        Vector3 get_g_best();

        std::vector<Ball> get_particles();
        std::vector<Vector3> get_velocities();
        std::vector<Vector3> get_positions();

};