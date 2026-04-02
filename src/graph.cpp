#include "../include/graph.h"

Graph::Graph(Graph::RepType rep_) {
    switch (rep_) {
        case RepType::ADJACENCY_LIST:
            rep = std::make_unique<AdjacencyList>();
            break;
       case RepType::ADJACENCY_MATRIX:
            rep = std::make_unique<AdjacencyMatrix>();
            break;
        default:
            //TODO тут нужно покрыть ошибку
            break;


    }
}

std::unordered_set<int> Graph::getConnected(int id) const {
    std::unordered_set<int> connected {};
    if (hasVertex(id)){
        std::unordered_set<int> black, grey;
        std::vector<int> stack = {id};
        while (!stack.empty()){
            int v = stack.back();
            if (black.contains(v)){
                stack.pop_back();
            } else if (grey.contains(v)){
                grey.erase(v); black.insert(v);
                stack.pop_back();
            } else {
                grey.insert(v);
                for (int n : getNeighbours(v)){
                    if (!black.contains(n) && !grey.contains(n)){
                        stack.push_back(n);
                        connected.insert(n);
                    }
                }
            }
        }
    }
    return connected;
};
