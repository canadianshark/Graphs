#include "dfs.h"


class SpanningTreeVisitor : public DFSVisitor {
private:
    Graph& tree;
public:
    explicit SpanningTreeVisitor(Graph& g) : tree(g) {}

    void onVertexDiscover(size_t u) override {
        tree.addVertex(u);
    }


    void onTreeEdge(size_t u, size_t v) override {
        tree.addEdge(u, v);
    }
};