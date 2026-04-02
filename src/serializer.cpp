#include "../include/serializer.h"
#include <fstream>
#include <stdexcept>

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