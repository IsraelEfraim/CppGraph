#include "MatrixGraph.hpp"

MatrixGraph::MatrixGraph(bool oriented, bool weighted)
    : Graph(oriented, weighted) {}

std::string MatrixGraph::getType()
{
    return std::string("matrix");
}
