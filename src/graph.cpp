#include "../include/graph.h"
#include "../include/dfs.h"
#include "../include/sub_graph_dfs.h"
#include "../include/span_tree_visitor.h"

#include <cstdlib>

Graph::Graph(Graph::RepType rep_) {
    switch (rep_) {
        case RepType::ADJACENCY_LIST:
            rep = std::make_unique<AdjacencyList>();
            backend = RepType::ADJACENCY_LIST;
            break;
       case RepType::ADJACENCY_MATRIX:
            rep = std::make_unique<AdjacencyMatrix>();
            backend = RepType::ADJACENCY_MATRIX;
            break;
        default:
            throw std::invalid_argument("there is no such graph representation type");
            break;


    }

}

Graph::RepType Graph::get_backend_type() const {
    return backend;
}

Graph Graph::get_component_subgraph(size_t id) const {
    Graph result(get_backend_type());
    DFS dfs(*this, std::make_unique<SubGraphVisitor>(result));
    dfs.traverseFrom(id);
    return result;
}

Graph Graph::get_span_tree() const {
    Graph result(get_backend_type());
    srand(time(0));
    DFS dfs(*this, std::make_unique<SpanningTreeVisitor>(result));
    auto verts = getAllVertices();
    size_t start_id = rand() % verts.size();
    dfs.traverseFrom(verts[start_id]);
    return result;
}

bool Graph::isBipartite () const {
    std::vector<size_t> verteces = getAllVertices();
    std::unordered_set<size_t> red, blue;
    
    size_t V = verteces.size();
    red.insert(verteces[0]);
    for (size_t i = 0; i != V; ++i){
        if (red.contains(verteces[i])){
            auto neighbours = getNeighbours(verteces[i]);
            for (auto n : neighbours){
                if (red.contains(n)) return false;
                blue.insert(n);
            }
        }
        if (blue.contains(verteces[i])){
            auto neighbours = getNeighbours(verteces[i]);
            for (auto n : neighbours){
                if (blue.contains(n)) return false;
                red.insert(n);
            }
        }
    }
    return true;
}

std::pair<size_t, size_t> Graph::getFarthest (size_t start) const {
    std::unordered_map<size_t, size_t> distances;
    std::queue<size_t> queue;

    distances[start] = 0;
    queue.push(start);

    size_t farthest = start;
    size_t max_dist = 0;

    while (!queue.empty()){
        size_t current = queue.front();
        queue.pop();

        for (size_t n : getNeighbours(current)){
            if (distances.find(n) == distances.end()){
                distances[n] = distances[current] + 1;
                queue.push(n);

                if (distances[n] > max_dist){
                    max_dist = distances[n];
                    farthest = n;
                }
            }
        }
    }

    return std::pair<size_t, size_t>{farthest, max_dist};
}

size_t Graph::getDiameter () const {
    std::vector<size_t> verteces = getAllVertices();
    if (verteces.empty()) return 0;

    auto [farthest1, dist1] = getFarthest(verteces[0]);
    auto [farthest2, dist2] = getFarthest(farthest1);

    return dist2;
}

size_t Graph::componentsCount () const {
    auto vvector = getAllVertices();
    std::unordered_set<size_t> vset;
    for (auto v : vvector){
        vset.insert(v);
    }
    size_t components = 0;
    for (auto v : vvector){
        if (vset.find(v) == vset.end()) continue;
        Graph sub = get_component_subgraph(v);
        auto connected = sub.getAllVertices();

        for (auto c : connected){
            vset.erase(c);
        }
        ++components;
    }
    
    return components;
}