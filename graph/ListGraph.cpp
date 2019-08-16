#include "ListGraph.hpp"

ListGraph::ListGraph(bool oriented, bool weighted)
    : Graph(oriented, weighted), adjacencyList(std::vector<std::vector<AdjacencyCell>>()) {}

bool ListGraph::nodeExists(int index)
{
    return (index >= 0 && index < this->adjacencyList.size());
}

bool ListGraph::addNode(std::string label)
{
    this->labels.push_back(label);
    this->adjacencyList.push_back(std::vector<AdjacencyCell>());
    return true;
}

bool ListGraph::addEdge(int from, int to, double weight)
{
    if (!weighted) {
        weight = 1.0;
    }

    bool selfLoop = oriented || (!oriented && from != to);

    if (selfLoop && this->nodeExists(from) && this->nodeExists(to)) {
        this->adjacencyList.at(from).push_back(AdjacencyCell(to, this->getNodeName(to), weight));
        if (!oriented) {
            this->adjacencyList.at(to).push_back(AdjacencyCell(from, this->getNodeName(from), weight));
        }
        return true;
    }

    return false;
}

double ListGraph::getEdgeWeight(int from, int to)
{
    double weight = 0.0;

    bool selfLoop = oriented || (!oriented && from != to);

    if (selfLoop && this->nodeExists(from) && this->nodeExists(to)) {
        for (auto it: this->adjacencyList.at(from)) {
            if (it.index == to) {
                weight = it.weight;
                break;
            }
        }
    }

    return weight;
}

std::vector<int> ListGraph::getNeighbors(int edgeIndex)
{
    return std::vector<int>();
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
