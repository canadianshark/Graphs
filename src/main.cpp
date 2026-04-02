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
    Graph complete = Graph::create_complete_graph(6, Graph::RepType::ADJACENCY_MATRIX);    
    std::cout << "complete\n"; complete.print();
    Graph bipartite = Graph::create_compl_bipartite(4, 3, Graph::RepType::ADJACENCY_MATRIX);    
    std::cout << "bipartite\n"; bipartite.print();
    Graph tree = Graph::create_tree_graph(6, Graph::RepType::ADJACENCY_MATRIX);    
    std::cout << "tree\n"; tree.print();
    Graph star = Graph::create_star_graph(6, Graph::RepType::ADJACENCY_MATRIX);    
    std::cout << "star\n"; star.print();
    Graph cycle = Graph::create_cycle_graph(6, Graph::RepType::ADJACENCY_MATRIX);    
    std::cout << "cycle\n"; cycle.print();
    Graph path = Graph::create_path_graph(6, Graph::RepType::ADJACENCY_MATRIX);    
    std::cout << "path\n"; path.print();
    Graph wheel = Graph::create_wheel_graph(6, Graph::RepType::ADJACENCY_MATRIX);    
    std::cout << "wheel\n"; wheel.print();
    Graph random = Graph::create_random_graph(6, Graph::RepType::ADJACENCY_MATRIX);    
    std::cout << "random\n"; random.print();
    Graph cubic = Graph::create_cubic_graph(6, Graph::RepType::ADJACENCY_MATRIX);    
    std::cout << "cubic\n"; cubic.print();

    return 0;
}
