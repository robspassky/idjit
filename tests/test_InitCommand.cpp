#include "catch.hpp"
#include "../InitCommand.hpp"
#include <sys/stat.h>
#include <stdio.h>

SCENARIO( "InitCommand -- create a database", "[InitCommand]" ) {

  InitCommand ic;

  GIVEN( "not created" ) {
    bool threw = false;
    try { ic.run(); } catch (std::exception e) { threw = true; }
    REQUIRE( threw == false );
  }
  GIVEN( "created" ) {
    bool threw = false;
    try { ic.run(); } catch (std::exception e) { threw = true; }
    REQUIRE( threw == true );
  }

}
