#include "catch.hpp"
#include "graph.h"
#include "serializer.h"
#include <fstream>
#include <string>
#include <iostream>

TEST_CASE("DotSerializer tests_", "[serializer]") {
    std::cout << "=== SERIALIZER TESTS RUNNING ===" << std::endl;

    Graph G(Graph::RepType::ADJACENCY_LIST);
    G.addEdge(1, 2);

    DotSerializer serializer("Test");
    serializer.serialize(G, "test.dot");

    std::cout << "File test.dot should be created" << std::endl;

    REQUIRE(std::ifstream("test.dot").good());
}


TEST_CASE("DotSerializer tests", "[serializer]") {
    std::vector<Graph::RepType> types{Graph::RepType::ADJACENCY_LIST};

    for (auto GraphType : types) {
        Graph G(GraphType);

        SECTION("Serialize empty graph") {
            DotSerializer serializer("EmptyGraph");
            serializer.serialize(G, "test_empty.dot");

        }

        SECTION("Serialize path graph") {
            Graph path = Graph::create_path_graph(5, GraphType);
            DotSerializer serializer("PathGraph");
            serializer.serialize(path, "test_path.dot");

        }

        SECTION("Serialize complete graph") {
            Graph complete = Graph::create_complete_graph(4, GraphType);
            DotSerializer serializer("CompleteGraph");
            serializer.serialize(complete, "test_complete.dot");
        }

        SECTION("Serialize cycle graph") {
            Graph cycle = Graph::create_cycle_graph(5, GraphType);
            DotSerializer serializer("CycleGraph");
            serializer.serialize(cycle, "test_cycle.dot");

        }

        SECTION("Serialize star graph") {
            Graph star = Graph::create_star_graph(5, GraphType);
            DotSerializer serializer("StarGraph");
            serializer.serialize(star, "test_star.dot");

        }

        SECTION("Custom graph name") {
            DotSerializer serializer("CustomName");
            G.addEdge(1, 2);
            serializer.serialize(G, "test_custom.dot");
        }

    }
}

