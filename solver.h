// Copyright 2019 Burcea Marian-Gabriel

#ifndef SOLVER_H_
#define SOLVER_H_

#include <fstream>
#include <utility>
#include <string>
#include <vector>
#include <climits>
#include <iomanip>
#include "./graph.h"
#include "./driver.h"
#include "./hashtable.h"
#define DMAX 200

class solver {
 public:
	// graful pentru locatii
	Graph<int> a;
	// vectorul de locatii
	std::vector<std::string> v;
	// vectorul de soferi
	Driver<int> *d = new Driver<int>[DMAX];
	// numarul de soferi
	int n;

	// hashtable pentru stocarea locatiilor
	Hashtable<std::string, int> h_place = Hashtable<std::string, int>(VMAX);
	// hashtable pentru stocarea soferilor
	Hashtable<std::string, int> h_drive = Hashtable<std::string, int>(VMAX);

	void read_data(std::ifstream&);

	void task1_solver(std::ifstream&, std::ofstream&);

	void task2_solver(std::ifstream&, std::ofstream&);

	void query_c(std::ifstream&);

	void query_q(std::ifstream&, std::ofstream&);

	void task3_solver(std::ifstream&, std::ofstream&);

	void query_d(std::ifstream&, int&);

	void query_b(std::ifstream&);

	void set_driver(int, float, int, int);

	void query_r(std::ifstream&, std::ofstream&, int&);

	void query_top_rating(std::ifstream&, std::ofstream&, int&);

	void query_top_dist(std::ifstream&, std::ofstream&, int&);

	void query_top_rides(std::ifstream&, std::ofstream&, int&);

	void query_info(std::ifstream&, std::ofstream&);

	void task4_solver(std::ifstream&, std::ofstream&);

	void task5_solver(std::ifstream&, std::ofstream&);
};
#endif  // SOLVER_H_
