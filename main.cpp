#include <iostream>

#include "graph/Graph.hpp"
#include "graph/MatrixGraph.hpp"
#include "graph/ListGraph.hpp"

auto printGraphInformation(Graph* g) -> void {
    std::cout << "Type:     " << g->getTypeName() << std::endl
              << "Oriented: " << g->isOriented()  << std::endl
              << "Weighted: " << g->isWeighted()  << std::endl;
}

auto matrixExample() -> void {
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

auto listExample () -> void {
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

auto depthFirstSearch() -> void {
    Graph* g = new ListGraph(false, false);

    g->addNode("A");
    g->addNode("B");
    g->addNode("C");
    g->addNode("D");
    g->addNode("E");
    g->addNode("F");

    g->addEdge("A-B");
    g->addEdge("A-C");
    g->addEdge("A-D");
    g->addEdge("B-D");
    g->addEdge("C-E");
    g->addEdge("C-F");
    g->addEdge("E-F");

    auto sequence = g->depthFirstSearch(0);
    for (size_t i = 0; i < sequence.size(); i++) {
        std::cout << g->getNodeName(sequence.at(i)) << ", ";
    }

    std::cout << std::endl;
}

auto breadthFirstSearch() -> void {
    Graph* g = new ListGraph(false, false);

    g->addNode("A");
    g->addNode("B");
    g->addNode("C");
    g->addNode("D");
    g->addNode("E");
    g->addNode("F");

    g->addEdge("A-B");
    g->addEdge("A-C");
    g->addEdge("A-D");
    g->addEdge("B-D");
    g->addEdge("C-E");
    g->addEdge("C-F");
    g->addEdge("E-F");

    auto sequence = g->breadthFirstSearch(0);
    for (size_t i = 0; i < sequence.size(); i++) {
        std::cout << g->getNodeName(sequence.at(i)) << ", ";
    }

    std::cout << std::endl;
}

auto dijkstra() -> void {
    Graph* g = new ListGraph(false, true);

    g->addNode("A");
    g->addNode("B");
    g->addNode("C");
    g->addNode("D");
    g->addNode("E");

    g->addEdge("A-B", 3);
    g->addEdge("A-C", 5);
    g->addEdge("A-D", 6);
    g->addEdge("A-E", 8);
    g->addEdge("B-D", 2);
    g->addEdge("B-E", 11);
    g->addEdge("C-E", 2);

    g->printToStream(std::cout);

    auto dijkstraMap = g->dijkstra(0);
    for (size_t i = 0; i < dijkstraMap.size(); i++) {
        std::cout << "["  << g->getNodeName(i)
                  << ", " << dijkstraMap.at(i).first
                  << ", " << g->getNodeName(dijkstraMap.at(i).second)
                  << "] " << std::endl;
    }
}

auto read() -> void {
    Graph* g = ListGraph::readFromFile("../sample/trabalho-234cores.txt");
}

auto main() -> int {
    //listExample();
    //matrixExample();
    //depthFirstSearch();
    //breadthFirstSearch();
    //dijkstra();
    //read();
    return 0;
}
