#include <iostream>
#include "clap.h"
#include "lexer.h"
#include "generator.h"

int main(const int argc, char *argv[]) {
    std::string file_path = process_args(argc, argv);

    if(!validate_file(file_path)) {
        std::cout << file_path << " is not a valid file." << std::endl;
        exit(EXIT_FAILURE);
    }

    const Lexer lexer(file_path);
    const auto tokens = lexer.tokenize();

    Generator generator(tokens);
    const auto content = generator.translate();

    std::cout << content << std::endl;

    create_html_file(content, file_path);

    return EXIT_SUCCESS;
}
