#ifndef LISTGRAPH_HPP
#define LISTGRAPH_HPP

#include "Graph.hpp"

class ListGraph : public Graph
{
    public:
        ListGraph(bool oriented, bool weighted);

        bool addNode(std::string label);
        bool addEdge(int from, int to, double weight = 1);

        double getEdgeWeight(int from, int to);
        std::vector<int> getNeighbors(int edgeIndex);

        std::string getTypeName();
        void printToStream(const std::ostream &stream);
};

#endif // LISTGRAPH_HPP
