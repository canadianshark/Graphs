#include "../include/graph.h"
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
    for (int i = 1; i < vert_n; ++i){
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

Graph Graph::create_path_graph(size_t vert_n, Graph::RepType representantion) {
    Graph G(representantion);
    for(int i = 0; i < vert_n-1; i++){
        G.addEdge(i, i+1);
    }
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
        int to = rand() % (vert_n - 1);
        if (to >= from) to++;
        G.addEdge(from, to);
    }
    return G;
}

Graph Graph::create_cubic_graph(size_t vert_n, Graph::RepType representantion) {
    if (vert_n < 4 || vert_n % 2 != 0) {
        throw std::invalid_argument("Cubic graph requires even number of vertices >= 4");
    }

    Graph G(representantion);


    G = create_cycle_graph(vert_n, representantion);

    for(size_t i = 0; i < vert_n / 2; i++){
        G.addEdge(i, i + vert_n / 2);
    }

    return G;
}
std::vector<bool> get_split (size_t n, size_t c) {
    srand(time(0));
    std::unordered_set<int> nums;
    while (nums.size() < c - 1){
        nums.insert(rand() % (n - 1));
    }
    std::vector<bool> split(n, 0);
    for (int num : nums) split[num + 1] = 1;
    split[0] = 1;
    return split;
}

Graph Graph::create_components(size_t vert_n, size_t components, RepType representation){
    if (components == 0 || components > vert_n){
        throw std::invalid_argument("Invalid number of components!");
    }
    Graph G(representation);
    auto split = get_split(vert_n, components);
    for (size_t i = 0; i != vert_n; ++i){
        if (split[i] == 1){
            G.addVertex(i);
        } else {
            G.addEdge(i, i - 1);
        }
    }
    return G;
};
// Graph static create_bridges(size_t vert_n, size_t bridges, RepType representation);
// Graph static create_articulation_points(size_t vert_n, size_t points, RepType representation);
// Graph static create_2_bridges(size_t vert_n, size_t bridges, RepType representation);