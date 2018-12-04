#ifndef IDJIT__JOB_HPP
#define IDJIT__JOB_HPP

#include <string>

using namespace std;

class Job {
  public:
    Job(int ncols, char **columns, char **data);
    Job(string shortname, string user);
    void save();

  private:
    string _id = "";
    string _name = "";
    string _criteria = "";
    string _owner = "";
    int _importance = 0;
    string _assignee = "";
    int _state = 0;
    int _status = 0;
    int _points = 0;
    int _deadline = 0;

};

#endif /* IDJIT__JOB_HPP */
