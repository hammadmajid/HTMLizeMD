#ifndef LEXER_H
#define LEXER_H
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

enum TokenType {
    // Line starts with #
    HeadingLevel1,
    // Line starts with ##
    HeadingLevel2,
    // Line starts with ###
    HeadingLevel3,
    // Line starts with ####
    HeadingLevel4,
    // Line starts with #####
    HeadingLevel5,
    // Line starts with ######
    HeadingLevel6,
    // Line starts with -
    UnorderedList,
    // Line starts with <integer>.
    OrderdList,
    // Default
    Paragraph,
};

struct Token {
    TokenType type;
    std::string value;
};



class Lexer {
    std::vector<std::string> stream;

public:
    explicit Lexer(const std::string& file_path) {
        if(std::fstream file_stream(file_path); file_stream.is_open()) {
            std::string line;
            while (std::getline(file_stream, line)) {
                stream.emplace_back(line);
            }
        }
        else {
            std::cout << "Something went wrong" << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    auto tokenize() -> std::vector<Token> {
        std::vector<Token> tokens;
        for (auto &line: stream) {
            if (const char first_char = line[0]; first_char == '#') {
                size_t heading_level = 1;
                while (heading_level <= 6 && line[heading_level] == '#') {
                    heading_level++;
                }

                tokens.push_back({
                      static_cast<TokenType>(heading_level - 1 + heading_level), line
                });
            }
            else if (first_char == '-') {
                tokens.push_back({UnorderedList, line});
            }
            else if (std::isdigit(first_char)) {
                tokens.push_back({OrderdList, line});
            }
            else {
                tokens.push_back({Paragraph, line});
            }
        }

        return tokens;
    }
};

#endif //LEXER_H
