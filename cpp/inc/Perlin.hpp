#ifndef PERLIN_HPP
#define PERLIN_HPP

#include <iostream>
#include "RandomVector.hpp"

class Perlin{
    public:
        Perlin(int seed = 1337);
        float operator()(float xp, float yp);
        std::vector<float> rescale(std::vector<float> input);
        int getCacheHits(){return m_vector.getCacheHits();};
    private:
        float fade(float val) {return val * val * val * (val * (val * 6 - 15) + 10);};
        float lerp(float v0, float v1, float ds) {return v0 + (v1 - v0) * ds;};
        int m_seed;
        RandomVector m_vector;
};

#endif