#include "catch.hpp"
#include "../InitCommand.hpp"
#include <sys/stat.h>

SCENARIO( "create a database", "[InitCommand]" ) {

  GIVEN( "In default directory" ) {
    InitCommand cmd{};

    REQUIRE( cmd.run().first == true );
  }

}
