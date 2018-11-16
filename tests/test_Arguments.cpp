#include "catch.hpp"
#include "../Arguments.hpp"

TEST_CASE( "Argument creation", "[Arguments]" ) {
  const char *argv[]{ "idjit", "init", "." };
  Arguments args{3, (char **)argv};
  REQUIRE( args.command == "init" );
  REQUIRE( args.args.size() == 1 );
  REQUIRE( args.args[0] == "." );
}

