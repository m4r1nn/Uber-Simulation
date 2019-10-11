// Copyright 2019 Burcea Marian-Gabriel

#include "./graph.h"
#include <queue>
#include <vector>

template <class T>
// adauga muchie in graf
void Graph<T>::add_edge(T src, T dst) {
	neigh[src].push_back(dst);
}

template <class T>
// sterge muchie
void Graph<T>::remove_edge(T src, T dst) {
	for (unsigned int i = 0; i < neigh[src].size(); i++) {
		if (neigh[src][i] == dst) {
			neigh[src].erase(neigh[src].begin() + i);
			return;
		}
	}
}

template <class T>
// verifica daca intre 2 noduri exista muchie
bool Graph<T>::has_edge(T src, T dst) {
	for (unsigned int i = 0; i < neigh[src].size(); i++) {
		if (neigh[src][i] == dst) {
			return true;
		}
	}
	return false;
}

template <class T>
// setter pentru dimensiunea grafului
void Graph<T>::set_size(int size) {
	this->size = size;

	// initializez lista de adiacenta
	for (int i = 0; i < size; i++) {
		std::vector<T> v;
		neigh.push_back(v);
	}
}

template <class T>
// verifica daca exista drum de la un nod la altul
bool Graph<T>::exist(T src, T dst) {
	std::vector<bool> vis(size, false);

	// fac BFS
	std::queue<int> q;
	q.push(src);
	// vizitez nodul sursa
	vis[src] = true;
	while (!q.empty()) {
		int current = q.front();
		q.pop();

		// vizitez vecinii nodului curent si ii pun in coada
		for (unsigned int i = 0; i < neigh[current].size(); i++) {
			if (vis[neigh[current][i]] == false) {
				q.push(neigh[current][i]);
				vis[neigh[current][i]] = true;
			}
		}
	}

	// returnez daca am gasit drum
	return vis[dst] == true;
}

template <class T>
// calculeaza distanta dintre 2 noduri
int Graph<T>::road(T src, T dst) {
	std::vector<bool> vis(size, false);
	std::vector<int> dist(size, 0);

	// fac BFS
	std::queue<int> q;
	q.push(src);
	// vizitez nodul sursa
	vis[src] = true;
	dist[src] = 1;
	while (!q.empty()) {
		int current = q.front();
		q.pop();

		// vizitez vecinii nodului curent si ii pun in coada
		for (unsigned int i = 0; i < neigh[current].size(); i++) {
			if (vis[neigh[current][i]] == false) {
				q.push(neigh[current][i]);
				vis[neigh[current][i]] = true;
				dist[neigh[current][i]] = dist[current] + 1;
			}
		}
	}

	// returnez distanta
	return dist[dst] - 1;
}

template <class T>
// calculez distantele dintre oricare 2 noduri din graf
void Graph<T>::set_distances() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			// initializez distantele cu -1 (nu exista drum)
			distances[i][j] = -1;
		}
	}

	// fac BFS pentru fiecare nod
	for (int i = 0; i < size; i++) {
		std::vector<bool> vis(size, false);
		std::vector<int> dist(size, 0);
		std::queue<int> q;

		q.push(i);
		vis[i] = true;
		// vizitez nodul sursa
		distances[i][i] = 0;
		while (!q.empty()) {
			int current = q.front();
			q.pop();

			// vizitez vecinii nodului curent si ii pun in coada
			for (unsigned int k = 0; k < neigh[current].size(); k++) {
			if (vis[neigh[current][k]] == false) {
					q.push(neigh[current][k]);
					vis[neigh[current][k]] = true;
					distances[i][neigh[current][k]] = distances[i][current] + 1;
				}
			}
		}
	}
}

template class Graph<int64_t>;
template class Graph<int32_t>;
template class Graph<int16_t>;
template class Graph<int8_t>;
