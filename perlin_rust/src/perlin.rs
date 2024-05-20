#[path = "random_vector.rs"] mod random_vector;


pub struct Perlin {
    rnd_vec: random_vector::RandomVector,
}

fn fade(val : f32) -> f32 {
    val * val * val * ( val * ( val * 6.0 - 15.0 ) + 10.0 )
}

fn lerp(v0: f32, v1 : f32, ds : f32) -> f32 {
    v0 + (v1 - v0) * ds
}

impl Perlin {
    pub fn new(seed: u64) -> Perlin {
        println!("Initialising Perlin creator with seed: {}", seed);
        let rnd_vec = random_vector::RandomVector::new(seed);
        Perlin{ rnd_vec }
    }

    pub fn eval(&mut self, xp: f32, yp: f32) -> f32 {
        let xlower : i32 = xp as i32;
        let ylower : i32 = yp as i32;
        let xupper : i32 = xlower + 1;
        let yupper : i32 = ylower + 1;

        let dx : f32 = fade(xp - xlower as f32);
        let dy : f32 = fade(yp - ylower as f32);

        let rg_lower_0 = self.rnd_vec.eval(xp, yp, xlower, ylower);
        let rg_upper_0 = self.rnd_vec.eval(xp, yp, xupper, ylower);
        let interp_lower = lerp(rg_lower_0, rg_upper_0, dx);

        let rg_lower_1 = self.rnd_vec.eval(xp, yp, xlower, yupper);
        let rg_upper_1 = self.rnd_vec.eval(xp, yp, xupper, yupper);
        let interp_upper = lerp(rg_lower_1, rg_upper_1, dx);

        lerp(interp_lower, interp_upper, dy)
    }

}