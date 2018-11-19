#include "Job.hpp"

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
  ss << "'" << job.id << "', ";
  ss << "'" << job.name << "', ";
  ss << "'" << job.criteria << "', ";
  ss << "'" << job.owner << "', ";
  ss << job.importance << ", ";
  ss << "'" << job.assignee << "', ";
  ss << job.state << ", ";
  ss << job.status << ", ";
  ss << job.points << ", ";
  ss << job.deadline << ") ";

  Db db;
  db.execute(ss.str());
}
