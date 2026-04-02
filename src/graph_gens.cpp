#include "../include/graph.h"
#include <cstdlib>
#include <ctime>

Graph Graph::create_complete_graph(int vert_n, Graph::RepType representation) {
    Graph G(representation);
    for(int i = 1; i <= vert_n; i++){
        G.addVertex(i);
        for(int n = 1; n < i; n++){
            G.addEdge(i, n);
        }
    }
    return G;
}

Graph Graph::create_path_graph(int vert_n, Graph::RepType representantion) {
    Graph G(representantion);

    for(int i = 1; i < vert_n; i++){
        G.addEdge(i, i+1);
    }

    return G;
}

Graph Graph::create_cycle_graph(int vert_n, Graph::RepType representantion){
    Graph G = Graph::create_path_graph(vert_n, representantion);
    G.addEdge(1,vert_n);
    return G;
}

Graph Graph::create_compl_bipartite(int vert_n, Graph::RepType representantion){
    Graph G(representantion);
    srand(time(0));
    int n_1 = rand() % (vert_n - 1);
    int n_2 = vert_n - n_1;
    for(int i = 1; i <= n_1; i++){
        for(int n  = n_1 + 1; n <= vert_n; n++){
            G.addEdge(i,n);
        }
    }
//TODO вообще от одной вершины не должно работать
    return G;
}

Graph Graph::create_star_graph(int vert_n, Graph::RepType representantion){
    Graph G(representantion);
    for(int n = 2; n <= vert_n; n++){
        G.addEdge(1,n);
    }
    return G;
}

Graph Graph::create_cubic_graph(int vert_n, Graph::RepType representantion) {
    Graph G(representantion);
    //TODO нужно сделать чтобы работало от 4+ вершин

}