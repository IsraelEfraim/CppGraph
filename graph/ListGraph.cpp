#include "ListGraph.hpp"

ListGraph::ListGraph(bool oriented, bool weighted)
    : Graph(oriented, weighted) {}

std::string ListGraph::getType()
{
    return std::string("list");
}
