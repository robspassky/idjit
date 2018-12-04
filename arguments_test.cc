#include "arguments.h"

#include "gtest/gtest.h"

namespace {

class ArgumentsTest : public ::testing::Test {
 protected:
  ArgumentsTest() { /* setup */ }
  ~ArgumentsTest() override { /* teardown */ }
  void SetUp() override { /* more setup */ }
  void TearDown() override { /* more teardown */ }
};

TEST_F(ArgumentsTest, MyCreation) {
  const char *argv[]{ "idjit", "init", "." };
  Arguments a{3, const_cast<char **>(argv)};
  EXPECT_EQ(a.command(), "init");
  EXPECT_EQ(a.args().size(), 1);
  EXPECT_EQ(a.args()[0], ".");
}

TEST_F(ArgumentsTest, HandleOptions) {
  const char *argv[]{ "idjit", "test", "-foo=bar", "-d" };
  Arguments a{4, const_cast<char **>(argv)};
  EXPECT_EQ(a.has("d"), true);
}

};  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

