#include "Graph.hpp"
#include <algorithm>
#include <limits>
#include <stack>
#include <queue>

Graph::Graph(bool oriented, bool weighted)
    : labels(std::vector<std::string>()), oriented(oriented), weighted(weighted) {}

bool Graph::nodeExists(size_t index)
{
    return (index < this->labels.size());
}

bool Graph::addEdge(std::string edge, double weight)
{
    size_t split = edge.find("-");

    if (split != std::string::npos) {
        size_t from = this->getNodeIndex(edge.substr(0, split));
        size_t to = this->getNodeIndex(edge.substr(split + 1));
        return this->addEdge(from, to, weight);
    }

    return false;
}

size_t Graph::getNodeIndex(std::string nodeName)
{
    for (size_t i = 0; i < this->labels.size(); i++) {
        if (this->labels.at(i) == nodeName) {
            return i;
        }
    }
    return static_cast<size_t>(-1);
}

std::vector<size_t> Graph::depthFirstSearch(size_t base)
{
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

std::vector<size_t> Graph::breadthFirstSearch(size_t base)
{
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

std::vector<DijkstraCell> Graph::dijkstra(size_t base)
{
    std::vector<DijkstraCell> distanceMap(this->labels.size(),
                                          DijkstraCell(std::numeric_limits<double>::max(), 0, false));

    if (this->nodeExists(base)) {
        size_t node = base;
        distanceMap.at(node).distance = 0.0;

        bool shouldLoop = true;
        while (shouldLoop) {
            auto neighbors = this->getNeighbors(node);

            for (auto neighbor : neighbors) {
                double distance = distanceMap.at(node).distance + this->getEdgeWeight(node, neighbor);

                if (distance < distanceMap.at(neighbor).distance) {
                    distanceMap.at(neighbor).distance = distance;
                    distanceMap.at(neighbor).predecessor = node;
                }
            }

            distanceMap.at(node).closed = true;
            shouldLoop = false;

            double smallerDistance = std::numeric_limits<double>::max();

            for (size_t i = 0; i < distanceMap.size(); i++) {
                if (!distanceMap.at(i).closed && distanceMap.at(i).distance < std::numeric_limits<double>::max()) {
                    shouldLoop = true;

                    if (distanceMap.at(i).distance < smallerDistance) {
                        node = i;
                        smallerDistance = distanceMap.at(i).distance;
                    }
                }
            }
        }
    }

    return distanceMap;
}

bool Graph::isOriented()
{
    return this->oriented;
}

bool Graph::isWeighted()
{
    return this->weighted;
}

std::string Graph::getNodeName(size_t nodeIndex)
{
    return this->labels.at(nodeIndex);
}

std::vector<std::string> Graph::getLabelVector()
{
    return this->labels;
}

Graph::~Graph() = default;
