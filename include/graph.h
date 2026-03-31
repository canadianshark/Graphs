#pragma once
#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

class GraphRepresentation {
public:
    virtual ~GraphRepresentation() = default;

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
public:
    enum class RepType {
        ADJACENCY_MATRIX,
        INCIDENCE_MATRIX,
        ADJACENCY_LIST
    };

    explicit Graph(RepType rep);
    ~Graph();

    void addVertex(int id){rep->addVertex(id);};
    void addEdge(int from, int to){rep->addEdge(from, to);};
    virtual std::unordered_set<int> getNeighbours(int id) const {return rep->getNeighbours(id);};
    size_t vertexDeg(int id) const {return rep->vertexDeg(id);};
    size_t vertexCount() const { return  rep->vertexCount();};
    size_t edgeCount() const { return  rep->edgeCount();};
    bool hasVertex(int id) const { return  rep->hasVertex(id);};
    bool hasEdge(int from, int to) const { return rep->hasEdge(from, to);};

private:
    std::unique_ptr<GraphRepresentation> rep;
};

class AdjecencyListRep: GraphRepresentation{
public:
    void addVertex(int id) override;
    void addEdge(int from, int to) override;
    virtual std::unordered_set<int> getNeighbours(int id) const override;
    size_t vertexDeg(int id) const override;
    bool hasVertex(int id) const override;
    bool hasEdge(int from, int to) const override;
    size_t vertexCount() const override;
    size_t edgeCount() const override;

private:
    std::unordered_map<int,std::unordered_set<int>> adj_list;
};

