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

SCENARIO( "db -- listing / adding jobs", "[Db]" ) {

  remove("test_idjit.db");
  Db db{"test_idjit.db", true};
  db.initialize();
  Job job{"create a test job", "tester"};

  GIVEN( "no jobs are in table" ) {
    REQUIRE( db.list_jobs().size() == 0);
  }

  GIVEN( "one job in table" ) {
    REQUIRE( db.list_jobs().size() == 0 );
    db.upsert_job(job);
    REQUIRE( db.list_jobs().size() == 1 );
  }

}
