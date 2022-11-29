#include <catch2/catch_test_macros.hpp>
#include "../src/getCleanedData.h"
TEST_CASE("practiceTest", "[weight=infinity][part=sanitizer]") {
  int i = 0;
  Sanitizer files;
  files.getCleanedData();
  REQUIRE( i == 0 );
}