cc_binary(
    name = "idjit", 
    srcs = glob(include=["*.cc", "*.h", "*.cpp", "*.hpp" ], exclude=[ "arguments_*"]),
    deps = ["arguments"],
    linkopts = ["-lsqlite3",]
)

cc_library(
    name = "arguments",
    srcs = ["arguments.cc", "arguments.h"],
    deps = [ "@abseil_cpp//absl/strings" ],
    copts = ["-O3", "-std=c++17", "-Wall", "-Wextra"]
)

cc_test(
    name = "arguments_test",
    srcs = [ "arguments_test.cc", "arguments.cc", "arguments.h" ],
    deps = [ "@abseil_cpp//absl/strings:strings", "@googletest//:gtest" ],
)

