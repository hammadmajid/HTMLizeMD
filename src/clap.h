#ifndef CLAP_H
#define CLAP_H

#include <iostream>
#include <string>
#include <filesystem>
#include <vector>

/**
 * @struct Args
 * @brief Structure to store input and output file paths.
 */
struct Args {
    std::string input_file; ///< Path to the input Markdown file.
    std::string output_file; ///< Path to the output HTML file.
};

/**
 * @class Clap
 * @brief Command Line Argument Processor for converting .md files to .html.
 */
class Clap {
    size_t m_argc; ///< Number of command line arguments.
    std::vector<std::string> m_argv; ///< Vector to store command line arguments.

    /**
     * @brief Prints help information for using the program.
     */
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

    /**
     * @brief Checks if a file has a specific extension.
     * @param path The path to the file.
     * @param extension The expected file extension.
     * @return True if the file has the specified extension, false otherwise.
     */
    static auto has_extension(const std::string &path, const std::string &extension) -> bool {
        return std::filesystem::exists(path) && std::filesystem::path(path).extension() == extension;
    }

public:
    /**
     * @brief Constructor for Clap class.
     * @param argc Number of command line arguments.
     * @param argv Array of command line arguments.
     */
    Clap(const int argc, char *argv[]) : m_argc(argc), m_argv(argv, argv + argc) {
    }

    /**
     * @brief Processes command line arguments and returns Args structure.
     * @return Args structure containing input and output file paths.
     */
    [[nodiscard]] auto process_args() const -> Args {
        for (const auto &arg: m_argv) {
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

        if (!has_extension(m_argv.at(1), ".md")) {
            std::cout << "Expected " << m_argv.at(1) <<
                    " to be a .md file. See help with --help option." << std::endl;
            exit(EXIT_FAILURE);
        }

        if (!has_extension(m_argv.at(2), ".html")) {
            std::cout << "Expected " << m_argv.at(2) <<
                    " to be a .html file. See help with --help option." << std::endl;
            exit(EXIT_FAILURE);
        }

        return Args{
            .input_file = m_argv[1],
            .output_file = m_argv[2]
        };
    }
};

#endif //CLAP_H
