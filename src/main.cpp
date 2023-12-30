#include <iostream>
#include "clap.h"
#include "lexer.h"
#include "generator.h"

int main(const int argc, char *argv[]) {
    auto [input_file, output_file] = Clap::process_args(argc, argv);

    if(!Clap::validate_file(input_file)) {
        std::cout << input_file << " is not a valid file." << std::endl;
        exit(EXIT_FAILURE);
    }

    const Lexer lexer(input_file);
    const auto tokens = lexer.tokenize();

    Generator generator(tokens);
    const auto content = generator.translate();

    std::cout << content << std::endl;

    Clap::create_html_file(content, output_file);

    return EXIT_SUCCESS;
}
