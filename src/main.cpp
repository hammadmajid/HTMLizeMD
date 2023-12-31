#include "clap.h"
#include "lexer.h"
#include "generator.h"

int main(const int argc, char *argv[]) {
    const Clap clap(argc, argv);
    std::string input_file, output_file;

    const auto args = clap.process_args();
    if (!args.has_value()) {
        switch (args.error()) {
            case ArgsStatus::InvalidNumOfArgs:
                std::cerr << "Error: Expected exactly two arguments";
                break;
            case ArgsStatus::InvalidSourceFile:
                std::cerr << "Error: Couldn't open source file";
                break;
            case ArgsStatus::InvalidOutputFile:
                std::cerr << "Error: Couldn't open output file";
                break;
            case ArgsStatus::HelpFlag:
                return EXIT_SUCCESS;
            case ArgsStatus::VersionFlag:
                std::cout << "v0.1.0" << std::endl;
                return EXIT_SUCCESS;
        }
        std::cerr << "\nSee help with --help option" << std::endl;
        return EXIT_FAILURE;
    }

    input_file = args.value().input_file;
    output_file = args.value().output_file;


    const Lexer lexer(input_file);
    const auto tokens = lexer.tokenize();

    Generator generator(tokens);
    const auto content = generator.translate();

    std::ofstream stream(output_file);

    if (stream.is_open()) {
        stream << content;
    } else {
        std::cerr << "Something went wrong when writing to file" << std::endl;
        exit(EXIT_FAILURE);
    }

    stream.close();

    return EXIT_SUCCESS;
}
