#include "arguments.h"

#include <stdexcept>
#include "absl/strings/str_split.h"


Arguments::Arguments(int argc, char **argv) {
  if (argc < 2)
    throw std::invalid_argument("no command specified");
  command_ = argv[1];
  for (int i=2; i<argc; i++) {
    if (argv[i][0] != '-')
      args_.push_back(argv[i]);
    else
      handle_option(argv[i]+1);
  }
}

bool Arguments::has(const char *name) {
  return options_.find(name) != options_.end();
}

void Arguments::handle_option(const char *option) {
  std::vector<std::string> v = absl::StrSplit(option, absl::MaxSplits('=', 2));
  if (v.size() > 1)
    options_[v[0]] = v[1];
  else
    options_[v[0]] = "true";
}

