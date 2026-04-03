#include "dfs.h"
#include <set>

struct BridgeData {
    std::set<std::pair<size_t, size_t>> bridges;

};


class BridgeFinderVisitor : public DFSVisitor {
private:
    BridgeData& data;
    std::unordered_map<size_t, size_t> tin, low;
public:

    size_t timer = 0;

    explicit BridgeFinderVisitor(BridgeData& d) : data(d) {}

    void onVertexDiscover(size_t u) override {
        tin[u] = low[u] = ++timer;
    }

    void onBackEdge(size_t u, size_t v) override {
        low[u] = std::min(low[u], tin[v]);
    }

    void onEdgeFinish(size_t u, size_t v) override {
        if (tin.count(v) && tin[v] > tin[u]) { // Это Tree Edge
            low[u] = std::min(low[u], low[v]);
            if (low[v] > tin[u]) { // Условие моста
                data.bridges.insert({std::min(u, v), std::max(u, v)});
            }
        }
    }
};

class BCCBuilderVisitor : public DFSVisitor {
private:
    Graph& target;
    const BridgeData& data;

public:
    BCCBuilderVisitor(Graph& g, const BridgeData& b)
            : target(g), data(b) {}

    void onVertexDiscover(size_t u) override {
        target.addVertex(u);
    }

    void onTreeEdge(size_t u, size_t v) override {
        if (data.bridges.find({std::min(u, v), std::max(u, v)}) == data.bridges.end()) {
            target.addEdge(u, v);
        }
    }

    void onBackEdge(size_t u, size_t v) override {
        target.addEdge(u, v);
    }
};