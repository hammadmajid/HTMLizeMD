#ifndef CLAP_H
#define CLAP_H
#include <string>
#include <fstream>
#include <filesystem>

inline auto process_args(const int argc, char *argv[]) -> std::string {
    if (argc != 2) {
        std::cout << "Expected at least 1 argument found " << argc - 1;
        exit(EXIT_FAILURE);
    }

    return argv[1];
}

inline auto validate_file(const std::string &path) -> bool {
    return std::filesystem::exists(path) && std::filesystem::path(path).extension() == ".md";
}

#endif //CLAP_H
