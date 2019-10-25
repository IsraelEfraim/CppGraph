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

    /* Track visited nodes sequence */
    std::vector<size_t> visited(this->labels.size(), 0);
    unsigned int visitCount = 0;

    std::stack<size_t> stack;
    stack.push(base);

    /* While there's no node left to visit */
    while (!stack.empty()) {
        size_t node = stack.top();

        /* Mark current node visit sequence */
        if (visited.at(node) == 0) {
            sequence.push_back(node);
            visited.at(node) = ++visitCount;
        }

        /* Search the current node's neighbors */
        auto neighbors = this->getNeighbors(node);
        size_t visitedNeighbors = 0;

        /* Add all the neighbors that weren't visited
           to the stack. Visit those which weren't visited
           before adding the others */
        for (size_t i = 0; i < neighbors.size(); i++) {
            /* If current neighbor wasn't visited, add it to stack
               and visit it */
            if (visited.at(neighbors.at(i)) == 0) {
                stack.push(neighbors.at(i));
                break;
            }
            visitedNeighbors++;
        }

        /* If all neighbors were visited, remove the
           current node from the stack */
        if (visitedNeighbors == neighbors.size())
            stack.pop();
    }

    return sequence;
}

auto Graph::breadthFirstSearch(size_t base) -> std::vector<size_t> {
    std::vector<size_t> sequence;

    /* Track visited nodes sequence */
    std::vector<size_t> visited(this->labels.size(), 0);
    unsigned visitCount = 0;

    /* Create queue structure */
    std::queue<size_t> queue;
    queue.push(base);

    /* While there's no node left to visit */
    while (!queue.empty()) {
        size_t node = queue.front();

        /* Mark current node visit sequence */
        if (visited.at(node) == 0) {
            sequence.push_back(node);
            visited.at(node) = ++visitCount;
        }

        /* Search the current node's neighbors */
        auto neighbors = this->getNeighbors(node);

        /* Enqueue all neighbors that weren't already visited */
        for (size_t i = 0; i < neighbors.size(); i++) {
            if (visited.at(neighbors.at(i)) == 0) {
                queue.push(neighbors.at(i));
            }
        }

        /* Remove the current node from the queue */
        queue.pop();
    }

    return sequence;
}

auto Graph::dijkstra(size_t base) -> std::vector<std::pair<double, size_t>> {
    /* Create dijkstra pathing structure */
    std::vector<std::pair<double, size_t>> distanceMap(this->labels.size(), { std::numeric_limits<double>::max(), 0 });
    std::vector<bool> closedMap(this->labels.size(), false);

    /* If initial node exists */
    if (this->nodeExists(base)) {
        size_t node = base;

        /* The first node has no pathing cost */
        distanceMap.at(node).first = 0.0;

        bool shouldLoop = true;
        while (shouldLoop) {
            /* Search current node's neighbors */
            auto neighbors = this->getNeighbors(node);

            /* Update neighbors pathing cost */
            for (auto neighbor : neighbors) {
                /* The distance is equal to the current node's cost
                   plus the edge between it and the neighbor */
                double distance = distanceMap.at(node).first + this->getEdgeWeight(node, neighbor);

                /* Update the distance and previous node
                   if the new distance is less than the
                   current neighbor cost */
                if (distance < distanceMap.at(neighbor).first) {
                    distanceMap.at(neighbor).first = distance;
                    distanceMap.at(neighbor).second = node;
                }
            }

            closedMap.at(node) = true;
            shouldLoop = false;

            double smallerDistance = std::numeric_limits<double>::max();

            /* Search for the least pathing cost open node */
            for (size_t i = 0; i < distanceMap.size(); i++) {
                if (!closedMap.at(i) && distanceMap.at(i).first < std::numeric_limits<double>::max()) {
                    /* The next while iteration must happen */
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
    /* Create solution and control vector */
    std::vector<Edge> solution;
    std::vector<bool> control(this->labels.size(), true);

    /* Remove an arbitrary node (specified by the caller) from the control */
    control.at(base) = false;

    size_t controlCount = control.size() - 1;
    while (controlCount > 0) {
        /* Declare a minimum weight edge with max possible weight */
        Edge min{ 0, 0, std::numeric_limits<double>::max() };

        /* Search all edges */
        for (size_t u = 0; u < control.size(); u++) {
            for (size_t v = 0; v < control.size(); v++) {
                /* u and v cannot be both in or out of the control */
                if (control.at(u) ^ control.at(v)) {
                    double weight = this->getEdgeWeight(u, v);
                    if (weight != 0.0 && weight < min.weight) {
                        min = { u, v, weight };
                    }
                }
            }
        }

        /* Add edge to the solution */
        solution.push_back(min);

        /* Remove (set to false) from the control */
        control.at(min.from) = false;
        control.at(min.to) = false;
        controlCount--;
    }

    return solution;
}

auto Graph::kruskal() -> std::vector<Edge> {
    std::vector<Edge> solution;

    /* Create the control and forest */
    std::map<std::pair<size_t, size_t>, double> control;
    std::vector<size_t> forest;

    /* Populate control and forest */
    for (size_t u = 0; u < this->labels.size(); u++) {
        for (size_t v : this->getNeighbors(u)) {
            /* Add unique edges */
            if (this->isOriented() || control.find({v, u}) == std::end(control)) {
                double weight = this->getEdgeWeight(u, v);
                if (weight != 0.0) {
                    control[{u, v}] = weight;
                }
            }
        }

        /* Each initial tree in the forest will have
           the same index as the nodes. */
        forest.push_back(u);
    }

    size_t remainingTrees = forest.size();
    while (!control.empty() && remainingTrees > 1) {
        /* Declare a minimum weight edge with max possible weight */
        Edge min { 0, 0, std::numeric_limits<double>::max() };

        /* Search for the minimum weight edge inside control */
        for (auto const& edge : control) {
            if (edge.second < min.weight) {
                min = { edge.first.first, edge.first.second, edge.second };
            }
        }

        /* Remove that edge from the control */
        control.erase({ min.from, min.to });

        /* Get u's and v's tree index */
        size_t uTree = forest.at(min.from),
               vTree = forest.at(min.to);

        /* If they're in different trees, add the found edge
           to the solution and merge the trees. */
        if (uTree != vTree) {
            solution.push_back(min);

            /* Merge v tree into u */
            for (auto& node : forest) {
                if (node == vTree) {
                    node = uTree;
                }
            }

            remainingTrees--;
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
