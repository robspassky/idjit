#include "JobCommand.hpp"
#include "Job.hpp"
#include <stdexcept>

using namespace std;

JobCommand::JobCommand(const std::vector<std::string>& args) {
  switch (args.size()) {
    case 1:
      _name = args[0];
      break;
    case 0:
      throw std::invalid_argument("invalid number of arguments passed to 'job' creation");
  }
}

void JobCommand::run() {
  Job job{_name, "anonymous"};
  job.save();
}

