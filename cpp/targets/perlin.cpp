#include "Perlin.hpp"
#include <iostream>
#include <fstream>


int main() {

    int height = 1080;
    int width = 1920;
    int seed = 1337;
    std::vector<float> values((height * width), 0.0);
    // values.reserve((height * width));

    float grid_size = 400.;
    float amplitude = 1.0;
    float frequency = 1.0;
    int octaves = 8;

    Perlin noiseCreator = Perlin(seed);

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            int index = y * width + x;
            float val = 0.;
            amplitude = 1.;
            frequency = 1.;
            for (int ioct = 0; ioct < octaves; ioct++) {
                float nx = float(x) / grid_size * frequency;
                float ny = float(y) / grid_size * frequency;
                val += noiseCreator(nx, ny) * amplitude;
                amplitude /= 2.;
                frequency *= 2.;
            }
            // values.push_back(val);
            values[index] = val;
        }
    }
    std::vector<float> result = noiseCreator.rescale(values);
    std::cout << "Had a total of " << noiseCreator.getCacheHits() << " cache hits." << std::endl;

    std::cout << "Saving results in outputfile.. " << std::endl;
    std::ofstream file("/Users/schmitse/Templates/PerlinNoise/data/cpp.txt");
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int index = y * width + x;
            file << result.at(index) << " ";
        }
        file << std::endl;
    }
    file.close();
    std::cout << "finished saving results!" << std::endl;
    return 0;
}