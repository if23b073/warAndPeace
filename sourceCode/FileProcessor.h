#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <optional>
#include <algorithm>
#include <numeric>
#include <cctype>
#include <functional>
#include <map>
#include <execution>


auto readFile = [](std::function<std::istream*()> inputProvider) -> std::optional<std::string> {
    std::unique_ptr<std::istream> input(inputProvider());
    if (!input || !(*input)) {
        return std::nullopt; 
    }

    std::stringstream buffer;
    buffer << input->rdbuf(); 
    return buffer.str();      
};

auto fileInputProvider = [](const std::string& filename) -> std::function<std::istream*()> {
    return [filename]() -> std::istream* {
        return new std::ifstream(filename); 
    };
};

auto tokenize = [](const std::string& text) -> std::vector<std::string> {
    return std::accumulate(text.begin(), text.end(), std::vector<std::string>{}, 
        [](std::vector<std::string>& words, char ch) -> std::vector<std::string>& {
            static std::string currentWord;

            if (std::isalpha(ch) || ch == '\'') { // Include apostrophes for contractions like "it's"
                currentWord += std::tolower(ch);
            } else if (!currentWord.empty()) { // End of a word
                words.push_back(currentWord);
                currentWord.clear();
            }
            return words;
        });
};

// Split sentences function using accumulate
auto splitSentences = [](const std::string& text) -> std::vector<std::string> {
    return std::accumulate(text.begin(), text.end(), std::vector<std::string>{}, 
        [](std::vector<std::string>& sentences, char ch) -> std::vector<std::string>& {
            static std::string currentSentence;
            static bool inSentence = false;

            currentSentence += ch;
            if (std::isalpha(ch)) {
                inSentence = true;
            }

            if (ch == '.' || ch == '!' || ch == '?') {
                if (inSentence) {
                    sentences.push_back(currentSentence);
                    currentSentence.clear();
                    inSentence = false;
                }
            }
            return sentences;
        });
};

// Create histogram function using accumulate
auto createHistogram = [](const std::vector<std::string>& sentences) -> std::map<int, int> {
    return std::accumulate(sentences.begin(), sentences.end(), std::map<int, int>(), 
        [](std::map<int, int>& histogram, const std::string& sentence) -> std::map<int, int> & {
            auto words = tokenize(sentence);
            int wordCount = words.size();
            if (wordCount > 0) { 
                histogram[wordCount]++;
            }
            return histogram;
        });
};


auto writeToFile = [](const std::map<int, int>& histogram, const std::string& filename) -> std::optional<std::string> {
    std::ofstream file(filename); 
    if (!file.is_open()) {
        return std::nullopt; 
    }

    for (const auto& entry : histogram) {
        file << "Sentence length: " << entry.first << " words - Frequency: " << entry.second << "\n";
    }

    return "Histogram successfully written to " + filename;
};

auto processFile = [](const std::string& inputFile, const std::string& outputFile) -> std::optional<std::string> {
    std::cout << "Starting to process file: " << inputFile << std::endl;

    auto contentOpt = readFile(fileInputProvider(inputFile)); 
    if (!contentOpt) {
        std::cerr << "Failed to read file: " << inputFile << std::endl;
        return std::nullopt; 
    }

    std::cout << "File successfully read. Splitting the content into sentences..." << std::endl;
    auto sentences = splitSentences(*contentOpt);

    std::cout << "Sentence splitting complete. Sentence count: " << sentences.size() << std::endl;

    std::cout << "Creating histogram from sentences..." << std::endl;
    auto histogram = createHistogram(sentences);

    std::cout << "Histogram created. Writing to file: " << outputFile << std::endl;
    auto writeResult = writeToFile(histogram, outputFile);

    if (writeResult) {
        std::cout << "Successfully wrote to file: " << outputFile << std::endl;
        return *writeResult;
    } else {
        std::cerr << "Failed to write to file: " << outputFile << std::endl;
        return std::nullopt;
    }
};