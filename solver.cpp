// Copyright 2019 Burcea Marian-Gabriel

#include "./solver.h"
#include <string>
#include <vector>
#include <utility>

// citirea datelor initiale: locatii si strazi
void solver::read_data(std::ifstream& fin) {
	int n, m;
	fin >> n >> m;

	// setez numarul de elemente din graf
	a.set_size(n);
	std::string place;

	// citesc locatiile si le pun in hashtable
	for (int i = 0; i < n; i++) {
		fin >> place;
		v.push_back(place);
		h_place.put(place, i);
	}
	std::string src, dst;

	// citesc strazile si setez muchiile in graf
	for (int i = 0; i < m; i++) {
		fin >> src >> dst;
		a.add_edge(h_place.get(src), h_place.get(dst));
	}
}

// rezolvare task1
void solver::task1_solver(std::ifstream& fin, std::ofstream& fout) {
	read_data(fin);
	int m;
	fin >> m;
	std::string src, dst;

	// citesc locatiile
	for (int i = 0; i < m; i++) {
		fin >> src >> dst;

		// afisez daca exista drum intre ele
		if (a.exist(h_place.get(src), h_place.get(dst))) {
			fout<< "y\n";
		} else {
			fout << "n\n";
		}
	}
}

// rezolvare task2
void solver::task2_solver(std::ifstream& fin, std::ofstream& fout) {
	int m;
	fin >> m;
	std::string src, dst;

	// citesc locatiile
	for (int i = 0; i < m; i++) {
		fin >> src >> dst;
		// afisez distanta dintre ele
		fout << a.road(h_place.get(src), h_place.get(dst)) << '\n';
	}
}

// query de tip c (adaugare/stergere drum)
void solver::query_c(std::ifstream& fin) {
	char s;
	std::string src, dst;
	int ind_src, ind_dst;
	fin >> src >> dst >> s;

	// iau nodurile pentru locatii din hashtable
	ind_src = h_place.get(src);
	ind_dst = h_place.get(dst);
	switch (s) {
		case '0':
			// adaug drum
			if (!a.has_edge(ind_src, ind_dst)) {
				a.add_edge(ind_src, ind_dst);
			}
			break;

		case '1':
			// sterg drumurile
			if (a.has_edge(ind_src, ind_dst)) {
				a.remove_edge(ind_src, ind_dst);
			}
			if (a.has_edge(ind_dst, ind_src)) {
				a.remove_edge(ind_dst, ind_src);
			}
			break;

		case '2':
			// drumul devine bidirectional
			if (!a.has_edge(ind_src, ind_dst)) {
				a.add_edge(ind_src, ind_dst);
			}
			if (!a.has_edge(ind_dst, ind_src)) {
				a.add_edge(ind_dst, ind_src);
			}
			break;

		case '3':
			// inversez sensul drumului
			if (a.has_edge(ind_src, ind_dst) && !a.has_edge(ind_dst, ind_src)) {
				a.remove_edge(ind_src, ind_dst);
				a.add_edge(ind_dst, ind_src);
			} else if (!a.has_edge(ind_src, ind_dst) && a.has_edge(ind_dst, ind_src)) {
				a.remove_edge(ind_dst, ind_src);
				a.add_edge(ind_src, ind_dst);
			}
			break;
	}
}

// query de tip q (afisare informatii despre drumuri)
void solver::query_q(std::ifstream& fin, std::ofstream& fout) {
	char s;
	std::string src, dst;
	fin >> src >> dst >> s;
	std::pair<int, int> p;
	switch (s) {
		case '0':
			// afisez daca exista drum de la sursa la destinatie
			if (a.exist(h_place.get(src), h_place.get(dst))) {
				fout << "y\n";
			} else {
				fout << "n\n";
			}
			break;

		case '1':
			// afisez distanta de la sursa la destinatie
			fout << a.road(h_place.get(src), h_place.get(dst)) << '\n';
			break;

		case '2':
			// afisez distanta de la sursa la destinatie cu oprire intermediara
			std::string inter;
			fin >> inter;
			// inter este locatia intermediara
			int d1 = a.road(h_place.get(src), h_place.get(inter));
			int d2 = a.road(h_place.get(inter), h_place.get(dst));
			if (d1 == -1 || d2 == -1) {
				fout << "-1\n";
			} else {
				fout << d1 + d2 << "\n";
			}
			break;
	}
}


// rezolvare task3
void solver::task3_solver(std::ifstream& fin, std::ofstream& fout) {
	int m;
	std::string query;
	fin >> m;

	// citesc query-urile
	for (int i = 0; i < m; i++) {
		fin >> query;

		// apelez functiile corespunzatoare
		if (query == "c") {
			query_c(fin);
		} else {
			query_q(fin, fout);
		}
	}

	// precalculez distantele dintre oricare 2 noduri pentru task4
	a.set_distances();
}


