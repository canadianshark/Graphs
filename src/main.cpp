#include <iostream>

#include "../include/graph.h"

int main() {
    Graph graph = Graph::create_complete_graph(10, Graph::RepType::ADJACENCY_LIST);
    graph.print();

    return 0;
}
