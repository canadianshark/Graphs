#pragma once
#include <memory>
#include <vector>
#include <string>
#include <unordered_map>

class Graph {
public:
    enum class Representation {
        ADJACENCY_MATRIX,
        INCIDENCE_MATRIX,
        ADJACENCY_LIST
    };

    explicit Graph(Representation rep);
    ~Graph();

    void addVertex(int id);
    void addEdge(int from, int to, double weight = 1.0);
    size_t vertexCount() const;
    size_t edgeCount() const;

private:
    class Impl;
    std::unique_ptr<Impl> pImpl;
};

class GraphRepresentation {
public:
    virtual ~GraphRepresentation() = default;

    virtual void addVertex(int id) = 0;
    virtual void addEdge(int from, int to, double weight) = 0;
    virtual bool hasVertex(int id) const = 0;
    virtual bool hasEdge(int from, int to) const = 0;
    virtual size_t vertexCount() const = 0;
    virtual size_t edgeCount() const = 0;
};

class Graph::Impl {
private:
    std::unique_ptr<GraphRepresentation> rep;

public:
    explicit Impl(Representation repType);


    void addVertex(int id) { rep->addVertex(id); }
    void addEdge(int from, int to, double weight) { rep->addEdge(from, to, weight); }
    bool hasVertex(int id) const { return rep->hasVertex(id); }
    bool hasEdge(int from, int to) const { return rep->hasEdge(from, to); }
    size_t vertexCount() const { return rep->vertexCount(); }
    size_t edgeCount() const { return rep->edgeCount(); }
};


