#pragma once
#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

class Graph;

class GraphRep {
public:
    virtual ~GraphRep() = default;

    virtual void addVertex(size_t id) = 0;
    virtual void addEdge(size_t from, size_t to) = 0;
    virtual void removeEdge(size_t from, size_t to) = 0;
    virtual void removeVertex(size_t id) = 0;
    virtual std::unordered_set<size_t> getNeighbours(size_t id) const = 0;
    virtual std::vector<size_t> getNeighboursShuffled(size_t id) const = 0;
    virtual size_t vertexDeg(size_t id) const = 0;
    virtual bool hasVertex(size_t id) const = 0;
    virtual bool hasEdge(size_t from, size_t to) const = 0;
    virtual size_t vertexCount() const = 0;
    virtual size_t edgeCount() const = 0;
    virtual std::vector<size_t> getAllVertices() const = 0;
    virtual std::vector<std::pair<size_t, size_t>> getAllEdges() const = 0;


    virtual void print() const = 0;
};

class Graph {
public:
    enum class RepType {
        ADJACENCY_MATRIX,
        ADJACENCY_LIST
    };
private:
    std::unique_ptr<GraphRep> rep;
    RepType backend;

public:


    explicit Graph(RepType rep_);

    Graph(Graph&& other) noexcept = default;

    Graph& operator=(Graph&& other) noexcept = default;

    ~Graph() = default;

    RepType get_backend_type() const;


    void addVertex(size_t id) { rep->addVertex(id); };
    void addEdge(size_t from, size_t to) { rep->addEdge(from, to); };
    void removeEdge(size_t from, size_t to) { rep->removeEdge(from, to); };
    void removeVertex(size_t id) { rep->removeVertex(id);};
    virtual std::unordered_set<size_t> getNeighbours(size_t id) const { return rep->getNeighbours(id); };
    std::vector<size_t> getNeighboursShuffled(size_t id) const {return rep->getNeighboursShuffled(id);};
    size_t vertexDeg(size_t id) const { return rep->vertexDeg(id); };
    size_t vertexCount() const { return rep->vertexCount(); };
    size_t edgeCount() const { return rep->edgeCount(); };
    bool hasVertex(size_t id) const { return rep->hasVertex(id); };
    bool hasEdge(size_t from, size_t to) const { return rep->hasEdge(from, to); };
    std::vector<size_t> getAllVertices() const { return rep->getAllVertices(); }
    std::vector<std::pair<size_t, size_t>> getAllEdges() const { return rep->getAllEdges(); }
    void merge(const Graph& other);

    void print () const { rep->print(); };

    Graph get_component_subgraph(size_t id) const;
    Graph get_span_tree() const;
    std::vector<Graph> get_edge_2_connected_components() const;



    // Generators
    Graph static create_complete_graph(size_t vert_n, RepType representantion);
    Graph static create_compl_bipartite(size_t vert_n, size_t vert_m, RepType representantion);
    Graph static create_tree_graph(size_t vert_n, RepType representantion);
    Graph static create_star_graph(size_t vert_n, RepType representantion);
    Graph static create_cycle_graph(size_t vert_n, RepType representantion);
    Graph static create_path_graph(size_t vert_n, RepType representantion);
    Graph static create_wheel_graph(size_t vert_n, RepType representation);
    Graph static create_common_graph(size_t vert_n, Graph::RepType representation);
    Graph static create_random_graph(size_t n, double probability, Graph::RepType representation);
    Graph static create_halin_graph(size_t vert_n, Graph::RepType representation);
    Graph static create_cubic_graph(size_t vert_n, RepType representation);
    Graph static create_components(size_t vert_n, size_t comp_k, RepType rep);
};

class AdjacencyList : public GraphRep {
private:
    std::unordered_map<size_t, std::unordered_set<size_t>> adj_list;
    size_t vertex_num = 0;
    size_t edges_num = 0;

public:
    void addVertex(size_t id) override;
    void addEdge(size_t from, size_t to) override;
    virtual void removeEdge(size_t from, size_t to) override;
    virtual void removeVertex(size_t id) override;
    virtual std::unordered_set<size_t> getNeighbours(size_t id) const override;
    std::vector<size_t> getNeighboursShuffled(size_t id) const override;
    size_t vertexDeg(size_t id) const override;
    bool hasVertex(size_t id) const override;
    bool hasEdge(size_t from, size_t to) const override;
    size_t vertexCount() const override;
    size_t edgeCount() const override;
    virtual std::vector<size_t> getAllVertices() const override;
    virtual std::vector<std::pair<size_t, size_t>> getAllEdges() const override;

    void print() const override;
};

class AdjacencyMatrix : public GraphRep {
private:
    std::unordered_map<size_t , size_t> index_tab;
    std::vector<std::vector<size_t>> matrix;
    size_t vertex_num = 0;
    size_t edges_num = 0;

public:
    void addVertex(size_t id_) override;
    void addEdge(size_t from_,size_t to_) override;
    virtual void removeVertex(size_t id_) override;
    virtual void removeEdge(size_t from_, size_t to_) override;

    virtual std::unordered_set<size_t> getNeighbours(size_t id_) const override;
    std::vector<size_t> getNeighboursShuffled(size_t id) const override;
    size_t vertexDeg(size_t id_) const override;
    bool hasVertex(size_t id_) const override;
    bool hasEdge(size_t from_, size_t to_) const override;

    size_t vertexCount() const override;
    size_t edgeCount() const override;

    virtual std::vector<size_t> getAllVertices() const override;
    virtual std::vector<std::pair<size_t, size_t>> getAllEdges() const override;


    void print() const override;
};

