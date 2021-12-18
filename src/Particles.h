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
        // Ball global_best_value;

        

        int number_of_particles;

        

    public:
        Particles(int ball_quantity);

        float w;
        float c1;
        float c2;

        void init_position(float x, float y, float z);
        void move_particles(float dt);
        void update_bests();
        void empty_vector();

        int get_quantity();

        std::vector<Ball> get_particles();
        std::vector<Vector3> get_velocities();
        std::vector<Vector3> get_positions();

};