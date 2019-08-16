#ifndef LISTGRAPH_HPP
#define LISTGRAPH_HPP

#include "Graph.hpp"

class AdjacencyCell
{
    public:
        int index;
        std::string label;
        double weight;

        AdjacencyCell(int index, std::string label, double weight)
            : index(index), label(label), weight(weight) {}
};

class ListGraph : public Graph
{
    protected:
        std::vector<std::vector<AdjacencyCell>> adjacencyList;

        bool nodeExists(int index);

    public:
        ListGraph(bool oriented, bool weighted);

        bool addNode(std::string label);
        bool addEdge(int from, int to, double weight = 1);

        double getEdgeWeight(int from, int to);
        std::vector<int> getNeighbors(int edgeIndex);

        std::string getTypeName();
        void printToStream(std::ostream &stream);
};

#endif // LISTGRAPH_HPP
