#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>
#include <string>

class Graph
{
    protected:
        std::vector<std::string> labels;
        bool oriented;
        bool weighted;

    public:
        Graph(bool oriented, bool weighted);

        virtual bool addNode(std::string label) = 0;
        virtual bool addEdge(int from, int to, double weight = 1) = 0;

        virtual double getEdgeWeight(int from, int to) = 0;
        virtual std::vector<int> getNeighbors(int edgeIndex) = 0;

        bool isOriented();
        bool isWeighted();

        std::string getNodeName(int nodeIndex);
        std::vector<std::string> getLabelVector();

        virtual std::string getTypeName() = 0;
        virtual void printToStream(std::ostream &stream) = 0;

        virtual ~Graph() = 0;
};

#endif // GRAPH_HPP
