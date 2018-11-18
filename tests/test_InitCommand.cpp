#include "catch.hpp"
#include "../InitCommand.hpp"
#include <sys/stat.h>
#include <stdio.h>

SCENARIO( "InitCommand -- create a database", "[InitCommand]" ) {

  InitCommand ic;

  GIVEN( "not created" ) {
    REQUIRE( ic.run().first == true );
  }
  GIVEN( "created" ) {
    REQUIRE( ic.run().first == false );
  }

}
