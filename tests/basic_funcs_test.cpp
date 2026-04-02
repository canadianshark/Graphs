#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "graph.h"
#include "vector"

TEST_CASE("Basic graph methods", "[base]"){
    std::vector<Graph::RepType> types{Graph::RepType::ADJACENCY_LIST};

    for(auto GraphType : types){
        Graph G(GraphType);

        SECTION("Vertex and edge creation"){
            G.addVertex(1);
            G.addVertex(2);
            G.addVertex(4);
            G.addEdge(1, 2);

            REQUIRE(G.hasVertex(1));
            REQUIRE(G.hasVertex(2));
            REQUIRE(G.hasVertex(4));
            REQUIRE_FALSE(G.hasVertex(1928198));

            REQUIRE(G.hasEdge(1, 2));
            REQUIRE_FALSE(G.hasEdge(1, 4));

            REQUIRE_FALSE(G.hasEdge(1, 1));

            Graph G2(GraphType);
            G2.addEdge(10, 20);
            REQUIRE(G2.hasVertex(10));
            REQUIRE(G2.hasVertex(20));
            REQUIRE(G2.hasEdge(10, 20));
            REQUIRE(G2.hasEdge(20, 10));

            Graph G3(GraphType);
            G3.addVertex(5);
            G3.addVertex(5);
            REQUIRE(G3.vertexCount() == 1);

            Graph G4(GraphType);
            G4.addEdge(1, 2);
            G4.addEdge(1, 2);
            G4.addEdge(2, 1);
            REQUIRE(G4.edgeCount() == 1);
        }

        Graph J(GraphType);

        SECTION("Vertex degrees and counting") {
            J.addVertex(1);
            REQUIRE(J.vertexCount() == 1);
            REQUIRE(J.vertexDeg(1) == 0);
            REQUIRE(J.edgeCount() == 0);

            J.addVertex(2);
            J.addVertex(3);
            J.addVertex(4);
            J.addEdge(1, 2);
            J.addEdge(1, 3);
            J.addEdge(1, 4);

            REQUIRE(J.vertexDeg(1) == 3);
            REQUIRE(J.vertexDeg(2) == 1);
            REQUIRE(J.vertexDeg(3) == 1);
            REQUIRE(J.vertexDeg(4) == 1);
            REQUIRE(J.edgeCount() == 3);

            J.addEdge(1, 1);
            REQUIRE(J.edgeCount() == 3);
            REQUIRE(J.vertexDeg(1) == 3);

            REQUIRE(J.vertexCount() == 4);

            J.addVertex(2);
            REQUIRE(J.vertexCount() == 4);

            REQUIRE(J.vertexDeg(999) == 0);
        }

        Graph K(GraphType);

        SECTION("Vertex and edge deletion"){
            K.addEdge(1,2);
            REQUIRE(K.vertexCount() == 2);
            REQUIRE(K.edgeCount() == 1);


            K.removeEdge(1, 2);
            REQUIRE(K.edgeCount() == 0);
            REQUIRE_FALSE(K.hasEdge(1, 2));
            REQUIRE_FALSE(K.hasEdge(2, 1));

            K.removeEdge(1, 2);
            REQUIRE(K.edgeCount() == 0);

            K.addEdge(1,3);
            K.addEdge(3,5);
            K.addEdge(1,4);
            K.addEdge(2,3);
            REQUIRE(K.edgeCount() == 4);


            K.removeVertex(3);
            REQUIRE_FALSE(K.hasVertex(3));
            REQUIRE_FALSE(K.hasEdge(1, 3));
            REQUIRE_FALSE(K.hasEdge(3, 5));
            REQUIRE_FALSE(K.hasEdge(2, 3));
            REQUIRE(K.hasEdge(1, 4));
            REQUIRE(K.edgeCount() == 1);
            REQUIRE(K.vertexCount() == 4);


            K.removeVertex(999);
            REQUIRE(K.vertexCount() == 4);

            Graph K2(GraphType);
            K2.addEdge(1,2);
            K2.addEdge(2,3);
            K2.addEdge(3,1);
            K2.removeVertex(1);
            REQUIRE_FALSE(K2.hasVertex(1));
            REQUIRE_FALSE(K2.hasEdge(1,2));
            REQUIRE_FALSE(K2.hasEdge(1,3));
            REQUIRE(K2.hasEdge(2,3));
            REQUIRE(K2.vertexCount() == 2);
            REQUIRE(K2.edgeCount() == 1);
        }

        Graph L(GraphType);

        SECTION("Neighbours retrieval"){
            auto empty_neighbours = L.getNeighbours(1);
            REQUIRE(empty_neighbours.empty());

            L.addEdge(1,2);
            L.addEdge(1,3);
            L.addEdge(1,4);
            L.addEdge(2,5);

            auto neighbours_1 = L.getNeighbours(1);
            REQUIRE(neighbours_1.size() == 3);
            REQUIRE(neighbours_1.count(2) == 1);
            REQUIRE(neighbours_1.count(3) == 1);
            REQUIRE(neighbours_1.count(4) == 1);

            auto neighbours_2 = L.getNeighbours(2);
            REQUIRE(neighbours_2.size() == 2);
            REQUIRE(neighbours_2.count(1) == 1);
            REQUIRE(neighbours_2.count(5) == 1);

            auto neighbours_999 = L.getNeighbours(999);
            REQUIRE(neighbours_999.empty());

            L.removeVertex(1);
            auto neighbours_2_after = L.getNeighbours(2);
            REQUIRE(neighbours_2_after.size() == 1);
            REQUIRE(neighbours_2_after.count(5) == 1);
            REQUIRE_FALSE(neighbours_2_after.count(1));
        }

        Graph M(GraphType);

        SECTION("Complex operations sequence"){
            M.addEdge(1, 2);
            M.addEdge(2, 3);
            M.removeVertex(2);
            M.addEdge(1, 4);
            M.addVertex(5);
            M.addEdge(4, 5);
            M.removeEdge(1, 4);

            REQUIRE(M.hasVertex(1));
            REQUIRE(M.hasVertex(4));
            REQUIRE(M.hasVertex(5));
            REQUIRE_FALSE(M.hasVertex(2));
            REQUIRE_FALSE(M.hasEdge(1, 2));
            REQUIRE_FALSE(M.hasEdge(1, 4));
            REQUIRE(M.hasEdge(4, 5));
            REQUIRE(M.edgeCount() == 1);

            M.addEdge(1, 2);
            REQUIRE(M.hasVertex(2));
            REQUIRE(M.hasEdge(1, 2));
            REQUIRE(M.edgeCount() == 2);
        }


        Graph O(GraphType);

        SECTION("Graph invariants"){
            O.addEdge(1, 2);
            O.addEdge(2, 3);
            O.addEdge(3, 4);
            O.addEdge(4, 5);
            O.addEdge(1, 5);

            size_t degree_sum = O.vertexDeg(1) + O.vertexDeg(2) + O.vertexDeg(3) +
                                O.vertexDeg(4) + O.vertexDeg(5);
            REQUIRE(degree_sum == 2 * O.edgeCount());

            REQUIRE(O.hasEdge(1, 2));
            REQUIRE(O.hasEdge(2, 1));

            O.removeEdge(1, 2);
            REQUIRE_FALSE(O.hasEdge(1, 2));
            REQUIRE_FALSE(O.hasEdge(2, 1));
        }


    }
}

