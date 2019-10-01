#include "Graph.hpp"
#include <algorithm>
#include <limits>
#include <stack>
#include <queue>

Graph::Graph(bool oriented, bool weighted)
    : labels(std::vector<std::string>()), oriented(oriented), weighted(weighted) {}

auto Graph::nodeExists(size_t index) -> bool {
    return (index < this->labels.size());
}

auto Graph::addEdge(std::string edge, double weight) -> bool {
    size_t split = edge.find("-");

    if (split != std::string::npos) {
        size_t from = this->getNodeIndex(edge.substr(0, split));
        size_t to = this->getNodeIndex(edge.substr(split + 1));
        return this->addEdge(from, to, weight);
    }

    return false;
}

auto Graph::getNodeIndex(std::string nodeName) -> size_t {
    for (size_t i = 0; i < this->labels.size(); i++) {
        if (this->labels.at(i) == nodeName) {
            return i;
        }
    }
    return static_cast<size_t>(-1);
}

auto Graph::depthFirstSearch(size_t base) -> std::vector<size_t> {
    std::vector<size_t> sequence;

    std::vector<size_t> visited(this->labels.size(), 0);
    unsigned int visitCount = 0;

    std::stack<size_t> stack;
    stack.push(base);

    while (!stack.empty()) {
        size_t node = stack.top();

        if (visited.at(node) == 0) {
            sequence.push_back(node);
            visited.at(node) = ++visitCount;
        }

        auto neighbors = this->getNeighbors(node);
        size_t visitedNeighbors = 0;

        for (size_t i = 0; i < neighbors.size(); i++) {
            if (visited.at(neighbors.at(i)) == 0) {
                stack.push(neighbors.at(i));
                break;
            }
            visitedNeighbors++;
        }

        if (visitedNeighbors == neighbors.size())
            stack.pop();
    }

    return sequence;
}

auto Graph::breadthFirstSearch(size_t base) -> std::vector<size_t> {
    std::vector<size_t> sequence;

    std::vector<size_t> visited(this->labels.size(), 0);
    unsigned visitCount = 0;

    std::queue<size_t> queue;
    queue.push(base);

    while (!queue.empty()) {
        size_t node = queue.front();

        if (visited.at(node) == 0) {
            sequence.push_back(node);
            visited.at(node) = ++visitCount;
        }

        auto neighbors = this->getNeighbors(node);

        for (size_t i = 0; i < neighbors.size(); i++) {
            if (visited.at(neighbors.at(i)) == 0) {
                queue.push(neighbors.at(i));
            }
        }

        queue.pop();
    }

    return sequence;
}

auto Graph::dijkstra(size_t base) -> std::vector<std::pair<double, size_t>> {
    std::vector<std::pair<double, size_t>> distanceMap(this->labels.size(), { std::numeric_limits<double>::max(), 0 });
    std::vector<bool> closedMap(this->labels.size(), false);

    if (this->nodeExists(base)) {
        size_t node = base;
        distanceMap.at(node).first = 0.0;

        bool shouldLoop = true;
        while (shouldLoop) {
            auto neighbors = this->getNeighbors(node);

            for (auto neighbor : neighbors) {
                double distance = distanceMap.at(node).first + this->getEdgeWeight(node, neighbor);

                if (distance < distanceMap.at(neighbor).first) {
                    distanceMap.at(neighbor).first = distance;
                    distanceMap.at(neighbor).second = node;
                }
            }

            closedMap.at(node) = true;
            shouldLoop = false;

            double smallerDistance = std::numeric_limits<double>::max();

            for (size_t i = 0; i < distanceMap.size(); i++) {
                if (!closedMap.at(i) && distanceMap.at(i).first < std::numeric_limits<double>::max()) {
                    shouldLoop = true;

                    if (distanceMap.at(i).first < smallerDistance) {
                        node = i;
                        smallerDistance = distanceMap.at(i).first;
                    }
                }
            }
        }
    }

    return distanceMap;
}

auto Graph::isOriented() -> bool {
    return this->oriented;
}

auto Graph::isWeighted() -> bool {
    return this->weighted;
}

auto Graph::getNodeCount() -> size_t {
    return this->labels.size();
}

auto Graph::getNodeName(size_t nodeIndex) -> std::string {
    return this->labels.at(nodeIndex);
}

auto Graph::getLabelVector() -> std::vector<std::string> {
    return this->labels;
}

Graph::~Graph() = default;

auto Graph::fillFromStream(Graph* g, std::istream& stream, size_t numNodes, size_t numEdges, bool weighted) -> Graph* {
    size_t remainingNodes = numNodes,
           remainingEdges = numEdges;

    while (stream.good() && remainingNodes > 0) {
       std::string node;
       stream >> node;

       if (stream.good()) {
           g->addNode(node);
           remainingNodes--;
       }
    }

    while (stream.good() && remainingEdges > 0) {
        double weight = 1.0;
        size_t from, to;

        stream >> from >> to;

        if (weighted) {
            stream >> weight;
        }

        if (stream.good()) {
            g->addEdge(from, to, weight);
        }
    }

    return g;
}
