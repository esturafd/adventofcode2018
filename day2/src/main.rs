
use std::io::{BufReader, BufRead};
use std::fs::File;
use std::env;

fn main() {
    let args: Vec<String> = env::args().collect();
    let file = File::open("input.txt").unwrap();
    if args[1] == "1" {
        first_puzzle(file);
    } else if args[1] == "2" {
        //second_puzzle(file);
    } else {
        println!("Invalid argument");
    }
}

fn first_puzzle(file: File) {
    let mut count = [0,0];
    for line in BufReader::new(file).lines() {
        let string_line = line.unwrap();
        let mut valid = [false,false];
        for chr in string_line.chars() {
            let vector: Vec<&str> = string_line.matches(chr).collect();
            let number = vector.len();
            if number <= 3 && number >= 2 && !valid[number -2] {
                valid[number -2] = true;
                count[number -2] = count[number -2] +1;
            }
        }
    }
    println!("The checksum of the boxes is {}", count[0] * count[1]);
}
