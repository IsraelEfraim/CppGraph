#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class Graph
{
    protected:
        std::vector<std::string> labels;
        bool oriented;
        bool weighted;

        bool nodeExists(size_t index);

        static auto fillFromStream(Graph* g, std::istream& stream, size_t numNodes, size_t numEdges, bool weighted) -> Graph*;

    public:
        Graph(bool oriented, bool weighted);

        virtual auto addNode(std::string label) -> bool = 0;
        virtual auto addEdge(size_t from, size_t to, double weight = 1) -> bool = 0;
        auto addEdge(std::string edge, double weight = 1) -> bool;

        virtual auto getEdgeWeight(size_t from, size_t to) -> double = 0;
        virtual auto getNeighbors(size_t edgeIndex) -> std::vector<size_t> = 0;

        auto depthFirstSearch(size_t base) -> std::vector<size_t>;
        auto breadthFirstSearch(size_t base) -> std::vector<size_t>;
        auto dijkstra(size_t base) -> std::vector<std::pair<double, size_t>>;

        auto isOriented() -> bool;
        auto isWeighted() -> bool;

        auto getNodeIndex(std::string nodeName) -> size_t;
        auto getNodeName(size_t nodeIndex) -> std::string;
        auto getLabelVector() -> std::vector<std::string>;

        virtual auto getTypeName() -> std::string = 0;
        virtual auto printToStream(std::ostream& stream) -> void = 0;

        virtual ~Graph() = 0;
};



#endif // GRAPH_HPP
