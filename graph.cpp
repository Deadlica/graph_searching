#include "graph.h"

Graph::Graph(adjacency_list_t &list): list(list) {
    for(int y = 0; y < list.first.size(); y++) //Initializes the adjacency matrix
        matrix.push_back(std::vector<double>(list.first.size(), std::numeric_limits<double>::max()));

    for(auto &e: list.second) //Fills in the connections
        matrix[e.n1][e.n2] = e.weight;
}

void Graph::DFS(int startNode) {
    visited.clear();
    std::stack<int> stackNeighbours; //Clears the stack

    stackNeighbours.push(startNode);
    while(!stackNeighbours.empty()) {
        auto currentNode = stackNeighbours.top();
        visited[currentNode] = true; //Marks as visited
        stackNeighbours.pop();
        getNeighbours(currentNode, stackNeighbours); //Gets neighbours
    }
}

void Graph::BFS(int startNode) {
    visited.clear();
    std::queue<int> queueNeighbours; //Clears the queue

    queueNeighbours.push(startNode);
    while(!queueNeighbours.empty()) {
        auto currentNode = queueNeighbours.front();
        visited[currentNode] = true; //Marks as visited
        queueNeighbours.pop();
        getNeighbours(currentNode, queueNeighbours); //Gets neighbours
    }
}

double Graph::shortestPath(int start, int end) { //Once every vertex is handled once, the extras are deleted since p_queue sorts them by lowest weight
    labeled.clear();
    prioNeighbours.push({0, start});

    while(!prioNeighbours.empty()) {
        auto node = prioNeighbours.top(); //Get next node
        prioNeighbours.pop();

        if(labeled[node.second].second) //Gets rid of node multiples in the p_queue if it's already been labeled
            continue;

        labeled[node.second] = {node.first, true}; //Marks node as finished labeled
        dijkstraNeighbours(node); //Gets adjacent nodes, with the weight to get there
    }

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
    int nodeId = node.second;
    double nodeWeight = node.first;
    for(int adj = 0; adj < matrix[nodeId].size(); adj++) { //Goes through neighbours in the matrix
        if(!labeled[adj].second) { //Neighbour isn't already labeled
            double edgeWeight = matrix[nodeId][adj];
            prioNeighbours.push({nodeWeight + edgeWeight, adj}); //Adds neighbour with nodeWeight + edgeWeight
        }
    }
}