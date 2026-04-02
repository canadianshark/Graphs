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
    Graph G = Graph::create_random_graph(6, Graph::RepType::ADJACENCY_MATRIX);
    
    G.print();
    print_set(G.getConnected(0));
    
    return 0;
}
