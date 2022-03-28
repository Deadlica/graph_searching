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

    double dist1 = graph.shortestPath(24, 37);
    std::cout << "Distance: " << dist1 << std::endl;
    double dist2 = graph.shortestPath(46, 47);
    std::cout << "Distance: "  << dist2 << std::endl;
    double dist3 = graph.shortestPath(30, 19);
    std::cout << "Distance: " << dist3 << std::endl;
}