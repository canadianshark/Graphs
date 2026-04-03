#include <iostream>

#include "../include/graph.h"
#include "../include/serializer.h"
#include "../include/parser.h"

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

int main (int argn, char* argv[]) {
    Graph::RepType rep = Graph::RepType::ADJACENCY_LIST;

    Graph G = Graph::create_compl_bipartite(4, 4, rep);
    G.print();

    MatrixParser P;
    Graph E(rep);
    P.parse(E, "../input/input.txt");
    E.print();

    // auto disconnected = G.getDisconnected();
    // for (auto n : disconnected){
    //     std::cout << n << ": ";
    //     auto connected = G.getConnected(n);
    //     for (auto m : connected) std::cout << m << " ";
    //     std::cout << "\n";
    // }

    // DotSerializer serializer;
    // serializer.serialize(G, "../output/output.txt");
    return 0;
}
