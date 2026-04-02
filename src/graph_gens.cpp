#include "graph.h"
#include <cstdlib>
#include <ctime>

Graph Graph::create_complete_graph(size_t vert_n, Graph::RepType representation) {
    Graph G(representation);
    for(int i = 0; i < vert_n; i++){
        G.addVertex(i);
        for(int n = 0; n < i; n++){
            G.addEdge(i, n);
        }
    }
    return G;
}

Graph Graph::create_compl_bipartite(size_t vert_n, size_t vert_m, Graph::RepType representantion){
    if(vert_n < 2){
        throw std::invalid_argument("Complete bipartite graph requires at least 2 vertices");
    }
    Graph G(representantion);
    for (int i = 0; i < vert_n; ++i){
        for (int j = 0; j < vert_m; ++j){
            G.addEdge(i, vert_n + j);
        }
    }
    return G;
}

Graph Graph::create_tree_graph(size_t vert_n, Graph::RepType representantion){
    Graph G(representantion);
    for (int i = 0; i < vert_n; ++i){
        G.addEdge(i, (i-1)/2);
    }
    return G;
}


Graph Graph::create_star_graph(size_t vert_n, Graph::RepType representantion){
    Graph G(representantion);
    for(int n = 1; n < vert_n; n++){
        G.addEdge(0, n);
    }

    return G;
}

Graph Graph::create_cycle_graph(size_t vert_n, Graph::RepType representantion){
    if(vert_n < 3){
        throw std::invalid_argument("Cycle graph requires at least 3 vertices");
    }

    Graph G = Graph::create_path_graph(vert_n, representantion);
    G.addEdge(vert_n-1, 0);
    return G;
}



Graph Graph::create_wheel_graph(size_t vert_n, Graph::RepType representation){
    Graph G = Graph::create_cycle_graph(vert_n-1, representation);
    for (int i = 0; i < vert_n - 1; ++i){
        G.addEdge(i, vert_n);
    }
    return G;
}

Graph Graph::create_random_graph(size_t vert_n, Graph::RepType representation){
    Graph G(representation);
    srand(time(0));
    int edges_num = rand() % (vert_n * (vert_n + 1) / 2);
    for (int v = 0; v != vert_n; ++v){
        G.addVertex(v);
    }
    for (int e = 0; e < edges_num; ++e){
        int from = rand() % vert_n;
        int to = rand() % (vert_n - 1) ;
        if (to >= from) to++;
        G.addEdge(from, to);
    }
    return G;
}

Graph Graph::create_cubic_graph(size_t vert_n, Graph::RepType representantion) {
    Graph G(representantion);
    //TODO нужно сделать чтобы работало от 4+ вершин
    return G;
}

Graph Graph::create_path_graph(size_t vert_n, Graph::RepType representantion) {
    Graph G(representantion);
    for(int i = 0; i < vert_n-1; i++){
        G.addEdge(i, i+1);
    }
    return G;
}