#include <iostream>
#include "graph.h"
#include <memory>
#include <vector>
#include <queue>
#include "wtime.h"
using graph_t = graph<long, long, int, long, long, char>;

// single thread BFS
template <typename T>
typename T::vert_t BFS(std::shared_ptr<T> g, typename T::vert_t start,
                       typename T::vert_t end) {
    if (start == end) return true;
    typename T::vert_t count = 1;
    std::vector<bool> all(g->vert_count, true);  // true: unvisited
    std::queue<typename T::vert_t> grey_current;
    decltype(grey_current) grey_next;
    grey_current.push(start);
    all[start] = false;
    while (grey_current.size() != 0 || grey_next.size() != 0) {
        while (grey_current.size() != 0) {
            auto vert = grey_current.front();
            grey_current.pop();
            auto neigh = g->get_adjacency(vert);
            for (auto i = 0; i < neigh.second; i++) {
                auto v = neigh.first[i];
                if (all[v]) {
                    if (neigh.first[i] == end) {
                        return count;
                    } else {
                        grey_next.push(v);
                        all[v] = false;
                    }
                }
            }
        }
        std::swap(grey_next, grey_current);
        count++;
    }
    return false;
}

long mtBFS(std::shared_ptr<graph_t> g, long start, long end) {
    if (start == end) return 0;
    bool flag = false;
    graph_t::vert_t count = 1;
    std::vector<bool> all(g->vert_count, true);  // true: unvisited
    std::queue<graph_t::vert_t> grey_current;
    decltype(grey_current) grey_next;
    grey_current.push(start);
    all[start] = false;
    while (grey_current.size() != 0 || grey_next.size() != 0) {
        while (grey_current.size() != 0) {
            auto vert = grey_current.front();
            grey_current.pop();
            all[vert] = false;
            auto neigh = g->get_adjacency(vert);
            graph_t::vert_t *adj = neigh.first;
            graph_t::vert_t num = neigh.second;
            //printf("%ld:\n", vert);
#pragma omp parallel for firstprivate(end)
            for (graph_t::vert_t i = 0; i < num; i++) {
                auto v = adj[i];
                if (all[v]) {
                    if (v == end) {
                        flag = true;
                    } else {
                        all[v] = false;
                    }
                }
            }
            if (flag) return count;
            for (graph_t::vert_t i = 0; i < num; i++)
                grey_next.push(adj[i]);
        }
        std::swap(grey_next, grey_current);
        count++;
    }
    return -1;
}

int main(int args, char **argv) {
    std::cout << "Input: ./exe beg csr weight\n";
    if (args != 4) {
        std::cout << "Wrong input\n";
        return -1;
    }

    const char *beg_file = argv[1];
    const char *csr_file = argv[2];
    const char *weight_file = argv[3];

    // template <file_vertex_t, file_index_t, file_weight_t
    // new_vertex_t, new_index_t, new_weight_t
    long start = 970809;
    long end = 1789999;
    auto g = std::make_shared<graph_t>(beg_file, csr_file, weight_file);
    std::cout << "single thread:" << std::endl;
    std::cout << start << " -> " << end << ":\n";
    auto t = wtime();
    std::cout << BFS(g, start, end) << std::endl;
    std::cout << "Time: " << wtime() - t << std::endl;
    std::cout << "multi thread:" << std::endl;
    t = wtime();
    std::cout << mtBFS(g, start, end) << std::endl;
    std::cout << "Time: " << wtime() - t << std::endl;
    return 0;
}
