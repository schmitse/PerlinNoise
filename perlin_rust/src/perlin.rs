use crate::random_vector;

struct Perlin {
    rnd_vec: random_vector::RandomVector,
}

impl Perlin {
    fn new(seed: i32) -> Perlin {
        let mut rv = random_vector::RandomVector::new(seed);
        Perlin{ rv }
    }

}