use rand::{Rng, SeedableRng};
use rand::rngs::StdRng;
use std::collections::HashMap;


pub struct RandomVector{
    rng: StdRng,
    cache: HashMap<(i32, i32), (f32, f32)>,
}

impl RandomVector{
    pub fn new(seed: u64) -> RandomVector {
        let rng = StdRng::seed_from_u64(seed);
        let cache = HashMap::new();
        RandomVector {rng, cache}
    }

    pub fn eval(&mut self, xp: f32, yp: f32, xx: i32, yy: i32) -> f32 {
        let dx: f32 = xp - xx as f32;
        let dy: f32 = yp - yy as f32;
        let gradient: (f32, f32) = self.get_random_gradient(xx, yy);
        dx * gradient.0 + dy * gradient.1
    }

    fn get_random_gradient(&mut self, xx: i32, yy: i32) -> (f32, f32) {
        let key: (i32, i32) = (xx, yy);

        if let Some(&gradient) = self.cache.get(&key) {
            return gradient;
        }

        let gradient = self.generate_random();
        self.cache.insert(key, gradient);
        gradient
    }

    fn generate_random(&mut self) -> (f32, f32) {
        let angle = self.rng.gen::<f32>() * 2.0 * std::f32::consts::PI;
        (angle.cos(), angle.sin())
    }
}