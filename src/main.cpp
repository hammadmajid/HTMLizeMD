#include <iostream>
#include "clap.h"
#include "lexer.h"
#include "generator.h"

int main(const int argc, char *argv[]) {
    Args args = process_args(argc, argv);

    if(!validate_file(args.input_file)) {
        std::cout << args.input_file << " is not a valid file." << std::endl;
        exit(EXIT_FAILURE);
    }

    const Lexer lexer(args.input_file);
    const auto tokens = lexer.tokenize();

    Generator generator(tokens);
    const auto content = generator.translate();

    std::cout << content << std::endl;

    create_html_file(content, args.output_file);

    return EXIT_SUCCESS;
}
