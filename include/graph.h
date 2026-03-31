#pragma once
#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

class GraphRep {
public:
    virtual ~GraphRep() = default;

    virtual void addVertex(int id) = 0;
    virtual void addEdge(int from, int to) = 0;
    virtual std::unordered_set<int> getNeighbours(int id) const = 0;
    virtual size_t vertexDeg(int id) const = 0;
    virtual bool hasVertex(int id) const = 0;
    virtual bool hasEdge(int from, int to) const = 0;
    virtual size_t vertexCount() const = 0;
    virtual size_t edgeCount() const = 0;
};

class Graph {
private:
    std::unique_ptr<GraphRep> rep;

public:
    enum class RepType {
        ADJACENCY_MATRIX,
        INCIDENCE_MATRIX,
        ADJACENCY_LIST
    };

    explicit Graph(RepType rep);

    ~Graph() = default;

    void addVertex(int id) { rep->addVertex(id); };
    void addEdge(int from, int to) { rep->addEdge(from, to); };
    virtual std::unordered_set<int> getNeighbours(int id) const { return rep->getNeighbours(id); };
    size_t vertexDeg(int id) const { return rep->vertexDeg(id); };
    size_t vertexCount() const { return rep->vertexCount(); };
    size_t edgeCount() const { return rep->edgeCount(); };
    bool hasVertex(int id) const { return rep->hasVertex(id); };
    bool hasEdge(int from, int to) const { return rep->hasEdge(from, to); };


};

class AdjacencyList : public GraphRep {
private:
    std::unordered_map<int, std::unordered_set<int>> adj_list;

public:
    void addVertex(int id) override;
    void addEdge(int from, int to) override;
    virtual std::unordered_set<int> getNeighbours(int id) const override;
    size_t vertexDeg(int id) const override;
    bool hasVertex(int id) const override;
    bool hasEdge(int from, int to) const override;
    size_t vertexCount() const override;
    size_t edgeCount() const override;

};

//class AdjacencyMatrix : public GraphRep {
//private:
//    size_t vertex;
//    std::vector<std::vector<bool>> matrix;
//
//public:
//    virtual ~AdjacencyMatrix() override;
//    void addVertex(int id) override;
//    void addEdge(int from, int to) override;
//    virtual std::unordered_set<int> getNeighbours(int id) const override;
//    size_t vertexDeg(int id) const override;
//    bool hasVertex(int id) const override;
//    bool hasEdge(int from, int to) const override;
//    size_t vertexCount() const override;
//    size_t edgeCount() const override;
//
// };