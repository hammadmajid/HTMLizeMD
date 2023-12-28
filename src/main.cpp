#include <iostream>
#include "clap.h"
#include "lexer.h"

int main(const int argc, char *argv[]) {
    const std::string file_path = process_args(argc, argv);

    if(!validate_file(file_path)) {
        std::cout << file_path << " is not a valid file." << std::endl;
        exit(EXIT_FAILURE);
    }

    const auto tokens = tokenize(file_path);

    for (const auto &[type, value]: tokens) {
        std::cout << type << " " << value << std::endl;
    }

    return 0;
}
