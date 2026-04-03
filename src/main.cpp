#include <iostream>

#include "../include/graph.h"
#include "../include/serializer.h"

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
    Graph::RepType rep = Graph::RepType::ADJACENCY_MATRIX;

    for(int n = 4; n <= 10; n++){
        Graph G = Graph::create_halin_graph(n, rep);
        DotSerializer serializer;
        serializer.serialize(G, "../output/output" + std::to_string(n) + ".dot");
    }
    // DotSerializer serializer;
    // serializer.serialize(G, "../output/output.txt");
    return 0;
}
