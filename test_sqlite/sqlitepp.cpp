#include "../sqlitepp.hpp"
#include <iostream>

int main(int argc, char** argv) {

  try {

    sqlite::db rdb = sqlite::create("test.db");
    sqlite::db odb = sqlite::open("test.db");

  } catch (const exception& e) {

    std::cerr << "Exception caught: " << e.what() << std::endl;

  }

}

