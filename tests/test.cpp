#include <catch2/catch_test_macros.hpp>
#include "../src/getCleanedData.h"
TEST_CASE("practiceTest", "[weight=infinity][part=sanitizer]") {
  int roadCount, interCount, airCount, planeCount, connectingCount;
  Sanitizer files;
  files.getCleanedData();
  interCount = files.getNodeCount(0);
  airCount = files.getNodeCount(1);
  roadCount = files.getEdgeCount(0);
  planeCount = files.getEdgeCount(1);
  connectingCount = files.getEdgeCount(2);

  REQUIRE( roadCount == 21693 );
  REQUIRE( interCount == 21048 );
  REQUIRE( airCount == 29 );
  REQUIRE( planeCount == 406 );
  REQUIRE( connectingCount == 29 );
}