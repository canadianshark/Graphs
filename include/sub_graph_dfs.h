#include "graph.h"
#include "dfs.h"

class SubGraphVisitor : public DFSVisitor {
private:
    Graph& targetGraph;
public:
    explicit SubGraphVisitor(Graph& g) : targetGraph(g) {}

    void onVertexDiscover(size_t u) override {
        targetGraph.addVertex(u);
    }

    void onTreeEdge(size_t u, size_t v) override {
        targetGraph.addEdge(u, v);
    }

    void onBackEdge(size_t u, size_t v) override {
        targetGraph.addEdge(u, v);
    }
};