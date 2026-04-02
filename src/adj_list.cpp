#include "graph.h"

void AdjacencyList::addVertex(size_t id) {
    if(!adj_list.contains(id)){
        adj_list[id] = std::unordered_set<size_t>{};
    }
}

void AdjacencyList::addEdge(size_t from, size_t to) {
    if(from == to){
        return;
    }
    if(!adj_list.contains(from)){
        addVertex(from);
    }
    if(!adj_list.contains(to)){
        addVertex(to);
    }
    adj_list[from].insert(to);
    adj_list[to].insert(from);
}

std::unordered_set<size_t> AdjacencyList::getNeighbours(size_t id) const {
    auto it = adj_list.find(id);
    if (it != adj_list.end()) {
        return it->second;
    }
    return {};
}

bool AdjacencyList::hasVertex(size_t id) const {
    return adj_list.contains(id);
}

bool AdjacencyList::hasEdge(size_t from, size_t to) const {
    if(from == to){
        return false;
    }
    auto it = adj_list.find(from);
    if (it == adj_list.end()) {
        return false;
    }
    return it->second.contains(to);
}

size_t AdjacencyList::vertexDeg(size_t id) const {
    auto it = adj_list.find(id);
    if (it == adj_list.end()) {
        return 0;
    }
    return it->second.size();
}

size_t AdjacencyList::vertexCount() const {
    return adj_list.size();
}

size_t AdjacencyList::edgeCount() const {
    size_t deg_sum = 0;
    for(const auto& vertex : adj_list){
        deg_sum += vertexDeg(vertex.first);
    }
    return deg_sum/2;
}

void AdjacencyList::removeEdge(size_t from, size_t to) {
    if(from == to){
        return;
    }
    if(adj_list.contains(from) && adj_list.contains(to)){
        adj_list[from].erase(to);
        adj_list[to].erase(from);
    }
}

void AdjacencyList::removeVertex(size_t id) {
    for(auto N : getNeighbours(id)){
        removeEdge(id, N);
    }
    adj_list.erase(id);
}

std::vector<size_t> AdjacencyList::getAllVertices() const {
    std::vector<size_t> vertices;
    for (const auto& pair : adj_list) {
        vertices.push_back(pair.first);
    }
    return vertices;
}

std::vector<std::pair<size_t, size_t>> AdjacencyList::getAllEdges() const {
    std::vector<std::pair<size_t, size_t>> edges;

    for (const auto& pair : adj_list) {
        size_t from = pair.first;
        const std::unordered_set<size_t>& neighbours = pair.second;

        for (size_t to : neighbours) {
            if (from < to) {
                edges.push_back({from, to});
            }
        }
    }

    return edges;
}
