#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../FileProcessor.h"
#include <iostream>

TEST_CASE("processFile") {
    SUBCASE("Valid input and output files") {
        std::ofstream input("test_input.txt");
        input << "Hello, world! Welcome to the test. To test the histograms!";
        input.close();

        auto result = processFile("test_input.txt", "test_output.txt");
        CHECK(result.has_value());
        CHECK(*result == "Histogram successfully written to test_output.txt");

        std::ifstream output("test_output.txt");
        std::stringstream buffer;
        buffer << output.rdbuf();

        CHECK(buffer.str() == "Sentence length: 2 words - Frequency: 1\nSentence length: 4 words - Frequency: 2\n");
    }

    SUBCASE("Invalid input file") {
        auto result = processFile("nonexistent_input.txt", "test_output.txt");
        CHECK(!result.has_value());
    }
}

TEST_CASE("tokenize") {
    SUBCASE("Tokenization of a simple sentence") {
    std::string text = "Hello, world! Welcome to the test.";
    std::vector<std::string> expected = {"hello", "world", "welcome", "to", "the", "test"};
    
    CHECK(tokenize(text) == expected);
    }

    SUBCASE("Tokenization with contractions and punctuation") {
    std::string text = "It's a beautiful day, isn't it?";
    std::vector<std::string> expected = {"it's", "a", "beautiful", "day", "isn't", "it"};

    CHECK(tokenize(text) == expected);
    }
}

TEST_CASE("splitSentences") {
    SUBCASE("Multiple sentence-ending punctuation") {
        std::string text = "Wow! This is amazing. Really?";
        std::vector<std::string> expected = {"Wow!", " This is amazing.", " Really?"};
        CHECK(splitSentences(text) == expected);
    }

    SUBCASE("Leading and trailing spaces") {
        std::string text = "  Hello world.  Another sentence!  ";
        std::vector<std::string> expected = {"  Hello world.", "  Another sentence!"};
        CHECK(splitSentences(text) == expected);
    }
}

TEST_CASE("createHistogram") {
    SUBCASE("Basic histogram") {
        std::vector<std::string> sentences = {"Hello world.", "This is a test!", "How're you?"};
        std::map<int, int> expected = {{2, 2}, {4, 1}};
        CHECK(createHistogram(sentences) == expected);
    }

    SUBCASE("Sentences with different lengths") {
        std::vector<std::string> sentences = {
            "A sentence with five words.", 
            "Short one.", 
            "Another very long sentence with seven words total."
        };
        std::map<int, int> expected = {{5, 1}, {2, 1}, {8, 1}};
        CHECK(createHistogram(sentences) == expected);
    }
}
