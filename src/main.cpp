#include <iostream>
#include "clap.h"
#include "lexer.h"
#include "generator.h"

int main(const int argc, char *argv[]) {
    auto [input_file, output_file] = process_args(argc, argv);

    if(!validate_file(input_file)) {
        std::cout << input_file << " is not a valid file." << std::endl;
        exit(EXIT_FAILURE);
    }

    const Lexer lexer(input_file);
    const auto tokens = lexer.tokenize();

    Generator generator(tokens);
    const auto content = generator.translate();

    create_html_file(content, output_file);

    return EXIT_SUCCESS;
}
