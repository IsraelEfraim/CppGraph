#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <fstream>
#include <algorithm>
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

        /* Navigation bitches */
        auto depthFirstSearch(size_t base) -> std::vector<size_t>;
        auto breadthFirstSearch(size_t base) -> std::vector<size_t>;
        auto dijkstra(size_t base) -> std::vector<std::pair<double, size_t>>;

        /* Coloring */
        template <typename ColorType>
        auto welshPowell(std::vector<ColorType> colors) -> std::vector<std::pair<size_t, ColorType>>;

        auto isOriented() -> bool;
        auto isWeighted() -> bool;

        auto getNodeIndex(std::string nodeName) -> size_t;
        auto getNodeName(size_t nodeIndex) -> std::string;
        auto getLabelVector() -> std::vector<std::string>;

        virtual auto getTypeName() -> std::string = 0;
        virtual auto printToStream(std::ostream& stream) -> void = 0;

        virtual ~Graph() = 0;
};

template <typename ColorType>
auto Graph::welshPowell(std::vector<ColorType> colors)-> std::vector<std::pair<size_t, ColorType>> {
    std::vector<std::pair<size_t, ColorType>> colored(this->labels.size());

    std::vector<bool> alreadyColored(this->labels.size(), false);
    size_t countColored = 0;

    std::vector<std::pair<size_t, size_t>> degreeMap;
    for (size_t i = 0; i < this->labels.size(); i++) {
        degreeMap.push_back({ i, this->getNeighbors(i).size() }); /* { node, degree } */
    }

    std::sort(std::begin(degreeMap), std::end(degreeMap),
    [] (std::pair<size_t, size_t> const& l, std::pair<size_t, size_t> const& r) -> bool {
        return l.second > r.second;
    });

    size_t current = 0;

    while (countColored < degreeMap.size()) {
        auto color = colors.at(current);

        for (size_t j = 0; j < degreeMap.size(); j++) {
            auto node = degreeMap.at(j);

            if (!alreadyColored.at(node.first)) {
                auto neighbors = this->getNeighbors(node.first);
                size_t sameColor = 0;

                for (auto neighbor : neighbors) {
                    if (alreadyColored.at(neighbor) && colored.at(neighbor).second == color) {
                        sameColor++;
                    }
                }

                if (sameColor == 0) {
                    colored.at(node.first) = { node.first, color };
                    alreadyColored.at(node.first) = true;
                    countColored++;
                }
            }
        }

        current++;
    }

    return colored;
}

#endif // GRAPH_HPP
