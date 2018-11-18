#include "catch.hpp"
#include "../Arguments.hpp"

TEST_CASE( "Argument creation", "[Arguments]" ) {
  const char *argv[]{ "idjit", "init", "." };
  Arguments a{3, (char **)argv};
  REQUIRE( a.command() == "init" );
  REQUIRE( a.args().size() == 1 );
  REQUIRE( a.args()[0] == "." );
}

