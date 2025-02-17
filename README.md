# Prerequisites
- C++ compiler (e.g., g++ or clang)
- make (build automation tool)

# Compile & Run
This is a C++ project that uses a Makefile to simplify the compilation process
## Steps
- Open a terminal and navigate to the project sourceCode directory where the Makefile is located
- Run the following command
```bash
make
```
- This will create the executable file "word_counter" in the sourceCode directory
- Once the project is compiled, run the program by executing the following command (inputFile is a required argument, outputFile is optional)
```bash
./word_counter <inputFile> [outputFile]
```
- After that, the result is written into the defined outputFile or output.txt if none is passed as argument