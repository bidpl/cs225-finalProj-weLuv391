#include <catch2/catch_test_macros.hpp>
#include "graph.h"

TEST_CASE("practiceTest", "[weight=1][part=1]") {
 int i =0;

  REQUIRE( i == 0 );
}

TEST_CASE("Basic BFS iteration", "[part=bfs]") {
  Graph testGraph;

  for(int i = 0; i < 5; ++i) {
    testGraph.insertNode(i, std::pair<double, double>());
  }

  testGraph.insertEdge(0, 0, 1, 0, 0);
  testGraph.insertEdge(1, 3, 1, 0, 0);
  testGraph.insertEdge(2, 3, 0, 0, 0);
  testGraph.insertEdge(3, 1, 2, 0, 0);
  testGraph.insertEdge(4, 4, 2, 0, 0);
  testGraph.insertEdge(5, 3, 4, 0, 0);

  std::vector<int> visitOrder;
  std::vector<int> ans = {0, 1, 3, 2, 4};

  for(Graph::Iterator it = testGraph.iterAt(0); it != testGraph.end(); ++it) {
    visitOrder.push_back((*it).ID);
  }

  REQUIRE(visitOrder == ans);
}