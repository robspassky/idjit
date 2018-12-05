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

  // Customer Test Data
  idjit::Arguments ct_init_  = { "init", {}, {} };
  idjit::Arguments ct_init2_ = { "init", { "/tmp" }, {} };
  idjit::Arguments ct_job_   = { "job", { "some job description" }, {} };

  // Unit Test Data
  idjit::Arguments ut_comm_  = { "test", {}, {} };
  idjit::Arguments ut_com2_  = { "test", { "arg1" }, {{ "opt1", "val1" }} };
  idjit::Arguments ut_com3_  = { "test", {}, {{ "-", "true" }} };
};

TEST_F(ArgumentsTest, CTInit) {
  const char *argv[] = { "idjit", "init" };
  auto args = idjit::parse_commandline(2, argv);
  EXPECT_EQ(args, ct_init_);
}

TEST_F(ArgumentsTest, CTInit2) {
  const char *argv[] = { "idjit", "init", "/tmp" };
  auto args = idjit::parse_commandline(3, argv);
  EXPECT_EQ(args, ct_init2_);
}

TEST_F(ArgumentsTest, CTJob) {
  const char *argv[] = { "idjit", "job", "some job description" };
  auto args = idjit::parse_commandline(3, argv);
  EXPECT_EQ(args, ct_job_);
}

TEST_F(ArgumentsTest, UTComm) {
  const char *argv[] = { "idjit", "test" };
  auto args = idjit::parse_commandline(2, argv);
  EXPECT_EQ(args, ut_comm_);
}

TEST_F(ArgumentsTest, UTCom2) {
  const char *argv[] = { "idjit", "test", "arg1", "-opt1=val1" };
  auto args = idjit::parse_commandline(4, argv);
  EXPECT_EQ(args, ut_com2_);
}

TEST_F(ArgumentsTest, UTCom2a) {
  const char *argv[] = { "idjit", "test", "-opt1=val1", "arg1" };
  auto args = idjit::parse_commandline(4, argv);
  EXPECT_EQ(args, ut_com2_);
}

TEST_F(ArgumentsTest, UTCom2b) {
  const char *argv[] = { "idjit", "test", "-opt1=val1", "arg1", "-opt1=val1" };
  auto args = idjit::parse_commandline(5, argv);
  EXPECT_EQ(args, ut_com2_);
}

TEST_F(ArgumentsTest, UTCom3) {
  const char *argv[] = { "idjit", "test", "-" };
  auto args = idjit::parse_commandline(3, argv);
  EXPECT_EQ(args, ut_com3_);
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

