#pragma once
#include <raylib.h>

class Perlin {
    private:

        int SEED;
        // static int hash[];

        int noise2(int x, int y);
        float lin_inter(float x, float y, float s);
        float smooth_inter(float x, float y, float s);
        float noise2d(float x, float y);


    public:
        Perlin();
        float perlin2d(float x, float y, float freq, int depth);

};