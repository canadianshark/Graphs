#include "../include/graph.h"
#include <cstdlib>
#include <ctime>
#include <set>

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

    if (vert_n == 0) return G;
    if (vert_n == 1) {
        G.addVertex(0);
        return G;
    }

    for (size_t i = 0; i < vert_n; i++) {
        G.addVertex(i);
    }

    std::vector<size_t> prufer_code(vert_n - 2);
    for (size_t i = 0; i < vert_n - 2; i++) {
        prufer_code[i] = rand() % vert_n;
    }

    std::vector<size_t> degree(vert_n, 1);
    for (size_t v : prufer_code) {
        degree[v]++;
    }

    std::set<size_t> leaves;
    for (size_t i = 0; i < vert_n; i++) {
        if (degree[i] == 1) leaves.insert(i);
    }

    for (size_t code : prufer_code) {
        size_t leaf = *leaves.begin();
        leaves.erase(leaves.begin());


        G.addEdge(leaf, code);

        degree[leaf]--;
        degree[code]--;

        if (degree[code] == 1) leaves.insert(code);
    }

    size_t leaf1 = *leaves.begin();
    leaves.erase(leaves.begin());
    size_t leaf2 = *leaves.begin();
    G.addEdge(leaf1, leaf2);

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

Graph Graph::create_common_graph(size_t vert_n, Graph::RepType representation){
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

Graph Graph::create_random_graph(size_t n, double probability, Graph::RepType representation) {
    Graph G(representation);

    if(probability < 0 || probability > 1){
        throw std::out_of_range("probability cant be less than 0 and bigger than 1");
    }

    for (size_t i = 0; i < n; i++) {
        G.addVertex(i);
    }

    for (size_t i = 0; i < n; i++) {
        for (size_t j = i + 1; j < n; j++) {
            double r = rand() / (double)RAND_MAX;
            if (r <= probability) {
                G.addEdge(i, j);
            }
        }
    }

    return G;
}

Graph Graph::create_halin_graph(size_t vert_n, Graph::RepType representation) {
        if (vert_n < 4) {
            throw std::invalid_argument("Halin graph requires at least 4 vertices");
        }

        Graph G = create_tree_graph(vert_n, representation);

        std::vector<size_t> leaves;
        for (size_t i = 0; i < vert_n; i++) {
            if (G.vertexDeg(i) == 1) {
                leaves.push_back(i);
            }
        }

        for (size_t i = leaves.size() - 1; i > 0; i--) {
            size_t j = rand() % (i + 1);
            std::swap(leaves[i], leaves[j]);
        }


        for (size_t i = 0; i < leaves.size() - 1; i++) {
            G.addEdge(leaves[i], leaves[i + 1]);
        }
        if (leaves.size() >= 2) {
            G.addEdge(leaves.back(), leaves.front());
        }

        return G;

}