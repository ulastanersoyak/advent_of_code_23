#!/bin/bash

if [ "$#" -ne 2 ]; then
    echo "usage: $0 <year> <day>"
    exit 1
fi

year=$1
day=$2

if [ "$year" -lt 15 ] || [ "$year" -gt "$(date +'%Y')" ]; then
    echo "year $year is invalid"
    exit 1
fi

if [ "$day" -lt 1 ] || [ "$day" -gt 25 ]; then
    echo "day $day is invalid"
    exit 1
fi

url="https://adventofcode.com/20$year/day/$day/input"
cookies_file="cookies.txt"
output_dir="20$year/day$day"

if [ ! -d "$output_dir" ]; then
    mkdir -p "$output_dir"
fi

response=$(curl -s -b "$cookies_file" "$url")

if [ $? -eq 0 ]; then
    echo "$response" > "$output_dir/input.txt"

    echo "#include <vector>
#include <fstream>
#include <string>
#include <iostream>

int main(int argc, char **argv){
  if(argc < 2){
     std::cerr << \"usage: \" << argv[0] << \" <filename>\\n\";
    return -1;
  }
  std::ifstream file{argv[1]};
  if(!file){
    std::cerr << \"failed to open file \" << argv[1];
    return -1;
  }
  std::string line;
  while(std::getline(file, line)){
  }
  file.close();
  return 0;
}" > "$output_dir/main_p1.cpp"

    echo "#include <vector>
#include <fstream>
#include <string>
#include <iostream>

int main(int argc, char **argv){
  if(argc < 2){
     std::cerr << \"usage: \" << argv[0] << \" <filename>\\n\";
    return -1;
  }
  std::ifstream file{argv[1]};
  if(!file){
    std::cerr << \"failed to open file \" << argv[1];
    return -1;
  }
  std::string line;
  while(std::getline(file, line)){
  }
  file.close();
  return 0;
}" > "$output_dir/main_p2.cpp"

    echo -e "all: main_p1 main_p2\n\nmain_p1: main_p1.cpp\n\tg++ -g main_p1.cpp -o main_p1\n\nmain_p2: main_p2.cpp\n\tg++ -g main_p2.cpp -o main_p2\n\nrun: all\n\t./main_p1 input.txt\n\t./main_p2 input.txt" > "$output_dir/makefile"

    echo "*.txt" > "$output_dir/.gitignore"
    cd $output_dir
    nvim .

else
    echo "failed request response <$response> from <$url>"
fi
