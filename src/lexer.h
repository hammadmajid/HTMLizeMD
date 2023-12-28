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

inline auto tokenize(const std::string &file_path) -> std::vector<Token> {
    std::fstream file_stream(file_path);
    std::vector<Token> tokens;

    if (file_stream.is_open()) {
        std::string line;
        while (std::getline(file_stream, line)) {
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

        file_stream.close();
    } else {
        std::cout << "Something went wrong" << std::endl;
        exit(EXIT_FAILURE);
    }

    return tokens;
}


#endif //LEXER_H
