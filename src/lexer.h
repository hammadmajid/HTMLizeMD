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

    [[nodiscard]] auto tokenize() const -> std::vector<Token> {
        std::vector<Token> tokens;
        for (auto &line: stream) {
            size_t index = 0;
            while (index < line.size() && (line[index] == '#' || line[index] == '-' || std::isdigit(line[index]))) {
                index++;
            }

            // Skip whitespace after the starting characters
            while (index < line.size() && std::isspace(line[index])) {
                index++;
            }

            if (std::string content = (index < line.size()) ? line.substr(index) : ""; !content.empty()) {
                if (line[0] == '#') {
                    size_t heading_level = 1;
                    while (heading_level <= 6 && line[heading_level] == '#') {
                        heading_level++;
                    }

                    tokens.push_back({
                        static_cast<TokenType>(HeadingLevel1 - 1 + heading_level), content
                    });
                }
                else if (line[0] == '-') {
                    tokens.push_back({UnorderedList, content});
                }
                else if (std::isdigit(line[0])) {
                    tokens.push_back({OrderdList, content});
                }
                else {
                    tokens.push_back({Paragraph, content});
                }
            }
        }

        return tokens;
    }
};

#endif //LEXER_H
