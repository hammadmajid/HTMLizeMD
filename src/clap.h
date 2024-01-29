#ifndef CLAP_H
#define CLAP_H
#include <string>
#include <fstream>
#include <filesystem>
#include <variant>
#include <vector>
#include <expected>

struct Args {
    std::string input_file;
    std::string output_file;
    bool help;
};

inline auto process_args(const int argc, char *argv[]) -> Args {
    if (argc != 3) {
        std::cout << "Expected exactly 2 argument found " << argc - 1;
        exit(EXIT_FAILURE);
    }

    return Args{
        .input_file = argv[1],
        .output_file = argv[2]
    };
}

inline auto validate_file(const std::string &path) -> bool {
    return std::filesystem::exists(path) && std::filesystem::path(path).extension() == ".md";
}

inline auto create_html_file(const std::string &content, const std::string &output_file_path) {
    std::ofstream stream(output_file_path);

    if (stream.is_open()) {
        stream << content;
    } else {
        std::cout << "Something went wrong" << std::endl;
        exit(EXIT_FAILURE);
    }

    stream.close();
}

class Clap {
    size_t m_argc;
    std::vector<std::string> m_argv;

    static auto has_extenion(const std::string &path, const std::string &extension) -> bool {
        return std::filesystem::exists(path) && std::filesystem::path(path).extension() == extension;
    }

public:
    Clap(const int argc, char *argv[]) : m_argc(argc) {
        for (int i = 1; i < argc; i++) {
            m_argv.emplace_back(argv[i]);
        }
    }

    [[nodiscard]] auto extract_source_file() const -> std::expected<std::string, error_t>  {
        if (has_extenion(m_argv.at(1), ",md")) {
            return m_argv.at(1);
        }

        return 1;
    }

    [[nodiscard]] auto extract_output_file() const -> std::variant<std::string, error_t> {
        if (has_extenion(m_argv.at(2), ".html")) {
            return m_argv.at(2);
        }

        return -1;
    }

    [[nodiscard]] auto process_args() const -> bool {
        for (const auto &arg: m_argv) {
            if (arg == "--help") {
                std::cout << "Convert Markdown(.md) file to Hypter Text Markup Language(.html) file" << std::endl
                        << std::endl << "Usage:" << std::endl << "\tHTMLizeMD -s source.md -o output.html" << std::endl
                        << std::endl << "Arguments:" << std::endl << "\tsource.md Path to Markdown file" << std::endl
                        << "\toutput.html Path to output HTML" << std::endl;
                return false;
            }
            if (!has_extenion(arg, ".md")) {
                std::cout << "Expected path to .md file. " << arg << " is not valid path" << std::endl;
                return false;
            }
            if (!has_extenion(arg, ".html")) {
                std::cout << "Expected path to .html file. " << arg << " is not valid path" << std::endl;
                return false;
            }
        }
        return true;
    }
};

#endif //CLAP_H
