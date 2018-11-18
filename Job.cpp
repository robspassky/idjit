#include "Job.hpp"

#include <map>
#include <string>

using namespace std;

Job::Job(int ncols, char** columns, char** data) {
  map<string, string> result;
  for (int i = 0; i<ncols; i++) {
    result.insert(make_pair(columns[i], data[i]));
  }

  id = result["id"];
  name = result["name"];
  criteria = result["criteria"];
  owner = result["owner"];
  importance = stoi(result["importance"]);
  assignee = result["assignee"];
  state = stoi(result["state"]);
  status = stoi(result["status"]);
  points = stoi(result["points"]);
  deadline = stoi(result["deadline"]);
}
