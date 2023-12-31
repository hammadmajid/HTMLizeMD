#ifndef CLAP_H
#define CLAP_H

#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <expected>

/**
 * @struct Args
 * @brief Structure to store input and output file paths.
 */
struct Args {
    std::string input_file; ///< Path to the input Markdown file.
    std::string output_file; ///< Path to the output HTML file.
};

/**
 * @enum ArgsStatus
 * @brief Enum class representing the status of command line arguments processing.
 */
enum class ArgsStatus {
    HelpFlag,
    ///< Help flag was encountered.
    VersionFlag,
    ///< Version flag was encountered.
    InvalidNumOfArgs,
    ///< Invalid number of command line arguments.
    InvalidSourceFile,
    ///< Input file has an invalid extension.
    InvalidOutputFile ///< Output file has an invalid extension.
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
     * @brief Checks if a file exists and path has a Markdown (.md) extension.
     * @param path The path to the file.
     * @return True if the file exits and path has the Markdown extension, false otherwise.
    */
    static auto validate_source_file(const std::string &path) -> bool {
        return std::filesystem::exists(path) && std::filesystem::path(path).extension() == ".md";
    }

    /**
     * @brief Checks if a file path has an HTML (.html) extension.
     * @param path The path to the file.
     * @return True if the file path has the HTML extension, false otherwise.
    */
    static auto validate_output_file(const std::string &path) -> bool {
        return std::filesystem::path(path).extension() == ".html";
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
     * @brief Processes command line arguments and returns the corresponding status or Args structure.
     * @return An std::expected containing either Args or ArgsStatus.
     */
    [[nodiscard]] auto process_args() const -> std::expected<Args, ArgsStatus> {
        for (const auto &arg: m_argv) {
            if (arg == "--help" || arg == "-h") {
                print_help();
                return std::unexpected{ArgsStatus::HelpFlag};
            }
            if (arg == "--version" || arg == "-v") {
                return std::unexpected{ArgsStatus::VersionFlag};
            }
        }

        if (m_argc != 3) {
            return std::unexpected{ArgsStatus::InvalidNumOfArgs};
        }

        const auto &input_file = m_argv[1]; // expect input file to be at index 1
        const auto &output_file = m_argv[2]; // expect output file to be at index 2

        if (!validate_source_file(input_file)) {
            return std::unexpected{ArgsStatus::InvalidSourceFile};
        }

        if (!validate_output_file(output_file)) {
            return std::unexpected{ArgsStatus::InvalidOutputFile};
        }

        return Args{input_file, output_file};
    }
};

#endif //CLAP_H
