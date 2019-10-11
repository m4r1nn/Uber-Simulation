// Copyright 2019 Burcea Marian-Gabriel

#ifndef GRAPH_H_
#define GRAPH_H_

#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#define MMAX 500

template <class T>
class Graph {
 public:
	// dimensiunea (numarul de noduri)
	int size;
	// lista de adiacenta
	std::vector<std::vector<T>> neigh;
	// matricea de distante
	int distances[MMAX][MMAX];

	// connstructor si destructor pentru graf
	Graph<T>() {}
	~Graph<T>() {}

	void add_edge(T, T);

	void remove_edge(T, T);

	bool has_edge(T, T);

	void set_size(int);

	bool exist(T, T);

	int road(T, T);

	void set_distances();
};

#endif  // GRAPH_H_
