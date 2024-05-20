struct Greeter;

impl Greeter {
    fn new() -> Greeter {
        Greeter
    }

    fn say_hello(&self) {
        println!("Hello World!");
    }

    fn say_goodbye(&self) {
        println!("Goodbye World!");
    }
}


fn main() {
    let greeter = Greeter::new();
    greeter.say_hello();
    greeter.say_goodbye();
}
