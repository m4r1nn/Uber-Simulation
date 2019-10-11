// Copyright 2019 Burcea Marian-Gabriel

#ifndef DRIVER_H_
#define DRIVER_H_

#include <iostream>
#include <string>

template <class T>
class Driver {
 public:
	std::string name;
	std::string place;

	bool status;
	float points;
	float rating;
	int distance;
	int races;
	T node;

	// constructor pentru clasa Driver
	Driver<T>(): status(false), points(0), rating(0),
		distance(0), races(0), node(-1){}
	// destructor pentru clasa Driver
	~Driver<T>() {}
};

#endif  // DRIVER_H_
