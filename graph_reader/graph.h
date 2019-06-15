#ifndef __GRAPH_H__
#define __GRAPH_H__
#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "wtime.h"
#include <stdlib.h>
#include <stdint.h>
#include <sys/stat.h>
#include <utility>
inline off_t fsize(const char *filename) {
	struct stat st; 
	if (stat(filename, &st) == 0)
		return st.st_size;
	return -1; 
}

template<typename T, typename V>
using arr_view_t = std::pair<T*, V>;

template<
typename file_vert_t, typename file_index_t, typename file_weight_t,
typename new_vert_t, typename new_index_t, typename new_weight_t>
class graph
{
	public:
		new_index_t *beg_pos;
		new_vert_t *csr;
		new_weight_t *weight;
		new_index_t vert_count;
		new_index_t edge_count;

	public:
		graph(){};
		~graph(){};
		graph(const char *beg_file, 
				const char *csr_file,
				const char *weight_file);
		arr_view_t<new_vert_t, new_index_t>
		get_adjacency(new_index_t vert) {
			auto start = beg_pos[vert];
			auto end = beg_pos[vert + 1];
			arr_view_t<new_vert_t, new_index_t> res = std::make_pair(csr+start, end - start);
			return res;
		};
};
#include "graph.hpp"
#endif
