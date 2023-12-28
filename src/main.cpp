#include <iostream>
#include "clap.h"

int main(const int argc, char *argv[]) {
    const std::string file_path = process_args(argc, argv);

    if(!validate_file(file_path)) {
        std::cout << file_path << " is not a valid file." << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "ok: " << file_path << std::endl;

    return 0;
}
