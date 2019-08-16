#include "MatrixGraph.hpp"

MatrixGraph::MatrixGraph(bool oriented, bool weighted)
    : Graph(oriented, weighted) {}

bool MatrixGraph::addNode(std::string label)
{
    return true;
}

bool MatrixGraph::addEdge(int from, int to, double weight)
{
    return true;
}

double MatrixGraph::getEdgeWeight(int from, int to)
{
    return 0.0;
}

std::vector<int> MatrixGraph::getNeighbors(int edgeIndex)
{
    return std::vector<int>();
}

std::string MatrixGraph::getTypeName()
{
    return std::string("Matrix");
}

void MatrixGraph::printToStream(std::ostream &stream)
{

}
