
fn main() {
    fizz_buzz_algorithm(100);
}

fn fizz_buzz_algorithm(max: i32) {
    for i in 1..max {
        let word = get_correct_word(i);
        if word == "" {
            println!("{}", i);
        }
        else {
            println!("{}", word);
        }
    }
}

fn get_correct_word(number: i32) -> String {
    if (number % 5) == 0 && (number % 3) == 0 {
        return "fizz buzz".to_string();
    }
    else if (number % 3) == 0 {
        return "fizz".to_string();
    }
    else if (number % 5) == 0 {
        return "buzz".to_string();
    }
    else {
        return "".to_string();
    }
}