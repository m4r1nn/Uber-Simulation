// Copyright 2019 Burcea Marian-Gabriel

#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <string>
#define VMAX 1000

template<class T>
class Node {
 public:
    T info;
    Node<T> *next, *prev;
};

template <class T>
class LinkedList {
 public:
    Node<T> *pfirst, *plast;

    LinkedList<T>(): pfirst(NULL), plast(NULL) {}

    Node<T>* front();

    void addLast(T);

    void removeFirst();

    int isEmpty();
};

template<class Tkey, class Tvalue>
class Elem {
 public:
	// cheie
	Tkey key;
	// valoare
	Tvalue value;
};

template<class Tkey, class Tvalue>
class Hashtable {
 private:
	// hashtable = vector de liste (bucket-uri)
	LinkedList<Elem<Tkey, Tvalue> > *H;
	// dimensiunea hashtable-ului
	int HMAX;

 public:
	int hash(std::string);

	explicit Hashtable<Tkey, Tvalue>(int hmax);

	~Hashtable<Tkey, Tvalue>();

	void put(Tkey, Tvalue);

	Tvalue get(Tkey);

	int has_key(Tkey);
};

#endif  // HASHTABLE_H_
