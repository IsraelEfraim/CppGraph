#ifndef MATRIXGRAPH_HPP
#define MATRIXGRAPH_HPP

#include "Graph.hpp"

class MatrixGraph : public Graph
{
    public:
        MatrixGraph(bool oriented, bool weighted);

        std::string getType();
};

#endif // MATRIXGRAPH_HPP
