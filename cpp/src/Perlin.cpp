#include "Perlin.hpp"
#include "RandomVector.hpp"

Perlin::Perlin(int seed) : m_vector(seed) {
    m_seed = seed;
    std::cout << "Initialising Perlin Generator with seed: " << seed << std::endl;
}

float Perlin::operator()(float xp, float yp){
    int xlower = int(xp);
    int ylower = int(yp);
    int xupper = xlower + 1;
    int yupper = ylower + 1;

    float dx = Perlin::fade(xp - float(xlower));
    float dy = Perlin::fade(yp - float(ylower));

    float rgLower0 = m_vector.eval(xp, yp, xlower, ylower);
    float rgUpper0 = m_vector.eval(xp, yp, xupper, ylower);
    float interpLower = Perlin::lerp(rgLower0, rgUpper0, dx);

    float rgLower1 = m_vector.eval(xp, yp, xlower, yupper);
    float rgUpper1 = m_vector.eval(xp, yp, xupper, yupper);
    float interpUpper = Perlin::lerp(rgLower1, rgUpper1, dx);

    return Perlin::lerp(interpLower, interpUpper, dy);
}

std::vector<float> Perlin::rescale(std::vector<float> input) {
    float _max = *std::max_element(input.begin(), input.end());
    float _min = *std::min_element(input.begin(), input.end());

    std::vector<float> _output;
    _output.reserve(input.size());

    for (int i = 0; i < input.size(); i++) {
        _output.push_back(-1 + (input.at(i) - _min) / (_max - _min) * 2);
    }
    return _output;
}