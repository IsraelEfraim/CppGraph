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

std::string Graph::getNodeName(int nodeIndex)
{
    return this->labels.at(static_cast<size_t>(nodeIndex));
}

std::vector<std::string> Graph::getLabelVector()
{
    return this->labels;
}

Graph::~Graph() = default;
