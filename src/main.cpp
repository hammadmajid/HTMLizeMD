#include "clap.h"
#include "lexer.h"
#include "generator.h"

int main(const int argc, char *argv[]) {
    const Clap clap(argc, argv);

    auto [input_file, output_file] = clap.process_args();

    const Lexer lexer(input_file);
    const auto tokens = lexer.tokenize();

    Generator generator(tokens);
    const auto content = generator.translate();

    Clap::create_html_file(content, output_file);

    return EXIT_SUCCESS;
}
