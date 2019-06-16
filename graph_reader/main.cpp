#include <iostream>
#include "graph.h"
#include <memory>
#include <vector>
#include <queue>
#include "wtime.h"

// single thread BFS
template <typename T>
bool BFS(std::shared_ptr<T> g, typename T::vert_t start,
         typename T::vert_t end) {
    if (start == end) return true;
    typename T::vert_t count = 0;
    std::vector<bool> all(g->vert_count, true);  // true: unvisited
    std::queue<typename T::vert_t> grey;
    grey.push(start);
    all[start] = false;
    while (grey.size() != 0) {
        auto vert = grey.front();
        grey.pop();
        auto neigh = g->get_adjacency(vert);
        count++;
        for (auto i = 0; i < neigh.second; i++) {
            auto v = neigh.first[i];
            if (all[v]) {
                if (neigh.first[i] == end) {
                    return true;
                } else {
                    grey.push(v);
                    all[v] = false;
                }
            }
        }
    }
    return false;
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
    // new_vertex_t, new_index_t, new_weight_t>
    using graph_t = graph<long, long, int, long, long, char>;
    long start = 6;
    long end = 3;
    auto g = std::make_shared<graph_t>(beg_file, csr_file, weight_file);
    // auto t = wtime();
    // auto res = BFS(g, start, end);
    // std::cout << res << std::endl << "Time: " << wtime() - t << std::endl;
    std::cout << "6 -> 9: " << std::boolalpha << BFS(g, 6, 9) << std::endl;
    return 0;
}
