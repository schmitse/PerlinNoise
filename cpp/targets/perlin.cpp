#include "Perlin.hpp"
#include <iostream>
#include <fstream>
#include <CLI/CLI.hpp>
#include <indicators/progress_bar.hpp>


int main(int argc, char **argv) {
    // Default values
    int height = 1080;
    int width = 1920;
    int seed = 1337;
    float grid_size = 400.0;
    int octaves = 8;
    std::string output_file = "cpp.txt";

    // CLI11 parser setup
    CLI::App app{"Perlin Noise Generator"};
    
    app.add_option("-H,--height", height, "Height of the grid")->default_val("1080");
    app.add_option("-w,--width", width, "Width of the grid")->default_val("1920");
    app.add_option("-s,--seed", seed, "Seed for the noise generator")->default_val("1337");
    app.add_option("-g,--grid_size", grid_size, "Grid size for the noise")->default_val("400.0");
    app.add_option("-o,--octaves", octaves, "Number of octaves for the noise")->default_val("8");
    app.add_option("-n,--name", output_file, "Name of the output file")->default_val("cpp.txt");

    CLI11_PARSE(app, argc, argv);

    float amplitude = 1.0;
    float frequency = 1.0;
    std::vector<float> values((height * width), 0.0);
    Perlin noiseCreator = Perlin(seed);

    indicators::ProgressBar bar{
        indicators::option::BarWidth{40},
        indicators::option::Start{"["},
        indicators::option::Fill{"="},
        indicators::option::Lead{">"},
        indicators::option::Remainder{" "},
        indicators::option::End{"]"},
        indicators::option::PostfixText{"Generating noise..."},
        indicators::option::ForegroundColor{indicators::Color::cyan},
        indicators::option::ShowElapsedTime{true},
        indicators::option::ShowRemainingTime{true},
        indicators::option::ShowPercentage{true},
        indicators::option::MaxProgress{width}
    };

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
            values[index] = val;
        }
        bar.tick();
    }
    bar.set_option(indicators::option::PostfixText{"Noise generation complete!"});
    bar.mark_as_completed();

    std::vector<float> result = noiseCreator.rescale(values);
    std::cout << "Had a total of " << noiseCreator.getCacheHits() << " cache hits." << std::endl;

    std::cout << "Saving results in outputfile: " << output_file << std::endl;
    std::ofstream file(output_file);
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