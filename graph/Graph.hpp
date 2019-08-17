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

        bool nodeExists(size_t index);

    public:
        Graph(bool oriented, bool weighted);

        virtual bool addNode(std::string label) = 0;
        virtual bool addEdge(size_t from, size_t to, double weight = 1) = 0;
        bool addEdge(std::string edge, double weight = 1);

        virtual double getEdgeWeight(size_t from, size_t to) = 0;
        virtual std::vector<size_t> getNeighbors(size_t edgeIndex) = 0;

        bool isOriented();
        bool isWeighted();

        size_t getNodeIndex(std::string nodeName);
        std::string getNodeName(size_t nodeIndex);
        std::vector<std::string> getLabelVector();

        virtual std::string getTypeName() = 0;
        virtual void printToStream(std::ostream &stream) = 0;

        virtual ~Graph() = 0;
};

#endif // GRAPH_HPP
