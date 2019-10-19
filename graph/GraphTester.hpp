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

    template <typename Return, typename Fn>
    auto execute(Fn algorithm) -> std::pair<std::chrono::duration<double>, Return> {
        auto begin = std::chrono::high_resolution_clock::now();
        Return solution = algorithm();
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
            auto _28 = multipleColoringTest("../../sample/GrafosColoracao/trabalho-28cores.txt", file);

            /* Ideally 65 color graph (sparser) */
            auto _65a = multipleColoringTest("../../sample/GrafosColoracao/trabalho-65cores1.txt", file);

            /* Ideally 65 color graph (less sparse) */
            auto _65b = multipleColoringTest("../../sample/GrafosColoracao/trabalho-65cores2.txt", file);

            /* Ideally 234 color graph */
            auto _234 = multipleColoringTest("../../sample/GrafosColoracao/trabalho-234cores.txt", file);
        }

    } // namespace Coloring

    namespace Mst {
        auto sumEdgesWeight(std::vector<Edge> const& edges) -> double {
            return std::accumulate(std::begin(edges), std::end(edges), 0.0,
                                   [](double sum, Edge const& current) -> double {
                                       return sum + current.weight;
                                   });
        }

        template <typename Fn>
        auto mstAlgorithms(Fn reader, std::string filename) -> std::pair<Sample, Sample> {
            Graph* g = reader(filename);

            auto prim = execute<std::vector<Edge>>([&]() -> std::vector<Edge> {
                return g->prim(0);
            });

            auto kruskal = execute<std::vector<Edge>>([&]() -> std::vector<Edge> {
                return g->kruskal();
            });

            auto primSum = static_cast<size_t>(sumEdgesWeight(prim.second));
            auto kruskalSum = static_cast<size_t>(sumEdgesWeight(kruskal.second));

            delete g;

            return {
                { prim.first.count(), primSum }, { kruskal.first.count(), kruskalSum }
            };
        }

        auto multipleMstTest(std::string filename, std::ostream& os) -> std::vector<std::pair<Sample, Sample>> {
            auto list = mstAlgorithms(ListGraph::readFromFile, filename);
            auto matrix = mstAlgorithms(MatrixGraph::readFromFile, filename);

            os << filename << std::endl;

            os << list.first.first << " " << list.first.second << std::endl
               << list.second.first << " " << list.second.second << std::endl
               << matrix.first.first << " " << matrix.first.second << std::endl
               << matrix.second.first << " " << matrix.second.second << std::endl << std::endl;

            return { list, matrix };
        }

        auto runEfficiencyTest(std::string filename) -> void {
            std::ofstream file(filename);

            auto _v50e25 = multipleMstTest("../sample/GrafosMST/50vertices25%Arestas.txt", file);
            auto _v50e50 = multipleMstTest("../sample/GrafosMST/50vertices50%Arestas.txt", file);
            auto _v50e100 = multipleMstTest("../sample/GrafosMST/50vertices100%Arestas.txt", file);

            auto _v500e25 = multipleMstTest("../sample/GrafosMST/500vertices25%Arestas.txt", file);
            auto _v500e50 = multipleMstTest("../sample/GrafosMST/500vertices50%Arestas.txt", file);
            auto _v500e100 = multipleMstTest("../sample/GrafosMST/500vertices25%Arestas.txt", file);

            auto _v1000e25 = multipleMstTest("../sample/GrafosMST/1000vertices25%Arestas.txt", file);
        }
    }
}

#endif // GRAPHTESTER_HPP
