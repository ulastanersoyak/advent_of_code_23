#!/bin/bash

for year_dir in "../src/"*/; do
    if [ -d "$year_dir" ]; then
        year=$(basename "$year_dir")
        present_numbers=""
        for day_dir in "$year_dir"*/; do
            day=$(basename "$day_dir")
            day_digits="${day:3}"
            present_numbers="$present_numbers $day_digits"
        done

        absent_numbers=""
        for ((i=1; i<=25; i++)); do
            if [[ ! $present_numbers =~ $i ]]; then
                absent_numbers="$absent_numbers $i"
            fi
        done
        echo "year $year:"
        echo "present days: $present_numbers"
        echo "absent days: $absent_numbers"
    fi
done
