#ifndef IDJIT__JOB_HPP
#define IDJIT__JOB_HPP

#include <string>

using namespace std;

/*
string getuuid() {
  default_random_engine dre;
  uniform_int_distribution<long long> dll(0);
  stringstream ss;
  ss << dll(dre);
  return ss.str();
}
*/

struct Job {
  string id;
  string name;
  string criteria;
  string owner;
  int importance = 0;
  string assignee;
  int state = 0;
  int status = 0;
  int points = 0;
  int deadline = 0;

  Job(int ncols, char **columns, char **data);
  Job(string shortname, string user) :
    name(shortname),
    owner(user),
    assignee(user)
  {
    id = "123456";
  }
  Job() {}
};

#endif /* IDJIT__JOB_HPP */
