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
    Graph G = Graph::create_random_graph(10, rep);

    G.print();
    auto disconnected = G.getDisconnected();
    for (auto n : disconnected){
        std::cout << n << ": ";
        auto connected = G.getConnected(n);
        for (auto m : connected) std::cout << m << " ";
        std::cout << "\n";
    }

    // DotSerializer serializer;
    // serializer.serialize(G, "../output/output.txt");
    return 0;
}
