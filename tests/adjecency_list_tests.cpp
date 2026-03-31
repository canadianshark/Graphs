#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "graph.h"

TEST_CASE("Adjacency list: basic methods"){
    Graph G(Graph::RepType::ADJACENCY_LIST);
    Graph J(Graph::RepType::ADJACENCY_LIST);

    SECTION("Vertex and edge creation"){
        G.addVertex(1);
        G.addVertex(2);
        G.addVertex(4);
        G.addEdge(1, 2);

        REQUIRE((G.hasVertex(1) && G.hasVertex(2)) == 1);

        REQUIRE(G.hasVertex(1928198) == 0);

        REQUIRE(G.hasEdge(1, 2) == 1);

        REQUIRE(G.hasEdge(1, 4) == 0);

    }

    SECTION("Vertex degrees and counting"){
        J.addVertex(1);
        REQUIRE(J.vertexCount() == 1);
        REQUIRE(J.vertexDeg(1) == 0);
        REQUIRE(J.edgeCount() == 0);
        J.addVertex(2);
        J.addVertex(3);
        J.addVertex(4);
        J.addEdge(1,2);
        J.addEdge(1,3);
        J.addEdge(1,4);

        REQUIRE(J.vertexDeg(1) == 3);
        REQUIRE(J.edgeCount() == 3);

        REQUIRE(J.vertexCount() == 4);
        J.addVertex(2);
        REQUIRE(J.vertexCount() == 4);


    }
}


