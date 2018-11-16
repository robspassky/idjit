#include "catch.hpp"
#include "../Arguments.hpp"

TEST_CASE( "Argument creation", "[Arguments]" ) {
  const char *argv[]{ "foo", "bar", "zik" };
  Arguments args{3, (char **)argv};
  REQUIRE( args.count == 2 );
}

