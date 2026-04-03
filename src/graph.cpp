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

std::unordered_set<size_t> Graph::getConnected(size_t id) const {
    std::unordered_set<size_t> connected {};
    if (hasVertex(id)){
        std::unordered_set<size_t> black, grey;
        std::vector<size_t> stack = {id};
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

std::unordered_set<size_t> Graph::getDisconnected() const {
    size_t v_size = vertexCount();

    std::unordered_set<size_t> verteces_set(v_size);
    std::vector<size_t> verteces = getAllVertices();
    
    for (size_t i = 0; i != v_size; ++i){
        verteces_set.insert(verteces[i]);
    }    

    std::unordered_set<size_t> disconnected;
    while (verteces_set.size() > 0){
        size_t i = 0;
        while (!verteces_set.contains(verteces[i])) ++i;
        
        size_t v = verteces[i];
        verteces_set.erase(v);
        std::unordered_set<size_t> connected = getConnected(v);
        
        for (size_t c : connected) {
            verteces_set.erase(c);
        }
        disconnected.insert(v);
    }
    return disconnected;
}

size_t Graph::componentsCount() const {
    return getDisconnected().size();
}