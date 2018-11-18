#include "catch.hpp"
#include "../Job.hpp"
#include <vector>
#include <string>

SCENARIO( "job -- create a job", "[Job]" ) {

  int ncols = 10;
  const char *columns[] = { "id", "name", "criteria", "owner", "importance", "assignee", "state", "status", "points", "deadline" };
  const char *data[] = { "123456", "catch job data", "here is some criteria for catch", "catchtester", "1", "catchassignee", "57473", "574705", "999", "1010101" };

  GIVEN( "In default directory" ) {
    REQUIRE_NOTHROW( new Job(ncols, (char**)columns, (char**)data) );
  }

}
