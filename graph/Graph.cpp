#include "Graph.hpp"
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

std::vector<int> Graph::depthFirstSearch(int base)
{
    std::vector<int> sequence;

    std::vector<int> visited(this->labels.size(), 0);
    int visitCount = 0;

    std::stack<int> stack;
    stack.push(base);

    while (!stack.empty()) {
        int node = stack.top();

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

std::vector<int> Graph::breadthFirstSearch(int base)
{
    std::vector<int> sequence;

    std::vector<int> visited(this->labels.size(), 0);
    int visitCount = 0;

    std::queue<int> queue;
    queue.push(base);

    while (!queue.empty()) {
        int node = queue.front();

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
