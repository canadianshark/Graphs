#include <iostream>

#include "../include/graph.h"

void AdjacencyMatrix::addVertex(int id_) {
    if (!hasVertex(id_)){
        size_t size_before = vertexCount();
        index_tab.insert({id_, size_before});
        for (size_t i = 0; i != size_before; ++i){
            matrix[i].push_back(0);
        }
        matrix.push_back(std::vector<int>(size_before+1, 0));
        vertex_num++;
    }
};

void AdjacencyMatrix::addEdge(int from_, int to_) {
    addVertex(from_);
    addVertex(to_);
    if (from_ == to_) return;
    int from = index_tab.at(from_);
    int to = index_tab.at(to_);
    if (matrix[from][to] == 0 && matrix[to][from] == 0) edges_num++;
    matrix[from][to] = 1;
    matrix[to][from] = 1;
};

void AdjacencyMatrix::removeVertex(int id_) {
    if (hasVertex(id_)){
        edges_num -= vertexDeg(id_);
        int id = index_tab.at(id_);
        for (auto& pair : index_tab){
            if (pair.second > id){
                pair.second--;
            }
        }
        size_t size = vertexCount();
        for (size_t i = 0; i != size; ++i){
            if (i == id) continue;
            for (size_t j = id; j != size - 1; ++j){
                matrix[i][j] = matrix[i][j + 1];
            }
            matrix[i].pop_back();
        }
        
        for (size_t i = id; i != size - 1; ++i){
            matrix[i] = matrix[i + 1];
        }
        matrix.pop_back();

        vertex_num--;
    }
};

void AdjacencyMatrix::removeEdge(int from_, int to_) {
    if (hasEdge(from_, to_)){
        int from = index_tab.at(from_);
        int to = index_tab.at(to_);
        matrix[from][to] = 0;
        matrix[to][from] = 0;
        edges_num--;
    }  
};

std::unordered_set<int> AdjacencyMatrix::getNeighbours(int id_) const {
    return std::unordered_set<int>{};
};

size_t AdjacencyMatrix::vertexDeg(int id_) const {
    if (hasVertex(id_)){
        int id = index_tab.at(id_);
        size_t size = matrix.size();
        int sum = 0;
        for (size_t i = 0; i != size; ++i){
            sum += matrix[id][i];
        }
        return sum;
    }
    return 0;
};

bool AdjacencyMatrix::hasVertex(int id_) const {
    return index_tab.find(id_) != index_tab.end();
};

bool AdjacencyMatrix::hasEdge(int from_, int to_) const {
    if (!hasVertex(from_)){
        std::cout << "WARNING Adj matrix: vertex (" << from_ << ") does not exist!\n";
        return false;
    }
    if (!hasVertex(to_)){
        std::cout << "WARNING Adj matrix: vertex (" << to_ << ") does not exist!\n";
        return false;
    }
    int from = index_tab.at(from_);
    int to = index_tab.at(to_);
    return matrix[from][to] == 1 && matrix[to][from] == 1;
};

size_t AdjacencyMatrix::vertexCount() const {
    return vertex_num;
};

size_t AdjacencyMatrix::edgeCount() const {
    return edges_num;
};

void AdjacencyMatrix::print() const {
    size_t size = matrix.size();
    for (size_t i = 0; i != size; ++i){
        std::cout << "[ ";
        for (size_t j = 0; j != size; ++j){
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "]\n";
    }
    std::cout << "]\n";
};


//#include "../include/graph.h"
//
//void AdjacencyMatrix::reindex(int id_) {
//    index_table[id] = last_index;
//    last_index++;
//}
//
//bool AdjacencyMatrix::check_by_real_id(int id_) const {
//    auto it = index_table.find(id);
//    if(it != index_table.end()){
//        return true;
//    }
//    else{
//        return false;
//    }
//}
//
//int AdjacencyMatrix::real_id(int id_) const {
//    auto it = index_table.find(id);
//    if(it != index_table.end()){
//        return it->second;
//    }
//    //TODO тут обезопасить это дело надо
//}
//
//void AdjacencyMatrix::addVertex(int id_) {
//    if(!check_by_real_id(id)){
//        std::vector<bool> row;
//        row.resize(last_index);
//        row[last_index - 1]=1;
//        if(matrix.capacity() < last_index){
//            matrix.push_back(row);
//        }
//        else{
//            matrix[last_index - 1] = row;
//        }
//    }
//    reindex(id);
//}
//
//void AdjacencyMatrix::addEdge(int from_, int to_) {
//   if(!check_by_real_id(from)){
//       addVertex(from);
//   }
//   if(!check_by_real_id(to)){
//        addVertex(to);
//   }
//   int actual_from = real_id(from);
//   int actual_to = real_id(to);
//   matrix[actual_from][actual_to] = 1;
//   matrix[actual_to][actual_from] = 1;
//}
//
//std::unordered_set<int> AdjacencyMatrix::getNeighbours(int id_) const {
//    auto it = index_table.find(id);
//    std::unordered_set<int> neighbours;
//    size_t index = 1;
//    if (it != index_table.end()) {
//      for(auto col : matrix[it->second]){
//          if(col == 1){
//              neighbours.insert(index);
//          }
//      }
//      index++;
//    }
//    return neighbours;
//}
//
//bool AdjacencyMatrix::hasEdge(int from_, int to_) const {
//    auto from_neighbours = getNeighbours(from);
//    auto to_heighbours = getNeighbours(to);
//
//    return (from_neighbours.contains(real_id(to)) && to_heighbours.contains(real_id(from)));
//
//}
//
//bool AdjacencyMatrix::hasVertex(int id_) const {
//    auto neighbours = getNeighbours(id);
//    return neighbours.contains(real_id(id));
//}
//
//size_t AdjacencyMatrix::vertexDeg(int id_) const {
//    auto neighbours = getNeighbours(id);
//    return neighbours.size();
//}
//
//size_t AdjacencyMatrix::vertexCount() const {
//    return matrix.size();
//}
//
//size_t AdjacencyMatrix::edgeCount() const {
//    size_t deg_sum = 0;
//    for(const auto& vertex : matrix){
//        deg_sum += vertexDeg(vertex.first);
//    }
//    return deg_sum/2;
//}