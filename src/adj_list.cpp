#include "graph.h"

void AdjacencyList::addVertex(int id) {
    if(!adj_list.contains(id)){
        adj_list[id] = std::unordered_set<int>{};
    }
}

void AdjacencyList::addEdge(int from, int to) {
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

std::unordered_set<int> AdjacencyList::getNeighbours(int id) const {
    auto it = adj_list.find(id);
    if (it != adj_list.end()) {
        return it->second;
    }
}

bool AdjacencyList::hasVertex(int id) const {
    return adj_list.contains(id);
}

bool AdjacencyList::hasEdge(int from, int to) const {
   if(from == to){
       return true;
   }
    auto from_neighbours = getNeighbours(from);
   auto to_neighbours = getNeighbours(to);
   return (from_neighbours.contains(to) && to_neighbours.contains(from));
   //Тут бы по-хорошему какой-нибудь варнинг кинуть, если вдруг ребро только в одну сторону в списке указано
}

size_t AdjacencyList::vertexDeg(int id) const {
    auto neighbours = getNeighbours(id);
    return neighbours.size();
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


void AdjacencyList::removeEdge(int from, int to) {
    if(from == to){
        return;
    }
    if(adj_list.contains(from) && adj_list.contains(to)){
        adj_list[from].erase(to);
        adj_list[to].erase(from);
    }

}

void AdjacencyList::removeVertex(int id) {
    for(auto N : getNeighbours(id)){
        removeEdge(id, N);
    }
    adj_list.erase(id);
}






