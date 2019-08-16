#include "ListGraph.hpp"

ListGraph::ListGraph(bool oriented, bool weighted)
    : Graph(oriented, weighted) {}

bool ListGraph::addNode(std::string label)
{
    return true;
}

bool ListGraph::addEdge(int from, int to, double weight)
{
    return true;
}

double ListGraph::getEdgeWeight(int from, int to)
{
    return 0.0;
}

std::vector<int> ListGraph::getNeighbors(int edgeIndex)
{
    return std::vector<int>();
}

std::string ListGraph::getTypeName()
{
    return std::string("List");
}

void ListGraph::printToStream(const std::ostream &stream)
{

}
