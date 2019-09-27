#ifndef MATRIXGRAPH_HPP
#define MATRIXGRAPH_HPP

#include "Graph.hpp"

class MatrixGraph : public Graph
{
    protected:
        std::vector<std::vector<double>> adjacencyMatrix;

    public:
        MatrixGraph(bool oriented, bool weighted);

        auto addNode(std::string label) -> bool;
        auto addEdge(size_t from, size_t to, double weight = 1) -> bool;

        auto getEdgeWeight(size_t from, size_t to) -> double;
        auto getNeighbors(size_t edgeIndex) -> std::vector<size_t>;

        auto getTypeName() -> std::string;
        auto printToStream(std::ostream& stream) -> void;

        static auto readFromStream(std::istream& stream) -> Graph*;
        static auto readFromFile(std::string const& filename) -> Graph*;
};

#endif // MATRIXGRAPH_HPP
