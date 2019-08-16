#include <iostream>

#include "graph/Graph.hpp"
#include "graph/MatrixGraph.hpp"
#include "graph/ListGraph.hpp"

void printGraphInformation(Graph* g)
{
    std::cout << "Type:     " << g->getTypeName() << std::endl
              << "Oriented: " << g->isOriented()  << std::endl
              << "Weighted: " << g->isWeighted()  << std::endl;
}

int main()
{
    Graph* g = new ListGraph(false, true);
    printGraphInformation(g);

    g->addNode("A");
    g->addNode("B");
    g->addNode("C");
    g->addNode("D");
    g->addNode("E");
    g->addNode("F");

    g->addEdge(0, 1, 5); // A-B
    g->addEdge(0, 4, 8); // A-E
    g->addEdge(1, 2, 3); // B-C
    g->addEdge(1, 4, 9); // B-E
    g->addEdge(2, 3, 2); // C-D
    g->addEdge(3, 4, 4); // D-E
    g->addEdge(3, 5, 2); // D-F

    g->printToStream(std::cout);

    delete g;

    return 0;
}
