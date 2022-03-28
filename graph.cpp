#include "graph.h"

Graph::Graph(adjacency_list_t &list): list(list), INF(std::numeric_limits<double>::max()) {
    for(int y = 0; y < list.first.size(); y++) //Initializes the adjacency matrix
        matrix.push_back(std::vector<double>(list.first.size(), INF));

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

const double Graph::shortestPath(int start, int end) { //Once every vertex is handled once, the extras are deleted since p_queue sorts them by lowest weight
    reversePath.clear();
    labeled.clear();
    adjacentVertices.push({0, start});

    while(!adjacentVertices.empty()) {
        auto node = adjacentVertices.top(); //Get next node
        adjacentVertices.pop();
        if(labeled[node.second].second) {continue;} //Gets rid of node multiples in the p_queue if it's already been labeled
        labeled[node.second] = {node.first, true}; //Marks node as finished labeled
        dijkstraNeighbours(node); //Gets adjacent nodes, with the weight to get there
    }

    printPath(start, end);
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

void Graph::printPath(int start, int end) {
    std::cout << "Path from node " << start << " to node " << end << ": ";
    std::vector<int> path;
    path.push_back(end);
    while(end != start) { //Adds backwards path to vector
        path.push_back(reversePath[end]);
        end = reversePath[end];
    }
    std::reverse(path.begin(), path.end()); //Reverses vector
    for(auto e: path) { //Prints path
        std::cout << e << "[" << list.first[e].substr(1) << "]" << "   ";
    }
    std::cout << std::endl;
}

void Graph::dijkstraNeighbours(std::pair<weight_t, node_id_t> node) {
    int nodeId = node.second;
    double nodeWeight = node.first;
    for(int adj = 0; adj < matrix[nodeId].size(); adj++) { //Goes through neighbours in the matrix
        double edgeWeight = matrix[nodeId][adj];
        if(!labeled[adj].second && edgeWeight != INF) { //Neighbour isn't already labeled
            adjacentVertices.push({nodeWeight + edgeWeight, adj}); //Adds neighbour with nodeWeight + edgeWeight
            reversePath[adj] = nodeId; //Tells the adjacent vertex which vertex it came from
        }
    }
}