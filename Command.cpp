#include "Command.hpp"
#include "InitCommand.hpp"
#include <stdexcept>

std::unique_ptr<Command> Command::create(const Arguments& args) {

  if (args.command() == "init") {

    return std::make_unique<InitCommand>(args.args());

  } else {

    throw std::invalid_argument("unknown command: " + args.command());

  }

}
