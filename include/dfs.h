#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>

class Graph;

enum class VertexColor {
   WHITE,
   GRAY,
   BLACK
};

class DFSVisitor {
public:


    virtual ~DFSVisitor() = default;

    // Глобальные события
    virtual void onInit() {}
    virtual void onFinish() {}

    // События для вершин
    virtual void onVertexInitialize(size_t vertex) {}
    virtual void onVertexDiscover(size_t vertex) {}
    virtual void onVertexFinish(size_t vertex) {}

    // События для компонент связности
    virtual void onComponentStart(size_t startVertex) {}
    virtual void onComponentFinish(size_t startVertex) {}
    virtual void onStartVertex(size_t startVertex) {}

    // События для рёбер
    virtual void onEdgeStart(size_t from, size_t to) {}
    virtual void onEdgeFinish(size_t from, size_t to) {}
    virtual void onTreeEdge(size_t from, size_t to) {}
    virtual void onBackEdge(size_t from, size_t to) {}
    virtual void onForwardEdge(size_t from, size_t to) {}
    virtual void onCrossEdge(size_t from, size_t to) {}
};

class DFS {
private:
    const Graph& graph;
    std::unique_ptr<DFSVisitor> visitor;

    std::unordered_map<size_t, VertexColor> color;
    std::unordered_map<size_t, size_t> parent;
    size_t currentTime;

    void dfsVisit(size_t u);

public:
    explicit DFS(const Graph& g, std::unique_ptr<DFSVisitor> vis = nullptr);

    void traverseFrom(size_t start);
    void traverse();

    const std::unordered_map<size_t, size_t>& getParent() const;
};

class PrintingVisitor : public DFSVisitor {
private:
    int spaces = 0;
    std::string getSpaces() const;



public:
    PrintingVisitor() = default;
    ~PrintingVisitor() = default;

    void onInit() override;
    void onFinish() override;
    void onVertexInitialize(size_t vertex) override;
    void onVertexDiscover(size_t vertex) override;
    void onVertexFinish(size_t vertex) override;
    void onComponentStart(size_t startVertex) override;
    void onComponentFinish(size_t startVertex) override;
    void onStartVertex(size_t startVertex) override;
    void onEdgeStart(size_t from, size_t to) override;
    void onEdgeFinish(size_t from, size_t to) override;
    void onTreeEdge(size_t from, size_t to) override;
    void onBackEdge(size_t from, size_t to) override;
    void onForwardEdge(size_t from, size_t to) override;
    void onCrossEdge(size_t from, size_t to) override;
};