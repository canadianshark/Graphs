#pragma once
#include "./graph.h"
#include <string>

class Parser {
public:
    virtual ~Parser() = default;
    virtual void parse (Graph& graph, const std::string& filename) const = 0;
};

class ListParser : public Parser {
private:
    std::string graphName;

public:
    explicit ListParser (const std::string& name = "G");
    void parse (Graph& graph, const std::string& filename) const override;
};

class MatrixParser : public Parser {
private:
    std::string graphName;

public:
    explicit MatrixParser (const std::string& name = "G");
    void parse (Graph& graph, const std::string& filename) const override;
};