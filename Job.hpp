#ifndef IDJIT__JOB_HPP
#define IDJIT__JOB_HPP

#include <string>
#include <random>
#include <sstream>

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
  int importance;
  string assignee;
  int state;
  int status;
  int points;
  int deadline;

  Job(string shortname, string user) :
    name(shortname),
    owner(user),
    assignee(user)
  {
    id = "123456";
  }
};

#endif /* IDJIT__JOB_HPP */
