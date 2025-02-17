#include "FileProcessor.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <inputFile> [outputFile]" << std::endl;
        return 1;
    }
    const std::string inputFile = argv[1];
    const std::string outputFile = (argc > 2) ? argv[2] : "output.txt";

    auto result = processFile(inputFile, outputFile);
    if (result) {
        std::cout << *result << std::endl;
    } else {
        std::cerr << "Datei konnte nicht verarbeitet werden." << std::endl;
        return 1;
    }

    return 0;
} 