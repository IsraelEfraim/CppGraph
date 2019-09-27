#ifndef LISTGRAPH_HPP
#define LISTGRAPH_HPP

#include "Graph.hpp"

class AdjacencyCell
{
    public:
        size_t index;
        std::string label;
        double weight;

        AdjacencyCell(size_t index, std::string label, double weight)
            : index(index), label(label), weight(weight) {}
};

class ListGraph : public Graph
{
    protected:
        std::vector<std::vector<AdjacencyCell>> adjacencyList;

    public:
        ListGraph(bool oriented, bool weighted);

        auto addNode(std::string label) -> bool;
        auto addEdge(size_t from, size_t to, double weight = 1) -> bool;

        auto getEdgeWeight(size_t from, size_t to) -> double;
        auto getNeighbors(size_t edgeIndex) -> std::vector<size_t>;

        auto getTypeName() -> std::string;
        auto printToStream(std::ostream& stream) -> void;

        static auto readFromStream(std::istream& stream) -> Graph*;
        static auto readFromFile(std::string const& filename) -> Graph*;
};

#endif // LISTGRAPH_HPP
