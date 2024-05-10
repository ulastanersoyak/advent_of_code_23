#!/bin/bash

EXEC_DIR="./build/src/"
total_time=0

for executable in "$EXEC_DIR"/*; do
    if [ -f "$executable" ] && [ -x "$executable" ]; then
        start_time=$(date +%s.%N)
        "$executable" > /dev/null 2>&1
        end_time=$(date +%s.%N)
        execution_time=$(echo "$end_time - $start_time" | bc)
        echo "Execution time for $(basename "$executable"): $execution_time seconds"
        total_time=$(echo "$total_time + $execution_time" | bc)
    fi
done

echo "Total execution time for all executables: $total_time seconds"
