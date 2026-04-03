#include "../include/graph.h"
#include "../include/dfs.h"

DFS::DFS(const Graph& g, std::unique_ptr<DFSVisitor> vis): graph(g), visitor(std::move(vis)), currentTime(0) {}

void DFS::dfsVisit(size_t u) {
    // ОБНАРУЖЕНИЕ ВЕРШИНЫ
    color[u] = VertexColor::GRAY;

    if (visitor) visitor->onVertexDiscover(u);

    // ОБХОД СОСЕДЕЙ
    for (size_t v : graph.getNeighboursShuffled(u)) {
        if (v == parent[u]) continue;
        if (visitor) visitor->onEdgeStart(u, v);

        if (color[v] == VertexColor::WHITE) {
            parent[v] = u;
            if (visitor) visitor->onTreeEdge(u, v);
            dfsVisit(v);
        }
        else if (color[v] == VertexColor::GRAY) {
            if (visitor) visitor->onBackEdge(u, v);
        }

        if (visitor) visitor->onEdgeFinish(u, v);
    }

    // ЗАВЕРШЕНИЕ ВЕРШИНЫ
    color[u] = VertexColor::BLACK;

    if (visitor) visitor->onVertexFinish(u);
}

void DFS::traverseFrom(size_t start) {
    if (!graph.hasVertex(start)) return;

    if (visitor) visitor->onInit();

    // Инициализация
    for (size_t v : graph.getAllVertices()) {
        color[v] = VertexColor::WHITE;
        parent[v] = v;
        if (visitor) visitor->onVertexInitialize(v);
    }

    currentTime = 0;

    if (visitor) visitor->onStartVertex(start);

    if (color[start] == VertexColor::WHITE) {
        if (visitor) visitor->onComponentStart(start);
        dfsVisit(start);
        if (visitor) visitor->onComponentFinish(start);
    }


    if (visitor) visitor->onFinish();
}

void DFS::traverse() {
    if (visitor) visitor->onInit();

    for (size_t v : graph.getAllVertices()) {
        color[v] = VertexColor::WHITE;
        parent[v] = v;
        if (visitor) visitor->onVertexInitialize(v);
    }

    currentTime = 0;

    for (size_t v : graph.getAllVertices()) {
        if (color[v] == VertexColor::WHITE) {
            if (visitor) visitor->onComponentStart(v);
            dfsVisit(v);
            if (visitor) visitor->onComponentFinish(v);
        }
    }

    if (visitor) visitor->onFinish();
}

const std::unordered_map<size_t, size_t>& DFS::getParent() const {
    return parent;
}






