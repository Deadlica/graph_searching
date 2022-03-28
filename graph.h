#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <stack>
#include <queue>
#include <limits>
#include "reader.h"

class Graph {
public:
    explicit Graph(adjacency_list_t &list);

    void DFS(int startNode);
    void BFS(int startNode);

    const double shortestPath(int start, int end);

    void print() const;
    void printVisitedNodes() const;
    void printPath(int start, int end);

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

    const double INF;

    //Containers
    std::vector<std::vector<double>> matrix;
    adjacency_list_t list;
    std::priority_queue<std::pair<weight_t, node_id_t> , std::vector<std::pair<weight_t, node_id_t>>, std::greater<>> adjacentVertices;
    std::map<node_id_t, bool> visited;
    std::map<node_id_t, std::pair<weight_t, bool>> labeled;
    std::map<node_id_t, node_id_t> reversePath;
};

#endif