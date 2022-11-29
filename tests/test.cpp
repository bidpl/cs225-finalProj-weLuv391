#include <catch2/catch_test_macros.hpp>
#include "../src/getCleanedData.h"
TEST_CASE("practiceTest", "[weight=1][part=1]") {
  int i = 0;
  getCleanedData();
  REQUIRE( i == 0 );
}