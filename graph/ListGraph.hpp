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

        bool addNode(std::string label);
        bool addEdge(size_t from, size_t to, double weight = 1);

        double getEdgeWeight(size_t from, size_t to);
        std::vector<size_t> getNeighbors(size_t edgeIndex);

        std::string getTypeName();
        void printToStream(std::ostream &stream);
};

#endif // LISTGRAPH_HPP
