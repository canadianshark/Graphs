#pragma once
#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

class GraphRep {
public:
    virtual ~GraphRep() = default;

    virtual void addVertex(size_t id) = 0;
    virtual void addEdge(size_t from, size_t to) = 0;
    virtual void removeEdge(size_t from, size_t to) = 0;
    virtual void removeVertex(size_t id) = 0;
    virtual std::unordered_set<size_t> getNeighbours(size_t id) const = 0;
    virtual size_t vertexDeg(size_t id) const = 0;
    virtual bool hasVertex(size_t id) const = 0;
    virtual bool hasEdge(size_t from, size_t to) const = 0;
    virtual size_t vertexCount() const = 0;
    virtual size_t edgeCount() const = 0;
    virtual std::vector<size_t> getAllVertices() const = 0;
    virtual std::vector<std::pair<size_t, size_t>> getAllEdges() const = 0;
};

class Graph {
private:
    std::unique_ptr<GraphRep> rep;

public:
    enum class RepType {
        ADJACENCY_MATRIX,
        ADJACENCY_LIST
    };

    explicit Graph(RepType rep_);

    Graph(Graph&& other) noexcept = default;

    Graph& operator=(Graph&& other) noexcept = default;

    ~Graph() = default;

    void addVertex(size_t id) { rep->addVertex(id); };
    void addEdge(size_t from, size_t to) { rep->addEdge(from, to); };
    void removeEdge(size_t from, size_t to) { rep->removeEdge(from, to); };
    void removeVertex(size_t id) { rep->removeVertex(id);};
    virtual std::unordered_set<size_t> getNeighbours(size_t id) const { return rep->getNeighbours(id); };
    size_t vertexDeg(size_t id) const { return rep->vertexDeg(id); };
    size_t vertexCount() const { return rep->vertexCount(); };
    size_t edgeCount() const { return rep->edgeCount(); };
    bool hasVertex(size_t id) const { return rep->hasVertex(id); };
    bool hasEdge(size_t from, size_t to) const { return rep->hasEdge(from, to); };
    std::vector<size_t> getAllVertices() const { return rep->getAllVertices(); }
    std::vector<std::pair<size_t, size_t>> getAllEdges() const { return rep->getAllEdges(); }


    Graph static create_complete_graph(size_t vert_n, RepType representantion);
    Graph static create_path_graph(size_t vert_n, RepType representantion);
    Graph static create_cycle_graph(size_t vert_n, RepType representantion);
    Graph static create_compl_bipartite(size_t vert_n, RepType representantion);
    Graph static create_star_graph(size_t vert_n, RepType representantion);
    Graph static create_tree_graph(size_t vert_n, RepType representantion);
    Graph static create_cubic_graph(size_t vert_n, RepType representantion);
};

class AdjacencyList : public GraphRep {
private:
    std::unordered_map<size_t, std::unordered_set<size_t>> adj_list;

public:
    void addVertex(size_t id) override;
    void addEdge(size_t from, size_t to) override;
    virtual void removeEdge(size_t from, size_t to) override;
    virtual void removeVertex(size_t id) override;
    virtual std::unordered_set<size_t> getNeighbours(size_t id) const override;
    size_t vertexDeg(size_t id) const override;
    bool hasVertex(size_t id) const override;
    bool hasEdge(size_t from, size_t to) const override;
    size_t vertexCount() const override;
    size_t edgeCount() const override;
    virtual std::vector<size_t> getAllVertices() const override;
    virtual std::vector<std::pair<size_t, size_t>> getAllEdges() const override;


};

//class AdjacencyMatrix : public GraphRep {
//private:
//    std::vector<std::vector<bool>> matrix;
//    int last_index = 1;
//    std::unordered_map<int, int> index_table;
//
//public:
//    virtual ~AdjacencyMatrix() override = default;
//    void reindex(int id);
//    bool check_by_real_id(int id) const;
//    int real_id(int id) const;
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