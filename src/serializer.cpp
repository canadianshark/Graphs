#include "../include/serializer.h"
#include <fstream>
#include <stdexcept>
#include <set>

DotSerializer::DotSerializer(const std::string& name): graphName(name) {}

void DotSerializer::serialize(const Graph& graph, const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    file << "graph " << graphName << " {\n";
    file << "    node [shape=circle];\n\n";


    file << "    // Vertices\n";
    auto vertices = graph.getAllVertices();
    for (size_t v : vertices) {
        file << "    " << v << ";\n";
    }


    file << "\n    // Edges\n";
    auto edges = graph.getAllEdges();
    for (const auto& edge : edges) {
        file << "    " << edge.first << " -- " << edge.second << ";\n";
    }

    file << "}\n";
    file.close();
}

void DotSerializer::serializeSpanningTreeHighlighted(const Graph& graph, const std::string& filename) const {
    Graph spanningTree = graph.get_span_tree();
    auto treeEdges = spanningTree.getAllEdges();

    std::set<std::pair<size_t, size_t>> treeEdgesSet;
    for (const auto& e : treeEdges) {
        treeEdgesSet.insert({std::min(e.first, e.second), std::max(e.first, e.second)});
    }

    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    file << "graph " << graphName << "_with_spanning_tree {\n";
    file << "    node [shape=circle, style=filled, fillcolor=lightblue];\n\n";

    // Вершины
    file << "    // Vertices\n";
    auto vertices = graph.getAllVertices();
    for (size_t v : vertices) {
        file << "    " << v << ";\n";
    }

    // Рёбра: рёбра остова - синие жирные, остальные - серые тонкие
    file << "\n    // Edges\n";
    auto allEdges = graph.getAllEdges();
    for (const auto& edge : allEdges) {
        size_t u = edge.first;
        size_t v = edge.second;
        auto key = std::make_pair(std::min(u, v), std::max(u, v));

        if (treeEdgesSet.find(key) != treeEdgesSet.end()) {
            // Ребро остова - синее жирное
            file << "    " << u << " -- " << v << " [color=blue, penwidth=3];\n";
        } else {
            // Остальные рёбра - серые тонкие
            file << "    " << u << " -- " << v << " [color=gray, penwidth=1, style=dashed];\n";
        }
    }

    file << "}\n";
    file.close();
}

void DotSerializer::serializeEdge2ConnectedComponents(const Graph& graph, const std::string& filename) const {
    auto components = graph.get_edge_2_connected_components();

    std::vector<std::string> colors = {
            "red", "blue", "green", "orange", "purple", "brown", "cyan", "magenta"
    };

    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    file << "graph " << graphName << "_edge2components_outline {\n";
    file << "    node [shape=circle, style=filled, fillcolor=white];\n";
    file << "    edge [color=gray, penwidth=1];\n\n";

    // Сопоставляем вершину с компонентой
    std::unordered_map<size_t, size_t> vertexToComponent;
    for (size_t i = 0; i < components.size(); i++) {
        auto vertices = components[i].getAllVertices();
        for (size_t v : vertices) {
            vertexToComponent[v] = i;
        }
    }

    // РАМКИ для компонент
    for (size_t i = 0; i < components.size(); i++) {
        file << "    subgraph cluster_" << i << " {\n";
        file << "        label=\"Component " << i << "\";\n";
        file << "        style=dashed;\n";
        file << "        color=" << colors[i % colors.size()] << ";\n";
        file << "        penwidth=3;\n";
        file << "        margin=15;\n\n";

        auto vertices = components[i].getAllVertices();
        for (size_t v : vertices) {
            file << "        " << v << ";\n";
        }

        file << "    }\n\n";
    }

    // Рёбра
    auto edges = graph.getAllEdges();
    for (const auto& edge : edges) {
        size_t u = edge.first;
        size_t v = edge.second;

        if (vertexToComponent[u] != vertexToComponent[v]) {
            file << "    " << u << " -- " << v << " [color=red, penwidth=3];\n";
        } else {
            file << "    " << u << " -- " << v << " [color=black, penwidth=1];\n";
        }
    }

    file << "}\n";
    file.close();
}