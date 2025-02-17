#!/bin/bash

# Compile the program using the Makefile
echo "Compiling the program..."
make -C sourceCode
if [ $? -ne 0 ]; then
    echo "Compilation failed."
    exit 1
fi

# Run the compiled program with a test file
echo "Running the program..."
./sourceCode/word_counter sourceCode/warAndPeace.txt output.txt
if [ $? -ne 0 ]; then
    echo "Program execution failed."
    exit 1
fi

echo "Program ran successfully. Check the output file: output.txt"