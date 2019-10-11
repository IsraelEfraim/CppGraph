#ifndef GRAPHTESTER_HPP
#define GRAPHTESTER_HPP

#include "Graph.hpp"
#include "ListGraph.hpp"
#include "MatrixGraph.hpp"
#include <chrono>
#include <functional>

namespace Tester {
    template <typename GraphType>
    auto createGraph(bool oriented, bool weighted) -> Graph* {
        return new GraphType(oriented, weighted);
    }

    using Sample = std::pair<double, size_t>;

    template <typename Fn, typename Arg>
    auto execute(Fn algorithm, std::vector<Arg> arg) -> std::pair<std::chrono::duration<double>, std::vector<Arg>> {
        auto begin = std::chrono::high_resolution_clock::now();
        std::vector<Arg> solution = algorithm(arg);
        auto elapsed = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - begin);

        return std::make_pair(elapsed, solution);
    }

    namespace Coloring {

        template <typename ColorType>
        auto countUniqueColors(std::vector<ColorType>& colors) -> size_t {
            std::sort(std::begin(colors), std::end(colors));
            auto leftover = std::unique(std::begin(colors), std::end(colors));
            colors.erase(leftover, std::end(colors));

            return colors.size();
        }

        template <typename Fn>
        auto coloringAlgorithms(Fn reader, std::string filename) -> std::pair<Sample, Sample> {
            Graph* g = reader(filename);

            std::vector<int> colors(g->getNodeCount());
            std::iota(std::begin(colors), std::end(colors), 0);

            auto wp = execute([&g](std::vector<int> const& arg) -> std::vector<int> {
                return g->welshPowell(arg);
            }, colors);

            auto wpTotal = countUniqueColors(wp.second);

            auto ds = execute([&g](std::vector<int> const& arg) -> std::vector<int> {
                return g->dsatur(arg);
            }, colors);

            auto dsTotal = countUniqueColors(ds.second);

            delete g;

            return {
                { wp.first.count(), wpTotal }, { ds.first.count(), dsTotal }
            };
        }

        auto multipleColoringTest(std::string filename, std::ostream& os) -> std::vector<std::pair<Sample, Sample>> {
            auto list = coloringAlgorithms(ListGraph::readFromFile, filename);
            auto matrix = coloringAlgorithms(MatrixGraph::readFromFile, filename);

            os << list.first.first << " " << list.first.second << std::endl
               << list.second.first << " " << list.second.second << std::endl
               << matrix.first.first << " " << matrix.first.second << std::endl
               << matrix.second.first << " " << matrix.second.second << std::endl << std::endl;

            return { list, matrix };
        }

        auto runEfficiencyTest(std::string filename) -> void {
            std::ofstream file(filename);

            /* Ideally 28 color graph */
            auto _28 = multipleColoringTest("../../sample/trabalho-28cores.txt", file);

            /* Ideally 65 color graph (sparser) */
            auto _65a = multipleColoringTest("../../sample/trabalho-65cores1.txt", file);

            /* Ideally 65 color graph (less sparse) */
            auto _65b = multipleColoringTest("../../sample/trabalho-65cores2.txt", file);

            /* Ideally 234 color graph */
            auto _234 = multipleColoringTest("../../sample/trabalho-234cores.txt", file);
        }

    } // namespace Coloring
}

#endif // GRAPHTESTER_HPP
