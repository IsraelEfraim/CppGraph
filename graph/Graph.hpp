#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <tuple>
#include <map>
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

        virtual auto addNode(std::string label) -> bool = 0;
        virtual auto addEdge(size_t from, size_t to, double weight = 1) -> bool = 0;
        auto addEdge(std::string edge, double weight = 1) -> bool;

        virtual auto getEdgeWeight(size_t from, size_t to) -> double = 0;
        virtual auto getNeighbors(size_t edgeIndex) -> std::vector<size_t> = 0;

        /* Navigation */
        auto depthFirstSearch(size_t base) -> std::vector<size_t>;
        auto breadthFirstSearch(size_t base) -> std::vector<size_t>;
        auto dijkstra(size_t base) -> std::vector<std::pair<double, size_t>>;

        /* Coloring */
        template <typename ColorType>
        auto welshPowell(std::vector<ColorType> const& colors) -> std::vector<ColorType>;

        template <typename ColorType>
        auto dsatur(std::vector<ColorType> const& colors) -> std::vector<ColorType>;

        auto isOriented() -> bool;
        auto isWeighted() -> bool;

        auto getNodeCount() -> size_t;

        auto getNodeIndex(std::string nodeName) -> size_t;
        auto getNodeName(size_t nodeIndex) -> std::string;
        auto getLabelVector() -> std::vector<std::string>;

        virtual auto getTypeName() -> std::string = 0;
        virtual auto printToStream(std::ostream& stream) -> void = 0;

        template <typename GraphType>
        static auto readFromStream(std::istream& stream) -> Graph*;

        template <typename GraphType>
        static auto readFromFile(std::string const& filename) -> Graph*;

        virtual ~Graph() = 0;
};

/* Reads a graph, given its type, from any input stream */
template <typename GraphType>
auto Graph::readFromStream(std::istream& stream) -> Graph* {
    size_t numNodes = 0, numEdges = 0, oriented = 0, weighted = 0;
    stream >> numNodes >> numEdges >> oriented >> weighted;

    Graph* g = new GraphType(oriented, weighted);

    size_t remainingNodes = numNodes,
           remainingEdges = numEdges;

    while (stream.good() && remainingNodes > 0) {
       std::string node;
       stream >> node;

       if (stream.good()) {
           g->addNode(node);
           remainingNodes--;
       }
    }

    while (stream.good() && remainingEdges > 0) {
        double weight = 1.0;
        size_t from, to;

        stream >> from >> to;

        if (weighted) {
            stream >> weight;
        }

        if (stream.good()) {
            g->addEdge(from, to, weight);
        }
    }

    return g;
}

/* Reads a graph, given its type, from a file */
template <typename GraphType>
auto Graph::readFromFile(std::string const& filename) -> Graph* {
    std::ifstream file(filename);
    return Graph::readFromStream<GraphType>(file);
}

/* Welsh & Powell Coloring Algorithm */
template <typename ColorType>
auto Graph::welshPowell(std::vector<ColorType> const& colors)-> std::vector<ColorType> {
    std::vector<ColorType> colored(this->labels.size());

    /* Store already colored nodes */
    std::vector<bool> alreadyColored(this->labels.size(), false);
    size_t countColored = 0;

    std::vector<std::pair<size_t, size_t>> degreeMap;
    for (size_t i = 0; i < this->labels.size(); i++) {
        degreeMap.push_back({ i, this->getNeighbors(i).size() }); /* { node, degree } */
    }

    /* Sort all pairs from degreeMap vector by their degree */
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

                /* Check on the current node's neighbors' colors */
                for (auto neighbor : neighbors) {
                    if (alreadyColored.at(neighbor) && colored.at(neighbor) == color) {
                        sameColor++;
                    }
                }

                /* If no neighbor was assigned this color, assign it
                   to the current node */
                if (sameColor == 0) {
                    colored.at(node.first) = color;
                    alreadyColored.at(node.first) = true;
                    countColored++;
                }
            }
        }

        current++;
    }

    return colored;
}

/* DSatur coloring algorithm */
template <typename ColorType>
auto Graph::dsatur(std::vector<ColorType> const& colors) -> std::vector<ColorType> {

    /* Node index, degree and saturation */
    using SaturTuple = std::tuple<size_t, size_t, size_t>;

    /* Store already colored nodes */
    std::vector<ColorType> colored(this->labels.size());
    std::vector<bool> alreadyColored(this->labels.size(), false);

    std::vector<SaturTuple> saturMap;

    for (size_t i = 0; i < this->labels.size(); i++) {
        saturMap.push_back({ i, this->getNeighbors(i).size(), 0 });
    }

    /* Sort records by their degree */
    std::sort(std::begin(saturMap), std::end(saturMap), [] (SaturTuple const& l, SaturTuple const& r) -> bool {
        return std::get<1>(l) > std::get<1>(r);
    });

    /* 'node' refers to the node index on the graph*/
    size_t node = 0, countColored = 0;
    while (countColored < saturMap.size()) {

        /* curNode refers to the current node index on the saturation map */
        size_t curNode = std::get<0>(saturMap.at(node));
        auto neighbors = this->getNeighbors(curNode);

        std::map<ColorType, size_t> neighborsColors;
        ColorType available;

        /* Count ocurrence of colors in neighbors */
        for (auto neighbor : neighbors) {
            if (alreadyColored.at(neighbor)) {
                neighborsColors[colored.at(neighbor)]++;
            }
        }

        /* Get the first one that isn't assigned to an neighbor */
        for (auto color : colors) {
            if (neighborsColors[color] == 0) {
                available = color;
                break;
            }
        }

        colored.at(curNode) = available;
        alreadyColored.at(curNode) = true;
        countColored++;

        /* Update neighbors' saturation */
        for (auto neighbor : neighbors) {
            if (!alreadyColored.at(neighbor)) {
                std::map<ColorType, size_t> saturation;

                /* Build histogram of its neighbors' colors */
                for (auto n : this->getNeighbors(neighbor)) {
                    if (alreadyColored.at(n)) {
                        saturation[colored.at(n)]++;
                    }
                }

                /* Its saturation is equal to the size of the map of neighbors' colors */
                for (size_t i = 0; i < saturMap.size(); i++) {
                    if (std::get<0>(saturMap.at(i)) == neighbor) {
                        std::get<2>(saturMap.at(i)) = saturation.size();
                        break;
                    }
                }
            }
        }

        /* Set the next node to be colored as the one with biggest saturation and degree */
        size_t mostSaturated = 0, biggestDegree = 0;
        for (size_t i = 0; i < saturMap.size(); i++) {
            if (!alreadyColored.at(std::get<0>(saturMap.at(i)))) {
                size_t curDegree = std::get<1>(saturMap.at(i)),
                       curSaturation = std::get<2>(saturMap.at(i));

                if (curSaturation > mostSaturated
                    || (curSaturation == mostSaturated && curDegree > biggestDegree)) {
                    node = i;
                    biggestDegree = curDegree;
                    mostSaturated = curSaturation;
                }
            }
        }
    }

    return colored;
}

#endif // GRAPH_HPP
