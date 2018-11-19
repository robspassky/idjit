#include "../sqlitepp.hpp"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct widget {
  string id;
  string name;
  int number;
  widget(string a, string b, int c) : id(a), name(b), number(c) {}
};

ostream& operator<<(ostream& os, const widget& w) {
  os << "{ " << w.id << ", " << w.name << ", " << w.number << " }";
  return os;
}

class widget_list : public sqlite::stmt {
  private:
    vector<widget> _widgets;

  public:
    widget_list() : stmt("SELECT * FROM 'widgets'") { }

    vector<widget> widgets() { return _widgets; }

    void process(map<string, string>& row) {
      widget w(row["id"], row["name"], stoi(row["number"]));
      _widgets.push_back(w);
    }
};

void initialize(sqlite::db& odb) {
  string sql = R"(
  CREATE TABLE 'widgets' (
    id TEXT PRIMARY KEY,
    name TEXT,
    number INTEGER
  )
  )";

  odb.execute(sql);
}

void populate(sqlite::db& odb) {
  string sql = R"(
  INSERT INTO 'widgets' (id, name, number) VALUES ('111', 'tommy', 111);
  INSERT INTO 'widgets' (id, name, number) VALUES ('222', 'sal', 222);
  INSERT INTO 'widgets' (id, name, number) VALUES ('333', 'mitch', 333);
  INSERT INTO 'widgets' (id, name, number) VALUES ('444', 'eric', 444);
  )";

  odb.execute(sql);
}

void list(sqlite::db& odb) {
  widget_list w;
  odb.execute(&w);

  for (auto w : w.widgets())
    cout << w << endl;
}

int main(int argc, char** argv) {

  try {

    remove("test.db");

    sqlite::db rdb = sqlite::create("test.db");
    sqlite::db odb = sqlite::open("test.db");

    initialize(odb);
    populate(odb);
    list(odb);

  } catch (const exception& e) {

    cerr << "Exception caught: " << e.what() << endl;

  }

}

