#!/bin/bash

# Define the name of the output includes.h file
output_file="src/includes.h"

# Function to recursively search for .h files and generate include links
generate_includes() {
    local dir="$1"

    # Loop through .h files in the current directory
    for header_file in "$dir"/*.h; do
        if [ -f "$header_file" ]; then
            echo "#include \"$header_file\"" >> "$output_file"
        fi
    done

    # Recursively process subdirectories
    for subdir in "$dir"/*/; do
        if [ -d "$subdir" ]; then
            generate_includes "$subdir"
        fi
    done
}

# Clear the output file if it exists
> "$output_file"

# Start generating includes from the current directory
generate_includes "$(pwd)"

echo "Includes generated in $output_file"
