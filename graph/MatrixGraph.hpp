#ifndef MATRIXGRAPH_HPP
#define MATRIXGRAPH_HPP

#include "Graph.hpp"

class MatrixGraph : public Graph
{
    protected:
        std::vector<std::vector<double>> adjacencyMatrix;

    public:
        MatrixGraph(bool oriented, bool weighted);

        bool addNode(std::string label);
        bool addEdge(size_t from, size_t to, double weight = 1);

        double getEdgeWeight(size_t from, size_t to);
        std::vector<size_t> getNeighbors(size_t edgeIndex);

        std::string getTypeName();
        void printToStream(std::ostream &stream);
};

#endif // MATRIXGRAPH_HPP
