#include "graph.h"

Graph::Graph(Graph::RepType rep_) {
    switch (rep_) {
        case RepType::ADJACENCY_LIST:
            rep = std::make_unique<AdjacencyList>();
            break;
//        case RepType::ADJACENCY_MATRIX:
//            rep = std::make_unique<AdjacencyMatrix>();
//            break;
        default:
            //TODO тут нужно покрыть ошибку
            break;


    }
}

