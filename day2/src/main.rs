
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

fn second_puzzle(file: File) {
    let buffer_lines = BufReader::new(file).lines();
    let lines: Vec<_> = buffer_lines.map(|line| {line.unwrap()}).collect();
    let mut r_id: String = "".to_owned();
    let mut r_type = 0;
    for i in 0..lines.len() {
        for j in (i+1)..lines.len() {
            let vectora: Vec<char> = lines[i].chars().collect();
            let vectorb: Vec<char> = lines[j].chars().collect();
            let mut result_id: String = "".to_owned();
            let mut result_type = 0;
            for k in 0..vectora.len() {
                if vectora[k] == vectorb[k] {
                    result_id.push(vectora[k]);
                    result_type = result_type +1;
                }
            }
            if result_type > r_type {
                r_type = result_type;
                r_id = result_id;
            }
        }
    }
    println!("Common grade {} code: {}", r_type, r_id);
}
