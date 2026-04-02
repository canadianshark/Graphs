#include <iostream>

#include "../include/graph.h"

void AdjacencyList::addVertex (int id) {
    if (!hasVertex(id)){
        adj_list[id] = std::unordered_set<int>{};
        vertex_num++;
    }
}

void AdjacencyList::addEdge (int from, int to) {
    addVertex(from);
    addVertex(to);
    if (from == to) return;
    if (!adj_list[from].contains(to) && !adj_list[to].contains(from)){
        edges_num++;
    }
    adj_list[from].insert(to);
    adj_list[to].insert(from);
}

void AdjacencyList::removeVertex (int id) {
    for (auto n : getNeighbours(id)){
        removeEdge(id, n);
    }
    adj_list.erase(id);
    vertex_num--;
}

void AdjacencyList::removeEdge (int from, int to) {
    if (from == to) return;
    if (hasEdge(from, to)){
        adj_list[from].erase(to);
        adj_list[to].erase(from);
        edges_num--;
    }
}

std::unordered_set<int> AdjacencyList::getNeighbours (int id) const {
    auto pair = adj_list.find(id);
    if (pair != adj_list.end()){
        return pair->second;
    }
    return std::unordered_set<int>{};
}

size_t AdjacencyList::vertexDeg (int id) const {
    return getNeighbours(id).size();
}

bool AdjacencyList::hasVertex (int id) const {
    return adj_list.contains(id);
}

bool AdjacencyList::hasEdge (int from, int to) const {
    if (!adj_list.contains(from)){
        std::cout << "WARNING Adj list: vertex (" << from << ") does not exist!\n";
        return false;
    }
    if (!adj_list.contains(to)){
        std::cout << "WARNING Adj list: vertex (" << to << ") does not exist!\n";
        return false;
    }
    return adj_list.at(from).contains(to);
}

size_t AdjacencyList::vertexCount () const {
    return vertex_num;
}

size_t AdjacencyList::edgeCount () const {
    return edges_num;
}

void AdjacencyList::print () const {
    for (auto pair : adj_list){
        int v = pair.first;
        std::unordered_set<int> neighbours = pair.second;

        std::cout << "[" << v << "] : {";
        size_t size = neighbours.size();
        for (auto n : neighbours){
            size--;
            std::cout << n;
            if (size != 0) std::cout << ", ";
        }
        std::cout << "}\n";
    }
    std::cout << "\n";
}
