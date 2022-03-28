#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <stack>
#include <queue>
#include "reader.h"

#define NOT_CONNECTED 0

class Graph {
public:
    explicit Graph(adjacency_list_t &list);

    void DFS(int startNode);
    void BFS(int startNode);

    double shortestPath(int start, int end);

    void print() const;
    void printVisitedNodes() const;

private:
    template<typename T>
    void getNeighbours(int node, T &neighbours) {
        for(auto e: list.second) {
            if(e.n1 == node && !visited[e.n2]) {
                neighbours.push(e.n2);
            }
        }
    }
    void dijkstraNeighbours(std::pair<weight_t, node_id_t>);

    std::vector<std::vector<double>> matrix;

    adjacency_list_t list;
    std::priority_queue<std::pair<weight_t, node_id_t> , std::vector<std::pair<weight_t, node_id_t>>, std::greater<std::pair<weight_t, node_id_t>>> prioNeighbours;
    std::map<node_id_t, bool> visited;
    std::map<node_id_t, std::pair<weight_t, bool>> labeled;
};

#endif