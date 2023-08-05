use stack::Stack;

mod stack;

fn test() {
    let mut s = Stack::<i32>::new();
    for i in 0..10 {
        s.push(i);
    }
    println!("Stack size: {}", s.len());
    println!("Stach capacity: {}", s.capacity());

    println!("Stack top: {}", s.top().unwrap());
    s.pop();
    println!("Stack top: {}", s.top().unwrap());

    println!("Clear stack.");
    s.clear();
    println!("Is empty: {}", s.empty());
}

fn main() {
    test();
}
