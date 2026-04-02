//#include "../include/graph.h"
//
//void AdjacencyMatrix::reindex(int id) {
//    index_table[id] = last_index;
//    last_index++;
//}
//
//bool AdjacencyMatrix::check_by_real_id(int id) const {
//    auto it = index_table.find(id);
//    if(it != index_table.end()){
//        return true;
//    }
//    else{
//        return false;
//    }
//}
//
//int AdjacencyMatrix::real_id(int id) const {
//    auto it = index_table.find(id);
//    if(it != index_table.end()){
//        return it->second;
//    }
//    //TODO тут обезопасить это дело надо
//}
//
//void AdjacencyMatrix::addVertex(int id) {
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
//void AdjacencyMatrix::addEdge(int from, int to) {
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
//std::unordered_set<int> AdjacencyMatrix::getNeighbours(int id) const {
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
//bool AdjacencyMatrix::hasEdge(int from, int to) const {
//    auto from_neighbours = getNeighbours(from);
//    auto to_heighbours = getNeighbours(to);
//
//    return (from_neighbours.contains(real_id(to)) && to_heighbours.contains(real_id(from)));
//
//}
//
//bool AdjacencyMatrix::hasVertex(int id) const {
//    auto neighbours = getNeighbours(id);
//    return neighbours.contains(real_id(id));
//}
//
//size_t AdjacencyMatrix::vertexDeg(int id) const {
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