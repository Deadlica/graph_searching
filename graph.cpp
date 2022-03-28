#include "graph.h"

Graph::Graph(adjacency_list_t &list): list(list) {
    for(int y = 0; y < list.first.size(); y++) {
        std::vector<double> row;
        for(int x = 0; x < list.first.size(); x++) {
            row.push_back(0);
        }
        matrix.push_back(row);
    }

    for(auto &e: list.second) {
        matrix[e.n1][e.n2] = e.weight;
    }
}

void Graph::DFS(int startNode) {
    visited.clear();
    std::stack<int> stackNeighbours; //Clears the stack

    stackNeighbours.push(startNode);
    while(!stackNeighbours.empty()) {
        auto currentNode = stackNeighbours.top();
        visited[currentNode] = true;
        stackNeighbours.pop();
        getNeighbours(currentNode, stackNeighbours);
    }
}

void Graph::BFS(int startNode) {
    visited.clear();
    std::queue<int> queueNeighbours; //Clears the queue

    queueNeighbours.push(startNode);
    while(!queueNeighbours.empty()) {
        auto currentNode = queueNeighbours.front();
        visited[currentNode] = true;
        queueNeighbours.pop();
        getNeighbours(currentNode, queueNeighbours);
    }
}

double Graph::shortestPath(int start, int end) {
    prioNeighbours.push({0, start});
    while(!prioNeighbours.empty()) {
        auto currentNode = prioNeighbours.top();
        prioNeighbours.pop();
        dijkstraNeighbours(currentNode); //Adds adjacent nodes, the weight from start to them
        labeled[currentNode.second] = {currentNode.first, true};
    }
    /*for(auto e: labeled) {
        std::cout << "Node: " << e.first << ", weight: " << e.second.first << std::endl;
    }*/
    return labeled[end].first;
}

void Graph::print() const {
    for(auto e: matrix) {
        for(auto a: e) {
            std::cout << a << "   ";
        }
        std::cout << std::endl;
    }
}

void Graph::printVisitedNodes() const {
    std::cout << "Visited Nodes:" << std::endl;
    for(auto e: visited) {
        std::cout << e.first << " ";
    }
    std::cout << std::endl;
}

void Graph::dijkstraNeighbours(std::pair<weight_t, node_id_t> node) {
    for(int i = 0; i < matrix[node.second].size(); i++) {
        double neighbourWeight = matrix[node.second][i];
        if(neighbourWeight && !labeled[i].second) {
            prioNeighbours.push({node.first + neighbourWeight, i});
        }
    }
}
