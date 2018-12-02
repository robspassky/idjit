#include "Job.hpp"
#include "Db.hpp"

#include <map>
#include <string>
#include "sole.hpp"

using namespace std;

Job::Job(string name, string user) : _name(name), _owner(user), _assignee(user) {
  _id = sole::uuid4().str();
}

Job::Job(int ncols, char** columns, char** data) {
  map<string, string> result;
  for (int i = 0; i<ncols; i++) {
    result.insert(make_pair(columns[i], data[i]));
  }

  _id = result["id"];
  _name = result["name"];
  _criteria = result["criteria"];
  _owner = result["owner"];
  _importance = stoi(result["importance"]);
  _assignee = result["assignee"];
  _state = stoi(result["state"]);
  _status = stoi(result["status"]);
  _points = stoi(result["points"]);
  _deadline = stoi(result["deadline"]);
}

void Job::save() {
  std::stringstream ss;
  ss << R"(
  INSERT OR REPLACE INTO jobs('id', 'name', 'criteria', 'owner', 'importance', 'assignee', 'state', 'status', 'points', 'deadline')
  )";

  ss << "  VALUES( ";
  ss << "'" << _id << "', ";
  ss << "'" << _name << "', ";
  ss << "'" << _criteria << "', ";
  ss << "'" << _owner << "', ";
  ss << _importance << ", ";
  ss << "'" << _assignee << "', ";
  ss << _state << ", ";
  ss << _status << ", ";
  ss << _points << ", ";
  ss << _deadline << ") ";

  Db db;
  db.execute(ss.str());
}
