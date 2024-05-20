#include "RandomVector.hpp"
#include <cmath>

RandomVector::RandomVector() : m_generator(0., 2 * 3.14159264), m_cacheHits(0) {
    std::seed_seq m_seed{1337};
    m_engine = std::default_random_engine{m_seed};
    m_generator = std::uniform_real_distribution<float>(0., 2 * 3.141592654);
}

RandomVector::RandomVector(int seed) : m_generator(0., 2 * 3.14159264), m_cacheHits(0) {
    std::seed_seq m_seed{seed};
    m_engine = std::default_random_engine{m_seed};
}

float RandomVector::eval(float xp, float yp, int xx, int yy){
    float dx = xp - float(xx);
    float dy = yp - float(yy);
    std::vector<float> gradient = RandomVector::randomVector(xx, yy);
    return dx * gradient.at(0) + dy * gradient.at(1);
}

std::vector<float> RandomVector::randomVector(int xx, int yy) {
    std::tuple<int, int> _key = std::make_tuple(xx, yy);
    if (m_cache.find(_key) != m_cache.end()) {
        m_cacheHits++;
        return m_cache.at(_key);
    }
    std::vector<float> _rVec = RandomVector::getVector();
    m_cache.insert({_key, _rVec});
    return _rVec;
}

std::vector<float> RandomVector::getVector(){
    float angle = m_generator(m_engine);
    return std::vector<float> {std::cos(angle), std::sin(angle)};
}
