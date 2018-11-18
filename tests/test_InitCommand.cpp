#include "catch.hpp"
#include "../InitCommand.hpp"
#include <string>
#include <vector>

SCENARIO( "InitCommand -- create a database", "[InitCommand]" ) {

  std::vector<std::string> vs;
  InitCommand ic{vs};

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
