#include "Command.hpp"
#include "InitCommand.hpp"
#include "JobCommand.hpp"
#include <stdexcept>

std::unique_ptr<Command> Command::create(const Arguments& args) {

  if (args.command() == "init") {

    return std::make_unique<InitCommand>(args.args());

  } else if (args.command() == "job") {

    return std::make_unique<JobCommand>(args.args());

  } else {

    throw std::invalid_argument("unknown command: " + args.command());

  }

}
