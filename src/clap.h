#ifndef CLAP_H
#define CLAP_H
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <vector>

struct Args {
    std::string input_file;
    std::string output_file;
};

class Clap {
    size_t m_argc;
    std::vector<std::string> m_argv;

    static auto print_help() {
        std::cout << "Convert .md files to .html ones" << std::endl;
        std::cout << std::endl;
        std::cout << "Usage:" << std::endl;
        std::cout << "\tHTMLizeMD <path_to_md_file> <path_to_html_file> [options]" << std::endl;
        std::cout << std::endl;
        std::cout << "\tOptions:" << std::endl;
        std::cout << "\t\t--help | -h        Print this message" << std::endl;
        std::cout << "\t\t--version | -v     Print version info" << std::endl;
    }

    static auto has_extention(const std::string &path, const std::string &extension) -> bool {
        return std::filesystem::exists(path) && std::filesystem::path(path).extension() == extension;
    }
public:
    Clap (const int argc, char * argv[]) : m_argc(argc) {
        for (int i = 0; i < m_argc; i++) {
            m_argv.emplace_back(argv[i]);
        }
    }

    [[nodiscard]] auto process_args() const -> Args {
        for (auto &arg: m_argv) {
            if (arg == "--help" || arg == "-h") {
                print_help();
                exit(EXIT_SUCCESS);
            }
            if (arg == "--version" || arg == "-v") {
                std::cout << "v0.1.0" << std::endl;
                exit(EXIT_SUCCESS);
            }
        }

        if (m_argc != 3) {
            std::cout << "Expected exactly two arguments" << std::endl;
            std::cout << "See --help" << std::endl;
            exit(EXIT_FAILURE);
        }

        if (!has_extention(m_argv.at(1), ".md")) {
            std::cout << "Expected " << m_argv.at(1) <<
                " to be a .md file. See help with --help option." << std::endl;
            exit(EXIT_FAILURE);
        }

        if (!has_extention(m_argv.at(2), ".html")) {
            std::cout << "Expected " << m_argv.at(2) <<
                " to be a .html file. See help with --help option." << std::endl;
            exit(EXIT_FAILURE);
        }

        return Args {
            .input_file = m_argv[1],
            .output_file = m_argv[2]
        };
    }

    static auto create_html_file(const std::string& content, const std::string &output_file_path) {
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
};

#endif //CLAP_H
