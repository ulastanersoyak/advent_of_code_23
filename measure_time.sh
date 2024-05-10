#!/bin/bash

# Directory containing executable files
EXEC_DIR="./build/src/"

# Total time variable
total_time=0

# Iterate over each executable file in the directory
for executable in "$EXEC_DIR"/*; do
    # Check if it's a file and executable
    if [ -f "$executable" ] && [ -x "$executable" ]; then
        # Get start time
        start_time=$(date +%s.%N)
        
        # Run the executable and suppress output
        "$executable" > /dev/null 2>&1
        
        # Get end time
        end_time=$(date +%s.%N)
        
        # Calculate execution time
        execution_time=$(echo "$end_time - $start_time" | bc)
        
        # Print execution time
        echo "Execution time for $(basename "$executable"): $execution_time seconds"
        
        # Add to total time
        total_time=$(echo "$total_time + $execution_time" | bc)
    fi
done

# Print total execution time
echo "Total execution time for all executables: $total_time seconds"
