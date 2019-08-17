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

void matrixExample()
{
    Graph* g = new MatrixGraph(false, true);
    printGraphInformation(g);

    g->addNode("1");
    g->addNode("2");
    g->addNode("3");
    g->addNode("4");
    g->addNode("5");
    g->addNode("6");

    g->addEdge(0, 1, 1); // 1-2
    g->addEdge(0, 4, 2); // 1-5
    g->addEdge(1, 2, 3); // 2-3
    g->addEdge(1, 4, 4); // 2-5
    g->addEdge(2, 3, 6); // 3-4
    g->addEdge(3, 4, 6); // 4-5
    g->addEdge(3, 5, 6); // 4-6

    g->printToStream(std::cout);

    delete g;
}

void listExample ()
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
}

int main()
{
    //listExample();
    //matrixExample();

    return 0;
}
