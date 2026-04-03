#include "catch.hpp"
#include "graph.h"
#include "dfs.h"

TEST_CASE("Complete Graph Generator Invariants", "[generator][complete]") {
    auto n = GENERATE(2, 5, 10);
    auto rep = Graph::RepType::ADJACENCY_LIST;

    Graph g = Graph::create_complete_graph(n, rep);

    REQUIRE(g.vertexCount() == (size_t)n);
    REQUIRE(g.edgeCount() == (size_t)(n * (n - 1) / 2));

    for (size_t v : g.getAllVertices()) {
        REQUIRE(g.vertexDeg(v) == (size_t)(n - 1));
    }
}

TEST_CASE("Complete Bipartite Graph Generator Invariants", "[generator][bipartite]") {
    auto params = GENERATE(std::make_pair(2, 2), std::make_pair(3, 5));
    size_t n = params.first;
    size_t m = params.second;
    auto rep = Graph::RepType::ADJACENCY_LIST;

    Graph g = Graph::create_compl_bipartite(n, m, rep);

    REQUIRE(g.vertexCount() == n + m);
    REQUIRE(g.edgeCount() == n * m);

    size_t partN = 0, partM = 0;
    for (size_t v : g.getAllVertices()) {
        if (g.vertexDeg(v) == m) partN++;
        else if (g.vertexDeg(v) == n) partM++;
    }
    REQUIRE(partN == n);
    REQUIRE(partM == m);
}

TEST_CASE("Tree Generator Invariants", "[generator][tree]") {
    auto n = GENERATE(2, 10, 50);
    auto rep = Graph::RepType::ADJACENCY_LIST;

    Graph g = Graph::create_tree_graph(n, rep);


    SECTION("Vertex and Edge Count") {
        REQUIRE(g.vertexCount() == (size_t)n);
        REQUIRE(g.edgeCount() == (size_t)(n - 1));
    }

    SECTION("Global Connectivity") {
        Graph component = g.get_component_subgraph(0);
        REQUIRE(component.vertexCount() == (size_t)n);
    }

    SECTION("Acyclicity Check") {
        bool hasCycle = false;
        DFS dfs(g, std::make_unique<CycleDetectorVisitor>(hasCycle));
        dfs.traverse();

        REQUIRE_FALSE(hasCycle);
    }
}

TEST_CASE("Star Graph Invariants", "[generator][star]") {
    auto n = GENERATE(3, 10, 50);
    Graph g = Graph::create_star_graph(n, Graph::RepType::ADJACENCY_LIST);

    SECTION("Structure and Degrees") {
        REQUIRE(g.vertexCount() == (size_t)n);
        REQUIRE(g.edgeCount() == (size_t)(n - 1));

        size_t centerCount = 0;
        size_t leafCount = 0;
        for (size_t v : g.getAllVertices()) {
            size_t deg = g.vertexDeg(v);
            if (deg == (size_t)(n - 1)) centerCount++;
            else if (deg == 1) leafCount++;
        }
        REQUIRE(centerCount == 1);
        REQUIRE(leafCount == (size_t)(n - 1));
    }

    SECTION("Acyclicity") {
        bool hasCycle = false;
        DFS dfs(g, std::make_unique<CycleDetectorVisitor>(hasCycle));
        dfs.traverse();
        REQUIRE_FALSE(hasCycle);
    }
}

TEST_CASE("Cycle Graph Invariants", "[generator][cycle]") {
    auto n = GENERATE(3, 10, 25);
    Graph g = Graph::create_cycle_graph(n, Graph::RepType::ADJACENCY_LIST);

    SECTION("Basic Invariants") {
        REQUIRE(g.vertexCount() == (size_t)n);
        REQUIRE(g.edgeCount() == (size_t)n);
        for (size_t v : g.getAllVertices()) {
            REQUIRE(g.vertexDeg(v) == 2);
        }
    }

    SECTION("Cycle detection") {
        bool hasCycle = false;
        DFS dfs(g, std::make_unique<CycleDetectorVisitor>(hasCycle));
        dfs.traverse();
        REQUIRE(hasCycle); // Цикл обязан присутствовать
    }
}

