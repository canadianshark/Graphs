#include "../include/parser.h"
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>

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

void DimacsParser::parse(Graph &G, const std::string &filename) const {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }

    size_t expected_vertices = 0;
    size_t expected_edges = 0;
    size_t line_num = 0;
    size_t edges_read = 0;

    std::string line;
    while (std::getline(file, line)) {
        line_num++;

        // Удаляем \r в конце для Windows
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        // Пропускаем пустые строки
        if (line.empty()) {
            continue;
        }

        // НАХОДИМ ПЕРВЫЙ НЕ-ПРОБЕЛЬНЫЙ СИМВОЛ
        size_t pos = 0;
        while (pos < line.size() && std::isspace(line[pos])) {
            pos++;
        }

        // Если строка состоит только из пробелов
        if (pos >= line.size()) {
            continue;
        }

        char type = line[pos];

        // Обработка комментариев
        if (type == 'c') {
            // Пропускаем комментарии
            continue;
        }
            // Обработка строки проблемы
        else if (type == 'p') {
            std::istringstream iss(line.substr(pos + 1));
            std::string problem_type;
            if (!(iss >> problem_type >> expected_vertices >> expected_edges)) {
                std::cerr << "Warning: Malformed problem line at line " << line_num << std::endl;
                continue;
            }

            if (problem_type != "edge") {
                throw std::runtime_error("Unsupported problem type: " + problem_type);
            }

            std::cout << "Info: Creating graph with " << expected_vertices
                      << " vertices and " << expected_edges << " edges." << std::endl;

            // Добавляем все вершины
            for (size_t i = 1; i <= expected_vertices; ++i) {
                G.addVertex(i);
            }
        }
            // Обработка строк рёбер
        else if (type == 'e') {
            if (expected_vertices == 0) {
                std::cerr << "Warning: Found edge before problem line at line " << line_num << ". Skipping." << std::endl;
                continue;
            }

            std::istringstream iss(line.substr(pos + 1));
            size_t u, v;
            if (!(iss >> u >> v)) {
                std::cerr << "Warning: Malformed edge line at line " << line_num << std::endl;
                continue;
            }

            // Добавляем ребро
            G.addEdge(u, v);
            edges_read++;

            // Прогресс-бар для больших файлов
            if (edges_read % 10000 == 0) {
                std::cout << "  Read " << edges_read << " edges..." << std::endl;
            }
        }
        else {
            // Если первый символ не c, не p, не e - выводим предупреждение
            std::cout << "Ignoring unknown line starting with '" << type
                      << "' at line " << line_num << std::endl;
            // Выводим первые 50 символов строки для отладки
            std::cout << "  Line content: \"" << line.substr(0, 50) << "\"" << std::endl;
        }
    }

    std::cout << "\n=== DIMACS Parsing Summary ===" << std::endl;
    std::cout << "Expected vertices: " << expected_vertices << std::endl;
    std::cout << "Expected edges:    " << expected_edges << std::endl;
    std::cout << "Actual vertices:   " << G.vertexCount() << std::endl;
    std::cout << "Actual edges:      " << G.edgeCount() << std::endl;
    std::cout << "Edges read:        " << edges_read << std::endl;

    if (expected_edges != G.edgeCount()) {
        std::cerr << "\n!!! Warning: Number of edges read (" << G.edgeCount()
                  << ") does not match expected (" << expected_edges << ") !!!" << std::endl;
    }


}
