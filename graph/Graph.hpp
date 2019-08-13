#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <string>

class Graph
{
    protected:
        bool oriented;
        bool weighted;

    public:
        Graph(bool oriented, bool weighted);

        bool isOriented();
        bool isWeighted();

        virtual std::string getType() = 0;

        virtual ~Graph() = 0;
};

#endif // GRAPH_HPP
