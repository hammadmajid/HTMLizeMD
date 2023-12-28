#ifndef GENERATOR_H
#define GENERATOR_H
#include "lexer.h"

class Generator {
    std::vector<Token> m_tokens;
    std::string m_content;

    auto generate_tag(const std::string &tag_name, const std::string &content) {
        const std::string tag = "<" + tag_name + ">" + content + "</" + tag_name + ">";
        for (const auto each: tag) {
            m_content.push_back(each);
        }
    }

public:
    explicit Generator(std::vector<Token> tokens) : m_tokens(std::move(tokens)) {
    }

    [[nodiscard]] auto translate() -> std::string {
        for (const auto &[type, value]: m_tokens) {
            if (type == HeadingLevel1) {
                generate_tag("h1", value);
            } else if (type == HeadingLevel2) {
                generate_tag("h2", value);
            } else if (type == HeadingLevel3) {
                generate_tag("h3", value);
            } else if (type == HeadingLevel4) {
                generate_tag("h4", value);
            } else if (type == HeadingLevel5) {
                generate_tag("h5", value);
            } else if (type == HeadingLevel6) {
                generate_tag("h6", value);
            } else if (type == UnorderedList) {
                for (const std::string open_tag = "<ul>"; const auto ch: open_tag) {
                    m_content.push_back(ch);
                }

                generate_tag("li", value);

                for (const std::string close_tag = "</ul>"; const auto ch: close_tag) {
                    m_content.push_back(ch);
                }
            } else if (type == OrderdList) {
                for (const std::string open_tag = "<ol>"; const auto ch: open_tag) {
                    m_content.push_back(ch);
                }

                generate_tag("li", value);

                for (const std::string close_tag = "</ul>"; const auto ch: close_tag) {
                    m_content.push_back(ch);
                }
            } else if (type == Paragraph) {
                generate_tag("p", value);
            }
        }
        return m_content;
    }
};

#endif //GENERATOR_H
