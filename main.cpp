#include "reader.h"
#include "graph.h"

int main() {
    system("clear");
    adjacency_list_t list = parse_file("export.txt");
    Graph graph(list);

    //Searches the graph from every starting node
    /*for(auto e: list.first) {
        graph.DFS(e.first);
        std::cout << "Start Node: " << e.first << ", ";
        graph.printVisitedNodes();
    }*/

    std::cout << "Distance: " << graph.shortestPath(24, 37) << std::endl;
    std::cout << "Distance: " << graph.shortestPath(46, 47) << std::endl;
    std::cout << "Distance: " << graph.shortestPath(30, 19) << std::endl;
}