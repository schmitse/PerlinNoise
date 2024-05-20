mod random_vector;


fn main() {
    println!("Hello, world!");
    let seed: u64 = 1337;
    let mut rv = random_vector::RandomVector::new(seed);

    let xx: i32 = 5;
    let yy: i32 = 4;
    let xp: f32 = 5.32;
    let yp: f32 = 4.22;

    let result: f32 = rv.eval(xp, yp, xx, yy);

    println!("Result {}", result);
}
