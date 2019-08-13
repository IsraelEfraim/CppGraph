#ifndef LISTGRAPH_HPP
#define LISTGRAPH_HPP

#include "Graph.hpp"

class ListGraph : public Graph
{
    public:
        ListGraph(bool oriented, bool weighted);

        std::string getType();
};

#endif // LISTGRAPH_HPP
