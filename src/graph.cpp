#include "../include/graph.h"
#include "dfs.h"
#include "sub_graph_dfs.h"
#include "cstdlib"
#include "span_tree_visitor.h"
#include "bridge_visitor.h"

Graph::Graph(Graph::RepType rep_) {
    switch (rep_) {
        case RepType::ADJACENCY_LIST:
            rep = std::make_unique<AdjacencyList>();
            backend = RepType::ADJACENCY_LIST;
            break;
       case RepType::ADJACENCY_MATRIX:
            rep = std::make_unique<AdjacencyMatrix>();
            backend = RepType::ADJACENCY_MATRIX;
            break;
        default:
            throw std::invalid_argument("there is no such graph representation type");
            break;


    }

}

Graph::RepType Graph::get_backend_type() const {
    return backend;
}

Graph Graph::get_component_subgraph(size_t id) const {
    Graph result(get_backend_type());
    DFS dfs(*this, std::make_unique<SubGraphVisitor>(result));
    dfs.traverseFrom(id);
    return result;
}

Graph Graph::get_span_tree() const {
    Graph result(get_backend_type());
    srand(time(0));
    DFS dfs(*this, std::make_unique<SpanningTreeVisitor>(result));
    auto verts = getAllVertices();
    size_t start_id = rand() % verts.size();
    dfs.traverseFrom(verts[start_id]);
    return result;
}

std::vector<Graph> Graph::get_edge_2_connected_components() const {

    BridgeData bridgeResult;
    DFS bridgeDfs(*this, std::make_unique<BridgeFinderVisitor>(bridgeResult));
    bridgeDfs.traverse();

    // 2. Выделяем компоненты
    std::vector<Graph> components;
    std::unordered_set<size_t> globalVisited;

    for (size_t v : getAllVertices()) {
        if (globalVisited.find(v) == globalVisited.end()) {
            Graph bcc(get_backend_type());

            auto visitor = std::make_unique<BCCBuilderVisitor>(bcc, bridgeResult);
            DFS bccDfs(*this, std::move(visitor));
            bccDfs.traverseFrom(v);

            // Все вершины, которые попали в bcc, помечаем как посещенные
            for (size_t node : bcc.getAllVertices()) {
                globalVisited.insert(node);
            }

            components.push_back(std::move(bcc));
        }
    }

    return components;
}

void Graph::merge(const Graph& other) {

    size_t offset = 0;
    auto vertices = this->getAllVertices();
    if (!vertices.empty()) {
        offset = *std::max_element(vertices.begin(), vertices.end()) + 1;
    }


    for (size_t v : other.getAllVertices()) {
        this->addVertex(v + offset);
    }


    for (const auto& edge : other.getAllEdges()) {
        this->addEdge(edge.first + offset, edge.second + offset);
    }
}


//std::unordered_set<size_t> Graph::getConnected(size_t id) const {
//    std::unordered_set<size_t> connected {};
//    if (hasVertex(id)){
//        std::unordered_set<size_t> black, grey;
//        std::vector<size_t> stack = {id};
//        while (!stack.empty()){
//            int v = stack.back();
//            if (black.contains(v)){
//                stack.pop_back();
//            } else if (grey.contains(v)){
//                grey.erase(v); black.insert(v);
//                stack.pop_back();
//            } else {
//                grey.insert(v);
//                for (int n : getNeighbours(v)){
//                    if (!black.contains(n) && !grey.contains(n)){
//                        stack.push_back(n);
//                        connected.insert(n);
//                    }
//                }
//            }
//        }
//    }
//    return connected;
//};
//
//std::unordered_set<size_t> Graph::getDisconnected() const {
//    size_t v_size = vertexCount();
//
//    std::unordered_set<size_t> verteces_set(v_size);
//    std::vector<size_t> verteces = getAllVertices();
//
//    for (size_t i = 0; i != v_size; ++i){
//        verteces_set.insert(verteces[i]);
//    }
//
//    std::unordered_set<size_t> disconnected;
//    while (verteces_set.size() > 0){
//        size_t i = 0;
//        while (!verteces_set.contains(verteces[i])) ++i;
//
//        size_t v = verteces[i];
//        verteces_set.erase(v);
//        std::unordered_set<size_t> connected = getConnected(v);
//
//        for (size_t c : connected) {
//            verteces_set.erase(c);
//        }
//        disconnected.insert(v);
//    }
//    return disconnected;
//}
//
//size_t Graph::componentsCount() const {
//    return getDisconnected().size();
//}

