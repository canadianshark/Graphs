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

    size_t v;
    double p;
    std::cin >> v >> p;
    Graph G = Graph::create_tree_graph(v, rep);
    G.print();


    // MatrixParser P;
    // Graph E(rep);
    // P.parse(E, "../input/input.txt");
    // E.print();

    // // auto disconnected = G.getDisconnected();
    // // for (auto n : disconnected){
    // //     std::cout << n << ": ";
    // //     auto connected = G.getConnected(n);
    // //     for (auto m : connected) std::cout << m << " ";
    // //     std::cout << "\n";
    // // }

    DotSerializer serializer;
    serializer.serialize(G, "../output/output.txt");
    
    std::cout << "Density: " << G.getDensity() << "\n";
    std::cout << "Transitivity: " << G.getTransitivity() << "\n";
    std::cout << "Diameter: " << G.getDiameter() << "\n";
    std::cout << "Components: " << G.componentsCount() << "\n";
    std::cout << "Is bipartite: " << G.isBipartite() << "\n";

    return 0;
}
