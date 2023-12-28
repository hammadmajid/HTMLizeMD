#ifndef CLAP_H
#define CLAP_H
#include <string>
#include <fstream>
#include <filesystem>

struct Args {
    std::string input_file;
    std::string output_file;
};

inline auto process_args(const int argc, char *argv[]) -> Args {
    if (argc != 3) {
        std::cout << "Expected exactly 2 argument found " << argc - 1;
        exit(EXIT_FAILURE);
    }

    return Args {
        .input_file = argv[1],
        .output_file = argv[2]
    };
}

inline auto validate_file(const std::string &path) -> bool {
    return std::filesystem::exists(path) && std::filesystem::path(path).extension() == ".md";
}

inline auto create_html_file(const std::string& content, const std::string &output_file_path) {
    std::ofstream stream(output_file_path);

    if (stream.is_open()) {
        stream << content;
    }
    else {
        std::cout << "Something went wrong" << std::endl;
        exit(EXIT_FAILURE);
    }

    stream.close();
}
#endif //CLAP_H
