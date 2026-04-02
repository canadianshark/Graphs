#include "graph.h"
#include <cstdlib>
#include <ctime>

Graph Graph::create_complete_graph(size_t vert_n, Graph::RepType representation) {
    Graph G(representation);
    for(size_t i = 1; i <= vert_n; i++){
        G.addVertex(i);
        for(size_t n = 1; n < i; n++){
            G.addEdge(i, n);
        }
    }
    return G;
}

Graph Graph::create_path_graph(size_t vert_n, Graph::RepType representantion) {
    Graph G(representantion);

    for(size_t i = 1; i < vert_n; i++){
        G.addEdge(i, i+1);
    }

    return G;
}

Graph Graph::create_cycle_graph(size_t vert_n, Graph::RepType representantion){
    if(vert_n < 3){
        throw std::invalid_argument("Cycle graph requires at least 3 vertices");
    }

    Graph G = Graph::create_path_graph(vert_n, representantion);
    G.addEdge(1, vert_n);
    return G;
}

Graph Graph::create_compl_bipartite(size_t vert_n, Graph::RepType representantion){
    if(vert_n < 2){
        throw std::invalid_argument("Complete bipartite graph requires at least 2 vertices");
    }

    Graph G(representantion);
    srand(time(0));

    size_t n_1 = rand() % (vert_n - 1);
    if(n_1 == 0) n_1 = 1; // Чтобы обе доли были непустыми
    size_t n_2 = vert_n - n_1;

    for(size_t i = 1; i <= n_1; i++){
        G.addVertex(i);
    }
    for(size_t i = n_1 + 1; i <= vert_n; i++){
        G.addVertex(i);
    }

    for(size_t i = 1; i <= n_1; i++){
        for(size_t n = n_1 + 1; n <= vert_n; n++){
            G.addEdge(i, n);
        }
    }

    return G;
}

Graph Graph::create_star_graph(size_t vert_n, Graph::RepType representantion){
    if(vert_n < 2){
        throw std::invalid_argument("Star graph requires at least 2 vertices");
    }

    Graph G(representantion);
    for(size_t n = 2; n <= vert_n; n++){
        G.addEdge(1, n);
    }
    return G;
}

Graph Graph::create_tree_graph(size_t vert_n, Graph::RepType representantion){
    Graph G(representantion);
    // TODO
    return G;
}

Graph Graph::create_cubic_graph(size_t vert_n, Graph::RepType representantion) {
    Graph G(representantion);
    //TODO нужно сделать чтобы работало от 4+ вершин
    return G;
}