// query de tip d (introducere sofer pe harta)
void solver::query_d(std::ifstream& fin, int& n) {
	int driver;
	std::string name, place;
	fin >> name >> place;
	bool exist = false;

	// verific daca soferul a mai fost adaugat si inainte
	if (h_drive.has_key(name)) {
		driver = h_drive.get(name);
		exist = true;
	}

	if (!exist) {
		// daca nu, il initializez si cresc numarul de soferi
		d[n].name = name;
		d[n].place = place;
		d[n].status = true;
		// obtin nodul corespunzator strazii in care apare
		d[n].node = h_place.get(d[n].place);
		h_drive.put(name, n);
		n++;

	} else {
		// daca da, doar ii schimb statusul in on si actualizez pozitia
		d[driver].place = place;
		d[driver].node = h_place.get(d[driver].place);
		d[driver].status = true;
	}
}

// query de tip b (repaus pentru sofer)
void solver::query_b(std::ifstream& fin) {
	std::string name;
	fin >> name;

	// gasesc indicele soferului din hashtabe si il scot de pe harta
	d[h_drive.get(name)].status = false;
}

// setez noile caracteristici pentru un sofer ce tocmai a indeplinit o cursa
void solver::set_driver(int driver, float rating, int ind_src, int ind_dst) {
	d[driver].points += rating;
	d[driver].races++;

	// actualizez distanta parcursa
	d[driver].distance += a.distances[d[driver].node][ind_src];
	d[driver].distance += a.distances[ind_src][ind_dst];
	d[driver].node = ind_dst;

	// ii schimb pozitia pe harta
	d[driver].place = v[d[driver].node];
	d[driver].rating = d[driver].points / d[driver].races;
}

// query de tip r (cursa de la sursa la destinatie)
void solver::query_r(std::ifstream& fin, std::ofstream& fout, int& n) {
	std::string src, dst;
	float rating;

	// citesc datele de intrare
	fin >> src >> dst >> rating;
	// obitn nodurile pentru sursa si destinatie
	int ind_src	= h_place.get(src), ind_dst = h_place.get(dst);
	int driver = -1, min_road = INT_MAX;

	// caut cel mai apropiat sofer de client
	for (int j = 0; j < n; j++) {
		if (d[j].status == 1 && a.distances[d[j].node][ind_src] != -1) {
			if (a.distances[d[j].node][ind_src] < min_road) {
				min_road = a.distances[d[j].node][ind_src];
				driver = j;

			} else if (a.distances[d[j].node][ind_src] == min_road) {
				if (d[j].rating > d[driver].rating) {
					driver = j;

				} else if (d[j].rating == d[driver].rating) {
					if (d[j].name < d[driver].name) {
						driver = j;
					}
				}
			}
		}
	}

	// cazul cand nu s-au gasit soferi
	if (driver == -1) {
		fout << "Soferi indisponibili\n";

	} else {
		// daca se poate ajunge la destinatie actualizez pozitia soferului
		if (a.distances[ind_src][ind_dst] != -1) {
			set_driver(driver, rating, ind_src, ind_dst);
		} else {
			// daca nu, afisez mesaj
			if (a.neigh[ind_dst].size() == 0) {
				fout << "Destinatie inaccesibila\n";
			} else {
				bool exist = false;

				// caut cea mai apropiata locatie de destinatie
				for (int j = a.neigh[ind_dst].size() - 1; j >= 0; j--) {
					if (a.distances[ind_src][a.neigh[ind_dst][j]] != -1) {
						ind_dst = a.neigh[ind_dst][j];
						set_driver(driver, rating, ind_src, ind_dst);
						exist = true;
						break;
					}
				}

				if (exist == false) {
					fout << "Destinatie inaccesibila\n";
				}
			}
		}
	}
}

// query de tip top_rating (topul soferilor in functie de rating)
void solver::query_top_rating(std::ifstream& fin, std::ofstream& fout, int& n) {
	int counter;
	fin >> counter;
	std::vector<bool> vis(n, false);

	for (int j = 0; j < counter && j < n; j++) {
		int ind_maxi = -1;
		float maxi = -1;

		// aflu ratingul maxim
		for (int k = 0; k < n; k++) {
			if (vis[k] == false) {
				if (d[k].rating > maxi) {
					maxi = d[k].rating;
					ind_maxi = k;

				} else if (d[k].rating == maxi) {
					if (d[k].name < d[ind_maxi].name) {
						ind_maxi = k;
					}
				}
			}
		}

		// "scot" soferul cu rating maxim marcandu-l
		vis[ind_maxi] = true;
		fout << d[ind_maxi].name << ':';
		fout << std::fixed << std::setprecision(3) << d[ind_maxi].rating << ' ';
	}

	fout << '\n';
}

