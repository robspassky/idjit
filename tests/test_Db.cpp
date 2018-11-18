#include "catch.hpp"
#include "../Db.hpp"

SCENARIO( "db -- create a database", "[Db]" ) {

  GIVEN( "In default directory" ) {
    remove(".idjit.db");
    WHEN( "not creating, does not exist" ) {
      bool threw = false;
      try { Db db(".idjit.db", false); } catch (const std::exception& e) { threw = true; }
      REQUIRE( threw == true );
    }
    WHEN( "creating, does not exist" ) {
      bool threw = false;
      try { Db db(".idjit.db", true); } catch (const std::exception& e) { threw = true; }
      REQUIRE( threw == false );
    }
    WHEN( "creating, does exist" ) {
      bool threw = false;
      try { Db db(".idjit.db", false); } catch (const std::exception& e) { threw = true; }
      REQUIRE( threw == true );
    }
    WHEN( "not creating, does exist" ) {
      bool threw = false;
      try { Db db(".idjit.db", true); } catch (const std::exception& e) { threw = true; }
      REQUIRE( threw == false );
    }
  }

}
