#include "Command.hpp"

using namespace std;

Command::Command(Arguments args) : _command{args.command} {}

void Command::run(istream& is, ostream& os, ostream &es) {
  cout << "Running command with " << _command << " command!" << endl;
}

