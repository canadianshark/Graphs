#include "graph.h"

void AdjacencyMatrix::addVertex(int id) {
    if(!matrix[id][id]){
        matrix[id][id] = 1;
    }
}

void AdjacencyMatrix::addEdge(int from, int to) {
    if(matrix[from][from] && matrix[to][to]){
        matrix[from][to] = 1;
        matrix[to][from] = 1;
    }
}

std::unordered_set<int> AdjacencyMatrix::getNeighbours(int id) const {
    auto it = matrix.find(id);
    std::unordered_set<int> neighbours;
    size_t index = 1;
    if (it != matrix.end()) {
      for(auto& col : it->second){
          if(col == 1){
              neighbours.insert(index);
          }
      }
      index++;
    }
    return neighbours;
}

bool AdjacencyMatrix::hasEdge(int from, int to) const {
    auto from_neighbours = getNeighbours(from);
    auto to_heighbours = getNeighbours(to);

    return (from_neighbours.contains(to) && to_heighbours.contains(from));

}

bool AdjacencyMatrix::hasVertex(int id) const {
    auto neighbours = getNeighbours(id);
    return neighbours.contains(id);
}

size_t AdjacencyMatrix::vertexDeg(int id) const {
    auto neighbours = getNeighbours(id);
    return neighbours.size();
}

size_t AdjacencyMatrix::vertexCount() const {
    return matrix.size();
}

size_t AdjacencyMatrix::edgeCount() const {
    size_t deg_sum = 0;
    for(const auto& vertex : matrix){
        deg_sum += vertexDeg(vertex.first);
    }
    return deg_sum/2;
}