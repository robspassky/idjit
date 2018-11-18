#include "catch.hpp"
#include "../JobCommand.hpp"
#include "../Db.hpp"
#include <string>
#include <vector>

SCENARIO( "JobCommand -- create a new job", "[JobCommand]" ) {

  remove(".idjit.db");
  Db db{".idjit.db", true};
  db.initialize();

  GIVEN( "job title" ) {
    std::vector<std::string> vs{ {"create a test job"} };
    JobCommand cmd{vs};

    REQUIRE_NOTHROW( cmd.run() );
    REQUIRE( db.list_jobs().size() == 1);
  }

}
