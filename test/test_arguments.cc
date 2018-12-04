#include "arguments.h"
#include "gtest/gtest.h"

#include <stdexcept>

namespace {

class ArgumentsTest : public ::testing::Test {
 protected:
  ArgumentsTest() { /* setup */ }
  ~ArgumentsTest() override { /* teardown */ }
  void SetUp() override { /* more setup */ }
  void TearDown() override { /* more teardown */ }
};

TEST_F(ArgumentsTest, InitCommand) {
  const char *argv[]{ "idjit", "init", "/tmp" };
  auto args = idjit::parse_commandline(3, argv);

  EXPECT_EQ(args.command, "init");
  EXPECT_EQ(args.args[0], "/tmp");
  EXPECT_EQ(args.args.size(), 1);
  EXPECT_EQ(args.options.size(), 0);
}

TEST_F(ArgumentsTest, HandleOptions) {
  const char *argv[]{ "idjit", "test", "-foo=bar", "-d" };
  auto args = idjit::parse_commandline(4, argv);
  EXPECT_EQ(args.command, "test");
  EXPECT_EQ(args.args.size(), 0);
  EXPECT_EQ(args.options.size(), 2);
  EXPECT_NE(args.options.find("d"), args.options.end());
  EXPECT_NE(args.options.find("foo"), args.options.end());
  EXPECT_EQ(args.options["foo"], "bar");
}

TEST_F(ArgumentsTest, NoValue) {
  const char *argv[]{ "idjit", "test", "-d" };
  auto args = idjit::parse_commandline(4, argv);
  EXPECT_NE(args.options.find("d"), args.options.end());
  EXPECT_EQ(args.options["d"], "true");
}

TEST_F(ArgumentsTest, EmptyOption) {
  const char *argv[]{ "idjit", "test", "-" };
  auto args = idjit::parse_commandline(3, argv);
  EXPECT_EQ(args.options["-"], "true");
}

TEST_F(ArgumentsTest, NoCommand) {
  const char *argv[]{ "idjit" };
  ASSERT_THROW(idjit::parse_commandline(1, argv), std::invalid_argument);
}

};  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

