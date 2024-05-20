#ifndef RANDOMVECTOR_HPP
#define RANDOMVECTOR_HPP

#include <vector>
#include <map>
#include <tuple>
#include <random>

class RandomVector{
    public:
        RandomVector();
        RandomVector(int seed);
        float eval(float xp, float yp, int xx, int yy);
        int getCacheHits() {return m_cacheHits;};
    private:
        std::vector<float> randomVector(int xx, int yy);
        std::vector<float> getVector();
        std::map<std::tuple<int, int>, std::vector<float>> m_cache;
        std::default_random_engine m_engine;
        std::uniform_real_distribution<float> m_generator;
        int m_cacheHits;
};


#endif