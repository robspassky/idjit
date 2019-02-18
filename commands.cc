#include "commands.h"

#include "db.h"

namespace idjit {

void do_init(std::vector<std::string> args) {
  const char *path = args.size() > 0 ? args[0].c_str() : "";
  Db db { path, true };
  db.initialize();
}

};  // namespace idjit
