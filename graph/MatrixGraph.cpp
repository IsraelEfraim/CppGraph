#include "MatrixGraph.hpp"

MatrixGraph::MatrixGraph(bool oriented, bool weighted)
    : Graph(oriented, weighted), adjacencyMatrix(std::vector<std::vector<double>>()) {}

auto MatrixGraph::addNode(std::string label) -> bool {
    this->labels.push_back(label);
    this->adjacencyMatrix.push_back(std::vector<double>(this->adjacencyMatrix.size() + 1, 0.0));

    for (size_t i = 0; i < this->adjacencyMatrix.size() - 1; i++) {
        this->adjacencyMatrix.at(i).push_back(0.0);
    }

    return true;
}

auto MatrixGraph::addEdge(size_t from, size_t to, double weight) -> bool {
    if (!this->isWeighted()) {
        weight = 1.0;
    }

    bool selfLoop = this->isOriented() || (!this->isOriented() && from != to);

    if (this->getEdgeWeight(from, to) == 0.0) {
        if (selfLoop && this->nodeExists(from) && this->nodeExists(to)) {
            this->adjacencyMatrix.at(from).at(to) = weight;
            if (!this->isOriented()) {
                this->adjacencyMatrix.at(to).at(from) = weight;
            }
            return true;
        }
    }


    return false;
}

auto MatrixGraph::getEdgeWeight(size_t from, size_t to) -> double {
    if (this->nodeExists(from) && this->nodeExists(to)) {
        return this->adjacencyMatrix.at(from).at(to);
    }

    return 0.0;
}

auto MatrixGraph::getNeighbors(size_t edgeIndex) -> std::vector<size_t> {
    std::vector<size_t> neighbors;

    if (this->nodeExists(edgeIndex)) {
        for (size_t i = 0; i < this->adjacencyMatrix.at(edgeIndex).size(); i++ ) {
            if (this->adjacencyMatrix.at(edgeIndex).at(i) != 0.0) {
                neighbors.push_back(i);
            }
        }
    }

    return neighbors;
}

auto MatrixGraph::getTypeName() -> std::string {
    return std::string("Matrix");
}

auto MatrixGraph::printToStream(std::ostream& stream) -> void {
    stream << "\t";
    for (size_t i = 0; i < this->adjacencyMatrix.size(); i++) {
        stream << this->labels.at(i) << "\t";
    }

    stream << std::endl;

    for (size_t i = 0; i < this->adjacencyMatrix.size(); i++) {
        stream << this->labels.at(i) << "\t";
        for (size_t j = 0; j < this->adjacencyMatrix.at(i).size(); j++) {
            stream << this->adjacencyMatrix.at(i).at(j) << "\t";
        }
        stream << std::endl;
    }
}

auto MatrixGraph::readFromStream(std::istream& stream) -> Graph* {
    return Graph::readFromStream<MatrixGraph>(stream);
}

auto MatrixGraph::readFromFile(std::string const& filename) -> Graph* {
    return Graph::readFromFile<MatrixGraph>(filename);
}
