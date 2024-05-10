#!/bin/bash

cookies_file="cookies.txt"
for year_dir in "./src/"*/; do
    if [ -d "$year_dir" ]; then
        year=$(basename $year_dir)
        year_digits="${year: -2}"
        for day_dir in "$year_dir"*/; do
          day=$(basename $day_dir)
          day_digits="${day: 3}"
          echo "fetching year $year day $day"
          url="https://adventofcode.com/20$year_digits/day/$day_digits/input"
          output_dir="./src/20$year_digits/day$day_digits/"
          response=$(curl -s -b "$cookies_file" "$url")
          if [ $? -eq 0 ]; then
            echo "successfully fetched"
            echo "$response" > "$output_dir/input.txt"
          fi
        done
    fi
done
