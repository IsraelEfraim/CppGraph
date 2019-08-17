#include "Graph.hpp"

Graph::Graph(bool oriented, bool weighted)
    : labels(std::vector<std::string>()), oriented(oriented), weighted(weighted) {}

bool Graph::isOriented()
{
    return this->oriented;
}

bool Graph::isWeighted()
{
    return this->weighted;
}

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

std::string Graph::getNodeName(size_t nodeIndex)
{
    return this->labels.at(nodeIndex);
}

std::vector<std::string> Graph::getLabelVector()
{
    return this->labels;
}

Graph::~Graph() = default;
