#include "Graph.hpp"

Graph::Graph(bool oriented, bool weighted)
    : oriented(oriented), weighted(weighted) {}

bool Graph::isOriented()
{
    return this->oriented;
}

bool Graph::isWeighted()
{
    return this->weighted;
}

Graph::~Graph() = default;
