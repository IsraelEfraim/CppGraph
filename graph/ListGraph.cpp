#include "ListGraph.hpp"

ListGraph::ListGraph(bool oriented, bool weighted)
    : Graph(oriented, weighted), adjacencyList(std::vector<std::vector<AdjacencyCell>>()) {}

auto ListGraph::addNode(std::string label) -> bool {
    this->labels.push_back(label);
    this->adjacencyList.push_back(std::vector<AdjacencyCell>());
    return true;
}

auto ListGraph::addEdge(size_t from, size_t to, double weight) -> bool {
    if (!weighted) {
        weight = 1.0;
    }

    bool selfLoop = oriented || (!oriented && from != to);

    if (this->getEdgeWeight(from, to) == 0.0) {
        if (selfLoop && this->nodeExists(from) && this->nodeExists(to)) {
            this->adjacencyList.at(from).push_back(AdjacencyCell(to, this->getNodeName(to), weight));
            if (!oriented) {
                this->adjacencyList.at(to).push_back(AdjacencyCell(from, this->getNodeName(from), weight));
            }
            return true;
        }
    }

    return false;
}


auto ListGraph::getEdgeWeight(size_t from, size_t to) -> double {
    double weight = 0.0;

    if (this->nodeExists(from) && this->nodeExists(to)) {
        for (auto it: this->adjacencyList.at(from)) {
            if (it.index == to) {
                weight = it.weight;
                break;
            }
        }
    }

    return weight;
}

auto ListGraph::getNeighbors(size_t edgeIndex) -> std::vector<size_t> {
    std::vector<size_t> neighbors;

    if (this->nodeExists(edgeIndex)) {
        for (AdjacencyCell it : adjacencyList.at(edgeIndex)) {
            neighbors.push_back(it.index);
        }
    }

    return neighbors;
}

auto ListGraph::getTypeName() -> std::string {
    return std::string("List");
}

auto ListGraph::printToStream(std::ostream& stream) -> void {
    for (size_t i = 0; i < this->adjacencyList.size(); i++) {
        std::string label = this->getNodeName(i);
        stream << label << " -> ";

        for (auto cell: this->adjacencyList.at(i)) {
            stream << "[" << cell.label << ":" << cell.weight << "], ";
        }

        stream << std::endl;
    }
}

auto ListGraph::readFromStream(std::istream& stream) -> Graph* {
    size_t numNodes = 0, numEdges = 0, oriented = 0, weighted = 0;
    stream >> numNodes >> numEdges >> oriented >> weighted;

    Graph* g = new ListGraph(oriented, weighted);
    Graph::fillFromStream(g, stream, numNodes, numEdges, weighted);

    return g;
}

auto ListGraph::readFromFile(std::string const& filename) -> Graph* {
    std::ifstream file(filename);

    return ListGraph::readFromStream(file);
}
