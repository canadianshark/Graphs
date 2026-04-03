#include "../include/parser.h"
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

ListParser::ListParser (const std::string& name) : graphName(name) {};
MatrixParser::MatrixParser (const std::string& name) : graphName(name) {};

void ListParser::parse (Graph& graph, const std::string& filename) const {
    std::ifstream file(filename);
    if (!file.is_open()){
        throw std::runtime_error("Cannot open file: " + filename);
    }
    
    std::string line;
    std::getline(file, line);
    size_t verteces = stoi(line);

    for (size_t i = 0; i != verteces; ++i){
        std::getline(file, line);
        size_t vertex = stoi(line);
        graph.addVertex(vertex);
    }

    while (std::getline(file, line)){
        size_t v1, v2;
        std::stringstream ss(line);
        ss >> v1 >> v2;
        graph.addEdge(v1, v2);
    }
    
    file.close();
}

void MatrixParser::parse (Graph& graph, const std::string& filename) const {
    std::ifstream file(filename);
    if (!file.is_open()){
        throw std::runtime_error("Cannot open file: " + filename);
    }
    
    std::string line;
    size_t i = 0;
    while (std::getline(file, line)){
        size_t j = 0;
        bool edge;
        std::stringstream ss(line);    
        while (ss >> edge){
            if (edge) graph.addEdge(i, j);
            ++j;
        }
        ++i;
    }
    
    file.close();
}