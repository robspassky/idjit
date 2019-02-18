CFLAGS = ["-O3", "-std=c++17", "-Wall", "-Wextra"]
LDFLAGS = ["-lsqlite3"]

cc_binary(
    name = "idjit", 
    srcs = [
      "main.cc"
    ],
    deps = [
      "arguments",
      "commands",
      "db"
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
    name = "commands",
    srcs = [
      "commands.cc", 
      "commands.h",
      "db.h"
    ],
    copts = CFLAGS
)

cc_test(
    name = "test_commands",
    srcs = [ 
      "test/test_commands.cc", 
      "commands.cc", 
      "commands.h",
      "db.h"
    ],
    deps = [ 
      "@googletest//:gtest" 
    ],
    copts = CFLAGS
)

cc_library(
    name = "db",
    srcs = [
      "db.cc", 
      "db.h"
    ],
    copts = CFLAGS
)

cc_test(
    name = "test_db",
    srcs = [ 
      "test/test_db.cc", 
      "db.cc", 
      "db.h" 
    ],
    deps = [ 
      "@googletest//:gtest" 
    ],
    copts = CFLAGS
)

