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
    Graph* g = new MatrixGraph(true, false);
    printGraphInformation(g);
    delete g;

    g = new ListGraph(false, true);
    printGraphInformation(g);
    delete g;

    return 0;
}
