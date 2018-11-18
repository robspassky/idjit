#ifndef IDJIT__JOB_HPP
#define IDJIT__JOB_HPP

#include <string>

using namespace std;

struct Job {
  string id = "";
  string name = "";
  string criteria = "";
  string owner = "";
  int importance = 0;
  string assignee = "";
  int state = 0;
  int status = 0;
  int points = 0;
  int deadline = 0;

  Job(int ncols, char **columns, char **data);
  Job(string shortname, string user);
};

#endif /* IDJIT__JOB_HPP */
