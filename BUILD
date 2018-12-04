CFLAGS = ["-O3", "-std=c++17", "-Wall", "-Wextra"]
LDFLAGS = []

cc_binary(
    name = "idjit", 
    srcs = [
      "main.cc"
    ],
    deps = [
      "arguments"
    ],
    linkopts = LDFLAGS,
    copts = CFLAGS
)

cc_library(
    name = "arguments",
    srcs = [
      "arguments.cc", 
      "arguments.h"
    ],
    copts = CFLAGS
)

cc_test(
    name = "test_arguments",
    srcs = [ 
      "test/test_arguments.cc", 
      "arguments.cc", 
      "arguments.h" 
    ],
    deps = [ 
      "@googletest//:gtest" 
    ],
    copts = CFLAGS
)





cc_library(
    name = "command",
    srcs = ["command.cc", "command.h", "job_command.h", "init_command.h"],
    deps = ["arguments"],
    copts = CFLAGS
)

cc_library(
    name = "job_command",
    srcs = ["job_command.cc", "job_command.h"],
    deps = ["arguments", "command", "job"],
    copts = CFLAGS
)

cc_library(
    name = "init_command",
    srcs = ["init_command.cc", "init_command.h"],
    deps = ["arguments", "command", "db"],
    copts = CFLAGS
)

cc_library(
    name = "job",
    srcs = ["job.cc", "job.h", "sole.h" ],
    deps = ["db"],
    copts = CFLAGS
)

cc_library(
    name = "db",
    srcs = ["db.cc", "db.h"],
    copts = CFLAGS
)

