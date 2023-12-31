#include <gtest/gtest.h>
#include "clap.h"

TEST(ClapTest, ProcessArgsHelpFlag) {
    const char* argv[] = {"HTMLizeMD", "--help"};
    const Clap clap(2, const_cast<char**>(argv));
    auto result = clap.process_args();

    EXPECT_EQ(ArgsStatus::HelpFlag, result.error());
}

TEST(ClapTest, ProcessArgsVersionFlag) {
    const char* argv[] = {"HTMLizeMD", "--version"};
    const Clap clap(2, const_cast<char**>(argv));
    auto result = clap.process_args();

    EXPECT_EQ(ArgsStatus::VersionFlag, result.error());
}

TEST(ClapTest, ProcessArgsInvalidNumOfArgs) {
    const char* argv[] = {"HTMLizeMD"};
    const Clap clap(1, const_cast<char**>(argv));
    auto result = clap.process_args();

    EXPECT_EQ(ArgsStatus::InvalidNumOfArgs, result.error());
}

TEST(ClapTest, ProcessArgsInvalidSourceFile) {
    const char* argv[] = {"HTMLizeMD", "input.txt", "output.html"};
    const Clap clap(3, const_cast<char**>(argv));
    auto result = clap.process_args();

    EXPECT_EQ(ArgsStatus::InvalidSourceFile, result.error());
}

TEST(ClapTest, ProcessArgsInvalidOutputFile) {
    const char* argv[] = {"HTMLizeMD", "../README.md", "output.txt"};
    const Clap clap(3, const_cast<char**>(argv));
    auto result = clap.process_args();

    EXPECT_EQ(ArgsStatus::InvalidOutputFile, result.error());
}

TEST(ClapTest, ProcessArgsValidArgs) {
    const char* argv[] = {"HTMLizeMD", "../README.md", "output.html"};
    const Clap clap(3, const_cast<char**>(argv));
    const auto result = clap.process_args();

    EXPECT_EQ("input.md", result.value().input_file);
    EXPECT_EQ("output.html", result.value().output_file);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
