CFLAGS = ["-O3", "-std=c++17", "-Wall", "-Wextra"]

cc_binary(
    name = "idjit", 
    srcs = ["main.cc"],
    deps = ["arguments", "command"],
    linkopts = ["-lsqlite3"],
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

cc_library(
    name = "arguments",
    srcs = ["arguments.cc", "arguments.h"],
    deps = [ "@abseil_cpp//absl/strings" ],
    copts = CFLAGS
)

cc_test(
    name = "arguments_test",
    srcs = [ "arguments_test.cc", "arguments.cc", "arguments.h" ],
    deps = [ "@abseil_cpp//absl/strings:strings", "@googletest//:gtest" ],
)

