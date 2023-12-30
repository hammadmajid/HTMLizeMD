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

    std::ofstream stream(output_file);

    if (stream.is_open()) {
        stream << content;
    } else {
        std::cout << "Something went wrong when writing to file." << std::endl;
        exit(EXIT_FAILURE);
    }

    stream.close();

    return EXIT_SUCCESS;
}
