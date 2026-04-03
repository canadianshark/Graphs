#include "../include/graph.h"
#include <iostream>
#include "dfs.h"
#include <random>

void AdjacencyList::addVertex (size_t id) {
    if (!hasVertex(id)){
        adj_list[id] = std::unordered_set<size_t>{};
        vertex_num++;
    }
}

void AdjacencyList::addEdge (size_t from, size_t to) {
    addVertex(from);
    addVertex(to);
    if (from == to) return;
    if (!adj_list[from].contains(to) && !adj_list[to].contains(from)){
        edges_num++;
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

bool AdjacencyList::hasEdge (size_t from, size_t to) const {
    if (!hasVertex(from)){
        std::cout << "WARNING Adj list: vertex (" << from << ") does not exist!\n";
        return false;
    }
    if (!hasVertex(to)){
        std::cout << "WARNING Adj list: vertex (" << to << ") does not exist!\n";
        return false;
    }
    return adj_list.at(from).contains(to);
}

size_t AdjacencyList::vertexDeg(size_t id) const {
    return getNeighbours(id).size();
}


size_t AdjacencyList::vertexCount () const {
    return vertex_num;
}

size_t AdjacencyList::edgeCount () const {
    return edges_num;
}


void AdjacencyList::removeVertex (size_t id) {
    if(!hasVertex(id)){
        return;
    }
    for (auto n : getNeighbours(id)){
        removeEdge(id, n);
    }
    adj_list.erase(id);
    vertex_num--;
}

void AdjacencyList::removeEdge (size_t from, size_t to) {
    if (from == to) return;
    if (hasEdge(from, to)){
        adj_list[from].erase(to);
        adj_list[to].erase(from);
        edges_num--;
    }
}

void AdjacencyList::print () const {
    for (auto pair : adj_list){
        int v = pair.first;
        std::unordered_set<size_t> neighbours = pair.second;

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
std::vector<size_t> AdjacencyList::getNeighboursShuffled(size_t id) const {
    std::vector<size_t> neighbours;
    auto it = adj_list.find(id);
    if (it != adj_list.end()) {
        neighbours.assign(it->second.begin(), it->second.end());
        std::shuffle(neighbours.begin(), neighbours.end(),
                     std::mt19937(std::random_device{}()));
    }
    return neighbours;
}


