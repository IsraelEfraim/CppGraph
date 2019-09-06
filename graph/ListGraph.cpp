#include "ListGraph.hpp"

ListGraph::ListGraph(bool oriented, bool weighted)
    : Graph(oriented, weighted), adjacencyList(std::vector<std::vector<AdjacencyCell>>()) {}

bool ListGraph::addNode(std::string label)
{
    this->labels.push_back(label);
    this->adjacencyList.push_back(std::vector<AdjacencyCell>());
    return true;
}

bool ListGraph::addEdge(size_t from, size_t to, double weight)
{
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


double ListGraph::getEdgeWeight(size_t from, size_t to)
{
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

std::vector<size_t> ListGraph::getNeighbors(size_t edgeIndex)
{
    std::vector<size_t> neighbors;

    if (this->nodeExists(edgeIndex)) {
        for (AdjacencyCell it : adjacencyList.at(edgeIndex)) {
            neighbors.push_back(it.index);
        }
    }

    return neighbors;
}

std::string ListGraph::getTypeName()
{
    return std::string("List");
}

void ListGraph::printToStream(std::ostream &stream)
{
    for (size_t i = 0; i < this->adjacencyList.size(); i++) {
        std::string label = this->getNodeName(i);
        stream << label << " -> ";

        for (auto cell: this->adjacencyList.at(i)) {
            stream << "[" << cell.label << ":" << cell.weight << "], ";
        }

        stream << std::endl;
    }
}
