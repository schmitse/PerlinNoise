mod perlin;
use std::fs::File;
use std::io::{self, Write};


fn main() -> io::Result<()> {
    let seed: u64 = 1337;
    let width: i32 = 1080;
    let height: i32 = 1920;

    let grid_width: f32 = 400.;
    let octaves : i32 = 8;

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

    let mut file = File::create("../data/rust.txt")?;
    for x in 0..width {
        for y in 0..height {
            let index : usize = (y * width + x) as usize;
            write!(file, "{} ", result[index])?;
        }
        write!(file, "\n")?;
    }
    Ok(())
}
