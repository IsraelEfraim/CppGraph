#ifndef MATRIXGRAPH_HPP
#define MATRIXGRAPH_HPP

#include "Graph.hpp"

class MatrixGraph : public Graph
{
    public:
        MatrixGraph(bool oriented, bool weighted);

        bool addNode(std::string label);
        bool addEdge(int from, int to, double weight = 1);

        double getEdgeWeight(int from, int to);
        std::vector<int> getNeighbors(int edgeIndex);

        std::string getTypeName();
        void printToStream(std::ostream &stream);
};

#endif // MATRIXGRAPH_HPP
