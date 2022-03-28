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

    graph.print();
    std::cout <<graph.shortestPath(0, 19) << std::endl;
}