#include "arguments.h"

#include <stdexcept>

namespace {

std::pair<std::string, std::string> parse_option(const char *string) {
  std::string key = string;
  auto pos = key.find_first_of('=');
  if (pos == std::string::npos)
    return { key, "true" };
  else
    return { key.substr(0, pos), key.substr(pos+1) };
}

};  // namespace

namespace idjit {

const Arguments parse_commandline(int argc, const char *argv[]) {
  if (argc < 2)
    throw std::invalid_argument("no command specified");

  Arguments a = { {}, {}, {} };
  for (int i=1; i<argc; i++) {
    if (argv[i][0] != '-') {
      if (a.command == "")
        a.command = argv[i];
      else
        a.args.push_back(argv[i]);
    } else {
      auto p = parse_option(argv[i]+1);
      if (p.first == "")
        a.options["-"] = p.second;
      else
        a.options[p.first] = p.second;
    }
  }

  return a;
}

};  // namespace idjit

std::ostream& operator<<(std::ostream& os, const idjit::Arguments& args) {
  os << "(Arguments) " << args.command;
  os << " [";
  for (auto a : args.args)
    os << a << ",";
  os << "]";
  os << " {";
  for (auto opt : args.options)
    os << opt.first << "=" << opt.second << ",";
  os << "}";
  os << std::endl;
  return os;
}

