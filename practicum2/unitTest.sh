#!/bin/bash

# Define paths and filenames
FOO_FILE="foo.txt"
NEW_FOO_FILE="newfoo.txt"


# Function to check file presence and size
check_file() {
    local file=$1
    local expected_size=$2

    if [ -e "$file" ]; then
        echo "File $file exists"
        
        actual_size=$(ls -l "$file" | awk '{print $5}')

        if [ "$actual_size" -eq "$expected_size" ]; then
            echo "File size is correct"
        else
            echo "File size is incorrect"
        fi
    else
        echo "File $file does not exist"
    fi
}

# Test performing WRITE operation
./rfs WRITE "$FOO_FILE"
foo_size=$(stat -s %s "$FOO_FILE")
check_file "rfsys/foo.txt" "$foo_size"

# Perform GET operation
#perform_get

# Check if the file exists and has the correct size
#check_file "$GET_FILE"  # Replace with the expected size

# Perform REMOVE operation
#perform_remove

# Check if the file is removed
#check_file "$REMOVE_FILE"  # Replace with the expected size

# Perform LS operation
#perform_ls
