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

           REQUIRE((G.hasVertex(1) && G.hasVertex(2)) == 1);

           REQUIRE(G.hasVertex(1928198) == 0);

           REQUIRE(G.hasEdge(1, 2) == 1);

           REQUIRE(G.hasEdge(1, 4) == 0);

           REQUIRE(G.hasEdge(1,1) == 1);

       }

       Graph J(GraphType);

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

           J.addEdge(1,1);
           REQUIRE(J.edgeCount() == 3);

           REQUIRE(J.vertexCount() == 4);
           J.addVertex(2);
           REQUIRE(J.vertexCount() == 4);

           J.addEdge(1,1);



       }

       Graph K(GraphType);

       SECTION("Vertex and edge deletion"){
           K.addEdge(1,2);

           REQUIRE(K.vertexCount() == 2);
           REQUIRE(K.edgeCount() == 1);

           K.removeEdge(1, 2);

           REQUIRE(K.edgeCount() == 0);

           K.addEdge(1,3);
           K.addEdge(3,5);

           K.removeVertex(3);

           REQUIRE(K.edgeCount() == 0);
           REQUIRE(K.vertexCount() == 3);


       }


   }


}


