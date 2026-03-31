#include "graph.h"

void AdjecencyListRep::addVertex(int id) {
    if(!adj_list.contains(id)){
        adj_list[id] = std::unordered_set<int>{};
    }
}

void AdjecencyListRep::addEdge(int from, int to) {
    if(adj_list.contains(from) && adj_list.contains(to)){
        adj_list[from].insert(to);
        adj_list[to].insert(from);
    }
}

std::unordered_set<int> AdjecencyListRep::getNeighbours(int id) const {
    auto it = adj_list.find(id);
    if (it != adj_list.end()) {
        return it->second;
    }
}

bool AdjecencyListRep::hasVertex(int id) const {
    return adj_list.contains(id);
}

bool AdjecencyListRep::hasEdge(int from, int to) const {
   auto from_neighbours = getNeighbours(from);
   auto to_neighbours = getNeighbours(to);
   return (from_neighbours.contains(to) && to_neighbours.contains(from));
}

size_t AdjecencyListRep::vertexDeg(int id) const {
    auto neighbours = getNeighbours(id);
    return neighbours.size();
}

size_t AdjecencyListRep::vertexCount() const {
    return adj_list.size();
}

size_t AdjecencyListRep::edgeCount() const {
    size_t deg_sum = 0;
    for(const auto& vertex : adj_list){
       deg_sum += vertexDeg(vertex.first);
    }
    return deg_sum/2;
}







