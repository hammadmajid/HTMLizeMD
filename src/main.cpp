#include <iostream>
#include "clap.h"
#include "lexer.h"
#include "generator.h"

int main(const int argc, char *argv[]) {
    const Clap clap(argc, argv);
    if (!clap.process_args()) {
        exit(EXIT_FAILURE);
    }

    if (const auto input_source = clap.extract_source_file(); input_source.has_value()) {
        const Lexer lexer(input_source.value());
    }

    auto [input_file, output_file, help] = process_args(argc, argv);

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
