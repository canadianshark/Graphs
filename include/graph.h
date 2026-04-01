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
    virtual void removeEdge(int from, int to) = 0;
    virtual void removeVertex(int id) = 0;
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
        ADJACENCY_LIST
    };

    explicit Graph(RepType rep_);

    Graph(Graph&& other) noexcept = default;

    Graph& operator=(Graph&& other) noexcept = default;

    ~Graph() = default;

    void addVertex(int id) { rep->addVertex(id); };
    void addEdge(int from, int to) { rep->addEdge(from, to); };
    void removeEdge(int from, int to) { rep->removeEdge(from, to); };
    void removeVertex(int id) { rep->removeVertex(id);};
    virtual std::unordered_set<int> getNeighbours(int id) const { return rep->getNeighbours(id); };
    size_t vertexDeg(int id) const { return rep->vertexDeg(id); };
    size_t vertexCount() const { return rep->vertexCount(); };
    size_t edgeCount() const { return rep->edgeCount(); };
    bool hasVertex(int id) const { return rep->hasVertex(id); };
    bool hasEdge(int from, int to) const { return rep->hasEdge(from, to); };

    // Generators
    Graph static create_complete_graph(int vert_n, RepType representantion);
    Graph static create_path_graph(int vert_n, RepType representantion);
    Graph static create_cycle_graph(int vert_n, RepType representantion);
    Graph static create_compl_bipartite(int vert_n, RepType representantion);
    Graph static create_star_graph(int vert_n, RepType representantion);
    Graph static create_tree_graph(int vert_n, RepType representantion);
    Graph static create_cubic_graph(int vert_n, RepType representantion);



};

class AdjacencyList : public GraphRep {
private:
    std::unordered_map<int, std::unordered_set<int>> adj_list;

public:
    void addVertex(int id) override;
    void addEdge(int from, int to) override;
    virtual void removeEdge(int from, int to) override;
    virtual void removeVertex(int id) override;
    virtual std::unordered_set<int> getNeighbours(int id) const override;
    size_t vertexDeg(int id) const override;
    bool hasVertex(int id) const override;
    bool hasEdge(int from, int to) const override;
    size_t vertexCount() const override;
    size_t edgeCount() const override;

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