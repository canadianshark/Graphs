#include <iostream>
#include <string>
#include <sstream>

#include "../include/graph.h"
#include "../include/serializer.h"
#include "../include/parser.h"

void print_set (std::unordered_set<int> s) {
    if (s.empty()){
        std::cout << "empty!\n";
        return;
    }
    for (int el : s){
        std::cout << el << " ";
    }
    std::cout << "\n";
}

int main (int argn, char* argv[]) {

    size_t v;
    Graph::RepType rep;
    Graph G = Graph::create_complete_graph(0, rep);

    if (argn == 1){
        std::cout << "Usage: run <verteces> <representation> [generator]\n\n";
        
        std::cout << "Verteces: integer\n\n";

        std::cout << "Representations:\n";
        std::cout << "\t-list\tAdjacency list\n";
        std::cout << "\t-matrix\tAdjacency matrix\n\n";
        
        std::cout << "Generators:\n";
        std::cout << "\t-cg\t\tComplete graph\n";
        std::cout << "\t-cb <part>\tComplete bipartite\n";
        std::cout << "\t-t\t\tTree\n";
        std::cout << "\t-s\t\tStar\n";
        std::cout << "\t-cy\t\tCycle\n";
        std::cout << "\t-p\t\tPath\n";
        std::cout << "\t-w\t\tWheel\n";
        std::cout << "\t-comm\t\tCommon\n";
        std::cout << "\t-r <prob>\tRandom\n";
        std::cout << "\t-h\t\tHalin\n";
        std::cout << "\t-cu\t\tCubic\n";
        std::cout << "\t-comp <comp>\tComponents\n";
        std::cout << "\t-parse <path>\tParsing list from file\n";
        return 1;
    }

    if (argn > 1) {
        v = atoi(argv[1]);
    }

    if (argn > 2) {
        if (std::string(argv[2]) == "-list"){
            rep = Graph::RepType::ADJACENCY_LIST;
        } else if (std::string(argv[2]) == "-matrix"){
            rep = Graph::RepType::ADJACENCY_MATRIX;
        } else {
            std::cout << "ERROR Unknown representation type: " << argv[2] << "\n";
            return 1;
        }
    }

    if (argn > 3) {
        
        if (std::string(argv[3]) == "-cg"){
            G = Graph::create_complete_graph(v, rep);   
        }
        if (std::string(argv[3]) == "-cb"){
            if (argn <= 4){
                std::cout << "ERROR Undefined parameter -cb\n";
                return 1;
            }
            G = Graph::create_compl_bipartite(v, atoi(argv[4]), rep);
        }
        if (std::string(argv[3]) == "-t"){
            G = Graph::create_tree_graph(v, rep);
        }
        if (std::string(argv[3]) == "-s"){
            G = Graph::create_star_graph(v, rep);
        }
        if (std::string(argv[3]) == "-cy"){
            G = Graph::create_cycle_graph(v, rep);            
        }
        if (std::string(argv[3]) == "-p"){
            G = Graph::create_path_graph(v, rep);            
        }
        if (std::string(argv[3]) == "-w"){
            G = Graph::create_wheel_graph(v, rep);            
        }
        if (std::string(argv[3]) == "-comm"){
            G = Graph::create_common_graph(v, rep);
        }
        if (std::string(argv[3]) == "-r"){
            if (argn <= 4){
                std::cout << "ERROR Undefined parameter -r\n";
                return 1;
            }
            G = Graph::create_random_graph(v, atof(argv[4]), rep);
        }
        if (std::string(argv[3]) == "-h"){
            G = Graph::create_halin_graph(v, rep);
        }
        if (std::string(argv[3]) == "-cu"){
            G = Graph::create_cubic_graph(v, rep);            
        }
        if (std::string(argv[3]) == "-comp"){
            if (argn <= 4){
                std::cout << "ERROR Undefined parameter -comp\n";
                return 1;
            }
            G = Graph::create_components(v, atoi(argv[4]), rep);            
        }
        if (std::string(argv[3]) == "-parse"){
            if (argn <= 4){
                std::cout << "EROR Unknown file for parsing!\n";
                return 1;
            }
            ListParser LP;
            LP.parse(G, argv[4]);
        }

    } else {
        G = Graph::create_complete_graph(v, rep);
    }
    
    G.print();

    std::cout << "Options:\n";
    std::cout << "\tadd vertex/edge v1 (v2)\n";
    std::cout << "\tremove vertex/edge v1 (v2)\n";
    std::cout << "\tget\n";
    std::cout << "\tprint\n";
    std::cout << "\n";

    std::string line;
    
    while (std::getline(std::cin, line)){
        std::stringstream ss(line);
        std::string action, mode, filepath;
        size_t v1, v2;

        ss >> action;
        if (action == "add"){
            ss >> mode;
            if (mode == "vertex"){
                ss >> v1;
                G.addVertex(v1);
                std::cout << v1 << " is added\n\n";
            } else if (mode == "edge"){
                ss >> v1 >> v2;
                G.addEdge(v1, v2);
                std::cout << "edge (" << v1 << "--" << v2 << ") is added\n\n";
            } else {
                std::cout << "Modes: vertex, edge\n\n";
            }
        } else if (action == "remove"){
            ss >> mode;
            if (mode == "vertex"){
                ss >> v1;
                G.removeVertex(v1);
                std::cout << v1 << " is removed\n\n";
            } else if (mode == "edge"){
                ss >> v1 >> v2;
                G.removeEdge(v1, v2);
                std::cout << "edge (" << v1 << "--" << v2 << ") is removed\n\n";
            } else {
                std::cout << "Modes: vertex, edge\n\n";
            }
        } else if (action == "get") {
            ss >> mode;
            if (mode == "deg"){
                ss >> v1;
                std::cout << G.vertexDeg(v1) << "\n\n";
            } else if (mode == "vCount"){
                std::cout << G.vertexCount() << "\n\n";
            } else if (mode == "eCount"){
                std::cout << G.edgeCount() << "\n\n";
            } else if (mode == "hasV"){
                ss >> v1;
                std::cout << ((G.hasVertex(v1)) ? "yes" : "no") << "\n\n";
            } else if (mode == "hasE"){
                ss >> v1 >> v2;
                std::cout << ((G.hasEdge(v1, v2)) ? "yes" : "no") << "\n\n";
            } else if (mode == "density") {
                std::cout << G.getDensity() << "\n\n";
            } else if (mode == "transitivity"){
                std::cout << G.getTransitivity() << "\n\n";
            } else if (mode == "bipartite") {
                std::cout << ((G.isBipartite()) ? "yes" : "no") << "\n\n";
            } else if (mode == "diameter") {
                std::cout << G.getDiameter() << "\n\n";
            } else if (mode == "components") {
                std::cout << G.componentsCount() << "\n\n";
            } else {
                std::cout << "Unknown mode! Modes available:\n\n";
                std::cout << "deg <vertex>\n";
                std::cout << "vCount\n";
                std::cout << "eCount\n";
                std::cout << "hasV <vertex>\n";
                std::cout << "hasE <v1> <v2>\n";
                std::cout << "density\n";
                std::cout << "transitivity\n";
                std::cout << "diameter\n";
                std::cout << "components\n\n";
            }

        } else if (action == "serialize") {
            ss >> filepath;
            DotSerializer DS;
            DS.serialize(G, filepath); 

        } else if (action == "print"){
            G.print();
        } else {
            std::cout << "Unknown action\n\n";
        }
    }

    return 0;
}
