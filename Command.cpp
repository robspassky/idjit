#include "Command.hpp"

using namespace std;

Command::Command(Arguments args) : _count{args.count} {}

void Command::run(istream& is, ostream& os, ostream &es) {
  cout << "Running command with " << _count << " arguments!" << endl;
}

