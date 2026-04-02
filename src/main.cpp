#include <iostream>

#include "../include/graph.h"

void print_set (std::unordered_set<int> s) {
    if (s.empty()){
        std::cout << "empty!\n";
        return;
    }
    for (int el : s){
        std::cout << el << " ";
    }
    std::cout << "\n";
}

int main() {
    Graph graph = Graph::create_complete_graph(5, Graph::RepType::ADJACENCY_MATRIX);    
    graph.addVertex(100);
    graph.addEdge(100, 1);
    graph.addEdge(2, 100);
    graph.addEdge(20, 30);

    graph.removeVertex(4);
    graph.removeEdge(3, 5);

    graph.print();

    print_set(graph.getNeighbours(2));
    std::cout << graph.vertexDeg(1) << "\n";
    std::cout << graph.hasVertex(20) << "\n";
    std::cout << graph.hasVertex(6) << "\n";
    std::cout << graph.hasEdge(2, 3) << "\n";
    std::cout << graph.hasEdge(3, 5) << "\n";
    std::cout << graph.hasEdge(6, 7) << "\n";
    
    std::cout << graph.vertexCount() << "\n";
    std::cout << graph.edgeCount() << "\n";
    return 0;
}
