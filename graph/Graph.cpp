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

int Graph::getNodeIndex(std::string nodeName)
{
    for (size_t i = 0; i < this->labels.size(); i++) {
        if (this->labels.at(i) == nodeName) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

std::string Graph::getNodeName(int nodeIndex)
{
    return this->labels.at(static_cast<size_t>(nodeIndex));
}

std::vector<std::string> Graph::getLabelVector()
{
    return this->labels;
}

Graph::~Graph() = default;
