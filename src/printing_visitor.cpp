#include "dfs.h"


std::string PrintingVisitor::getSpaces() const {
    return std::string(spaces * 2, ' ');
}

void PrintingVisitor::onInit() {
    std::cout << "=== DFS START ===" << std::endl;
}

void PrintingVisitor::onFinish() {
    std::cout << "=== DFS FINISH ===" << std::endl;
}

void PrintingVisitor::onVertexInitialize(size_t vertex) {
    std::cout << getSpaces() << "[INIT] Vertex: " << vertex << std::endl;
}

void PrintingVisitor::onVertexDiscover(size_t vertex) {
    std::cout << getSpaces() << ">> DISCOVER: " << vertex << std::endl;
    spaces++;
}

void PrintingVisitor::onVertexFinish(size_t vertex) {
    spaces--;
    std::cout << getSpaces() << "<< FINISH: " << vertex << std::endl;
}

void PrintingVisitor::onComponentStart(size_t startVertex) {
    std::cout << "\n[COMPONENT START] from: " << startVertex << std::endl;
}

void PrintingVisitor::onComponentFinish(size_t startVertex) {
    std::cout << "[COMPONENT FINISH]" << std::endl;
}

void PrintingVisitor::onStartVertex(size_t startVertex) {
    std::cout << "[START VERTEX] " << startVertex << std::endl;
}

void PrintingVisitor::onEdgeStart(size_t from, size_t to) {
    std::cout << getSpaces() << "  edge: " << from << " -> " << to << " ... ";
}

void PrintingVisitor::onEdgeFinish(size_t from, size_t to) {
    std::cout << "done" << std::endl;
}

void PrintingVisitor::onTreeEdge(size_t from, size_t to) {
    std::cout << "TREE" << std::endl;
}

void PrintingVisitor::onBackEdge(size_t from, size_t to) {
    std::cout << "BACK (CYCLE!)" << std::endl;
}

void PrintingVisitor::onForwardEdge(size_t from, size_t to) {
    std::cout << "FORWARD" << std::endl;
}

void PrintingVisitor::onCrossEdge(size_t from, size_t to) {
    std::cout << "CROSS" << std::endl;
}