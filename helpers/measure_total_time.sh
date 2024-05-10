#!/bin/bash

EXEC_DIR="../build/src/"
total_time=0

for executable in "$EXEC_DIR"/*; do
    if [ -f "$executable" ] && [ -x "$executable" ]; then
        start_time=$(date +%s.%N)
        IFS="_" read -r -a parts <<< "$executable"
        year=${parts[0]: -4}
        day=${parts[1]}
        input_path="./src/$year/$day/input.txt"
        echo $input_path
        "$executable" $input_path> /dev/null 2>&1
        end_time=$(date +%s.%N)
        execution_time=$(echo "$end_time - $start_time" | bc)
        echo "execution time for $(basename "$executable"): $execution_time seconds"
        total_time=$(echo "$total_time + $execution_time" | bc)
    fi
done

echo "Total execution time for all executables: $total_time seconds"
