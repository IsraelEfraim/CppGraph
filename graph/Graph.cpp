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

auto Graph::prim(size_t base) -> std::vector<Edge> {
    std::vector<Edge> solution;
    std::vector<bool> control(this->labels.size(), true);

    control.at(base) = false;

    size_t controlCount = control.size() - 1;
    while (controlCount > 0) {
        Edge min{ 0, 0, std::numeric_limits<double>::max() };

        for (size_t u = 0; u < control.size(); u++) {
            for (size_t v = 0; v < control.size(); v++) {
                if (control.at(u) ^ control.at(v)) {
                    double weight = this->getEdgeWeight(u, v);
                    if (weight != 0.0 && weight < min.weight) {
                        min = { u, v, weight };
                    }
                }
            }
        }
        solution.push_back(min);

        control.at(min.from) = false;
        control.at(min.to) = false;
        controlCount--;
    }

    return solution;
}

auto Graph::kruskal() -> std::vector<Edge> {
    std::vector<Edge> solution;

    std::map<std::pair<size_t, size_t>, double> control;
    std::vector<std::vector<size_t>> forest;

    for (size_t u = 0; u < this->labels.size(); u++) {
        for (size_t v : this->getNeighbors(u)) {
            if (this->isOriented() || control.find({v, u}) == std::end(control)) {
                control[{u, v}] = this->getEdgeWeight(u, v);
            }
        }
        forest.push_back(std::vector<size_t>{ u });
    }

    while (!control.empty() && forest.size() > 1) {
        Edge min { 0, 0, std::numeric_limits<double>::max() };

        for (auto const& edge : control) {
            if (edge.second < min.weight) {
                min = { edge.first.first, edge.first.second, edge.second };
            }
        }

        control.erase({ min.from, min.to });

        size_t uTree = 0, vTree = 0;

        for (size_t i = 0; i < forest.size(); i++) {
            if (std::find(std::begin(forest.at(i)), std::end(forest.at(i)), min.from) != std::end(forest.at(i))) {
                uTree = i;
            }
            if (std::find(std::begin(forest.at(i)), std::end(forest.at(i)), min.to) != std::end(forest.at(i))) {
                vTree = i;
            }
        }

        if (uTree != vTree) {
            solution.push_back(min);

            for (auto node : forest.at(vTree)) {
                forest.at(uTree).push_back(node);
            }

            forest.erase(std::begin(forest) + static_cast<long>(vTree));
        }
    }

    return solution;
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