// query de tip top_dist (topul soferilor in functie de distanta parcursa)
void solver::query_top_dist(std::ifstream& fin, std::ofstream& fout, int& n) {
	int counter;
	fin >> counter;
	std::vector<bool> vis(n, false);

	for (int j = 0; j < counter && j < n; j++) {
		int ind_maxi = -1, maxi = -1;

		// aflu distanta maxima
		for (int k = 0; k < n; k++) {
			if (vis[k] == false) {
				if (d[k].distance > maxi) {
					maxi = d[k].distance;
					ind_maxi = k;

				} else if (d[k].distance == maxi) {
					if (d[k].name < d[ind_maxi].name) {
						ind_maxi = k;
					}
				}
			}
		}

		// "scot" soferul cu distanta maxima marcandu-l
		vis[ind_maxi] = true;
		fout << d[ind_maxi].name << ':' << d[ind_maxi].distance << ' ';
	}

	fout << '\n';
}

// query de tip top_rides (topul soferilor in functie de numarul de curse)
void solver::query_top_rides(std::ifstream& fin, std::ofstream& fout, int& n) {
	int counter;
	fin >> counter;
	std::vector<bool> vis(n, false);

	for (int j = 0; j < counter && j < n; j++) {
		int ind_maxi = -1, maxi = -1;

		// aflu numarul minim de curse
		for (int k = 0; k < n; k++) {
			if (vis[k] == false) {
				if (d[k].races > maxi) {
					maxi = d[k].races;
					ind_maxi = k;

				} else if (d[k].races == maxi) {
					if (d[k].name < d[ind_maxi].name) {
						ind_maxi = k;
					}
				}
			}
		}

		// "scot" soferul cu numarul minim de curse marcandu-l
		vis[ind_maxi] = true;
		fout << d[ind_maxi].name << ':' << d[ind_maxi].races << ' ';
	}

	fout << '\n';
}

// query de tip info (informatii despre un anumit sofer)
void solver::query_info(std::ifstream& fin, std::ofstream& fout) {
	std::string name;
	fin >> name;
	fout << name << ": ";

	// obtin indicele soferului din hashtable
	int driver = h_drive.get(name);
	// afisez informatiile
	fout << d[driver].place << ' ';
	fout << std::fixed << std::setprecision(3) << d[driver].rating << ' ';
	fout << d[driver].races << ' ' << d[driver].distance << ' ';

	if (d[driver].status) {
		fout << "online\n";
	} else {
		fout << "offline\n";
	}
}

// rezolvare task4
void solver::task4_solver(std::ifstream& fin, std::ofstream& fout) {
	int m;
	fin >> m;
	std::string query;

	// citesc datele de intrare
	for (int i = 0; i < m; i++) {
		fin >> query;
		// raspund la query-uri

		if (query == "d") {
			query_d(fin, n);
			continue;
		}

		if (query == "b") {
			query_b(fin);
			continue;
		}

		if (query == "r") {
			query_r(fin, fout, n);
			continue;
		}

		if (query == "top_rating") {
			query_top_rating(fin, fout, n);
			continue;
		}

		if (query == "top_dist") {
			query_top_dist(fin, fout, n);
			continue;
		}

		if (query == "top_rides") {
			query_top_rides(fin, fout, n);
			continue;
		}

		if (query == "info") {
			query_info(fin, fout);
			continue;
		}
	}
}

// rezolvare task5
void solver::task5_solver(std::ifstream& fin, std::ofstream& fout) {
	int fuel, driver, m;
	std::string name, place;

	// citesc datele de intrare
	fin >> fuel >> name;
	driver = d[h_drive.get(name)].node;
	fin >> m;
	std::vector<int> places(m, 0);
	int k = -1;

	// citesc locatiile si le pun in vectorul pentru sortat
	for (int i = 0; i < m; i++) {
		fin >> place;
		places[++k] = h_place.get(place);
	}

	// sortez vectorul
	for (int i = 0; i < m - 1; i++) {
		for (int j = i + 1; j < m; j++) {
			if (a.distances[driver][places[i]] > a.distances[driver][places[j]]) {
				int aux = places[i];
				places[i] = places[j];
				places[j] = aux;

			} else if (a.distances[driver][places[i]] ==
				a.distances[driver][places[j]] && v[places[i]] > v[places[j]]) {
				int aux = places[i];
				places[i] = places[j];
				places[j] = aux;
			}
		}
	}

	// afisez locatiile la care se poate ajunge
	k = -1;
	while (1) {
		if (a.distances[driver][places[++k]] != -1) {
			break;
		}
	}

	while (k < m) {
		if (a.distances[driver][places[k]] > fuel) {
			break;
		}
		fout << v[places[k]] << ' ';
		while (k < m - 1 && places[k] == places[k + 1]) {
			k++;
		}
		k++;
	}

	// eliberez memoria pentru vectorul de soferi
	delete[] d;
}
