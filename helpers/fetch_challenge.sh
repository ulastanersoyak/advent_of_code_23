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
output_dir="../src/20$year/day$day"
if [ ! -d "$output_dir" ]; then
    mkdir -p "$output_dir"
fi
response=$(curl -s -b "$cookies_file" "$url")
if [ $? -eq 0 ]; then
    echo "$response" > "$output_dir/input.txt"
else
    echo "failed request response <$response> from <$url>"
fi