TEST_CASE("Path Graph Invariants", "[generator][path]") {
    auto n = GENERATE(2, 10, 40);
    Graph g = Graph::create_path_graph(n, Graph::RepType::ADJACENCY_LIST);

    SECTION("Structure") {
        REQUIRE(g.vertexCount() == (size_t)n);
        REQUIRE(g.edgeCount() == (size_t)(n - 1));

        size_t ends = 0;
        size_t middle = 0;
        for (size_t v : g.getAllVertices()) {
            if (g.vertexDeg(v) == 1) ends++;
            else if (g.vertexDeg(v) == 2) middle++;
        }

        REQUIRE(ends == 2);
        REQUIRE(middle == (size_t)(n - 2));
    }

    SECTION("Acyclicity") {
        bool hasCycle = false;
        DFS dfs(g, std::make_unique<CycleDetectorVisitor>(hasCycle));
        dfs.traverse();
        REQUIRE_FALSE(hasCycle);
    }
}

TEST_CASE("Wheel Graph Invariants", "[generator][wheel]") {
    auto n = GENERATE(4, 10, 20);
    Graph g = Graph::create_wheel_graph(n, Graph::RepType::ADJACENCY_LIST);

    SECTION("Structure and Degrees") {
        REQUIRE(g.vertexCount() == (size_t)n);
        REQUIRE(g.edgeCount() == (size_t)(2 * (n - 1)));

        size_t hubCount = 0;
        size_t rimCount = 0;
        for (size_t v : g.getAllVertices()) {
            size_t deg = g.vertexDeg(v);
            if (deg == (size_t)(n - 1)) hubCount++;
            else if (deg == 3) rimCount++;
        }
        REQUIRE(hubCount == 1);
        REQUIRE(rimCount == (size_t)(n - 1));
    }
}

TEST_CASE("Cubic Graph Invariants", "[generator][cubic]") {
    auto n = GENERATE(4, 8, 12);
    Graph g = Graph::create_cubic_graph(n, Graph::RepType::ADJACENCY_LIST);

    SECTION("Regularity") {
        REQUIRE(g.vertexCount() == (size_t)n);
        for (size_t v : g.getAllVertices()) {
            REQUIRE(g.vertexDeg(v) == 3);
        }
        REQUIRE(g.edgeCount() == (size_t)(3 * n / 2));
    }
}

TEST_CASE("Random Graph Invariants", "[generator][random]") {
    size_t n = 20;
    double p = 0.5;
    Graph g = Graph::create_random_graph(n, p, Graph::RepType::ADJACENCY_LIST);

    SECTION("Basic constraints") {
        REQUIRE(g.vertexCount() == n);
        REQUIRE(g.edgeCount() <= (n * (n - 1) / 2));
    }
}

TEST_CASE("Random Components Generator Invariants", "[generator][components]") {
    auto params = GENERATE(
            std::make_pair(10, 3),
            std::make_pair(20, 5),
            std::make_pair(5, 5)
    );

    size_t n = params.first;
    size_t k = params.second;
    auto rep = Graph::RepType::ADJACENCY_LIST;

    Graph g = Graph::create_components(n, k, rep);

    SECTION("Vertex count consistency") {
        REQUIRE(g.vertexCount() == n);
    }

    SECTION("Connectivity count") {
        auto components = g.get_edge_2_connected_components();

        INFO("Testing n=" << n << " with k=" << k << ". Found: " << components.size());
        REQUIRE(components.size() == k);
    }

    SECTION("Total edges upper bound") {
        REQUIRE(g.edgeCount() <= (n * (n - 1) / 2));
    }
}