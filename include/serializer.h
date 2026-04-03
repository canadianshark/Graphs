#pragma once
#include "graph.h"
#include <string>

class GraphSerializer {
public:
    virtual ~GraphSerializer() = default;
    virtual void serialize(const Graph& graph, const std::string& filename) const = 0;

};

class DotSerializer : public GraphSerializer {
private:
    std::string graphName;

public:
    explicit DotSerializer(const std::string& name = "G");
    void serialize(const Graph& graph, const std::string& filename) const override;
    void serializeSpanningTreeHighlighted(const Graph& graph, const std::string& filename) const;
    void serializeEdge2ConnectedComponents(const Graph& graph, const std::string& filename) const;
};