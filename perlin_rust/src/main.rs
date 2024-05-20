mod perlin;
use std::fs::File;
use std::io::{self, Write};
use clap::Parser;

#[derive(Parser, Debug)]
#[clap(name = "PerlinNoise CLI")]
#[clap(version = "1.0")]
#[clap(about = "A simple CLI to generate perlin noise")]
struct Cli {
    /// Width of the grid
    #[clap(short = 'w', long = "width", default_value = "1080")]
    width: i32,

    /// Height of the grid
    #[clap(short = 'H', long = "height", default_value = "1920")]
    height: i32,

    /// Grid width
    #[clap(short = 'g', long = "grid_width", default_value = "400.0")]
    grid_width: f32,

    /// Number of octaves
    #[clap(short = 'o', long = "octaves", default_value = "8")]
    octaves: i32,

    /// Seed for the random generator
    #[clap(short = 's', long = "seed", default_value = "133742069")]
    seed: u64,

    /// name for the output txt file
    #[clap(short = 'n', long = "name", default_value = "rust.txt")]
    name: String,
}


fn main() -> io::Result<()> {
    let args = Cli::parse();

    // let seed: u64 = 1337;
    // let width: i32 = 1080;
    // let height: i32 = 1920;
    // let grid_width: f32 = 400.;
    // let octaves : i32 = 8;

    let seed = args.seed;
    let width = args.width;
    let height = args.height;
    let grid_width = args.grid_width;
    let octaves = args.octaves;

    let mut perlin = perlin::Perlin::new(seed);

    let mut result: Vec<f32> = vec![0.0; (width * height) as usize];

    for x in 0..width { 
        for y in 0..height {
            let index : usize = (y * width + x) as usize;
            let mut val : f32 = 0.0;
            let mut amplitude : f32 = 1.0;
            let mut frequency : f32 = 1.0;
            for _ in 0..octaves {
                let xp : f32 = x as f32 / grid_width * frequency;
                let yp : f32 = y as f32 / grid_width * frequency;
                val += perlin.eval(xp, yp) * amplitude;
                frequency *= 2.0;
                amplitude /= 2.0;
            }
            result[index] = val;
        }
    }

    if let Some(output) = perlin::rescale(result) {
        let file_path = format!("../data/{}", args.name);
        let mut file = File::create(file_path)?;
        for x in 0..width {
            for y in 0..height {
                let index : usize = (y * width + x) as usize;
                write!(file, "{} ", output[index])?;
            }
            write!(file, "\n")?;
        }
    } else {
        println!("No result vector provided!");
    }
    Ok(())
}
