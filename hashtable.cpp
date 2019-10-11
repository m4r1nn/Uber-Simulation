// Copyright 2019 Burcea Marian-Gabriel

#include "./hashtable.h"
#include <string>
#include <iostream>
#include <cstdlib>

template <class T>
// pointer la primul nod din lista
Node<T>* LinkedList<T>::front() {
    return pfirst;
}

template <class T>
// adauga element la sfarsitul listei
void LinkedList<T>::addLast(T x) {
	// creare nod nou
    Node<T> *paux = new struct Node<T>;
    paux->info = x;
    paux->prev = plast;
    paux->next = NULL;

    // legatura la lista
    if (plast != NULL) {
        plast->next = paux;
    }
    plast = paux;
    if (pfirst == NULL) {
        pfirst = plast;
    }
}

template <class T>
// sterge primul element din lista
void LinkedList<T>::removeFirst() {
    Node<T>* paux;
    if (pfirst != NULL) {
    	// stergere legatura
        paux = pfirst->next;
        if (pfirst == plast) {
            plast = NULL;
        }

        // stergere nod
    	delete pfirst;
    	pfirst = paux;
    	if (pfirst != NULL) {
        	pfirst->prev = NULL;
    	}
    }
}

template <class T>
// spune daca lista este vida
int LinkedList<T>::isEmpty() {
    return (pfirst == NULL);
}

template <class Tkey, class Tvalue>
// functia de hash
int Hashtable<Tkey, Tvalue>::hash(std::string key) {
	int hkey = 0;
	for (unsigned int i = 0; i < key.length(); i++) {
	hkey = (hkey * 31 + key[i]) % VMAX;
	}
	// returneaza un intreg
	return hkey;
}

template <class Tkey, class Tvalue>
// constructor pentru hashtable
Hashtable<Tkey, Tvalue>::Hashtable(int hmax) {
	HMAX = hmax;
	H = new LinkedList<Elem<Tkey, Tvalue> > [HMAX];
}

template <class Tkey, class Tvalue>
// destructor pentru hashtable
Hashtable<Tkey, Tvalue>::~Hashtable() {
	// sterg element cu element de pe fiecare nivel
	for (int i = 0; i < HMAX; i++) {
		while (!H[i].isEmpty()) {
			H[i].removeFirst();
		}
	}
	delete[] H;
}

template <class Tkey, class Tvalue>
// adaugare in hashtable
void Hashtable<Tkey, Tvalue>::put(Tkey key, Tvalue value) {
	Node<Elem<Tkey, Tvalue> > *p;
	Elem<Tkey, Tvalue> info;

	// gasesc nivelul pe care trebuie adaugat
	int hkey = hash(key);
	p = H[hkey].front();
	while (p != NULL) {
		if (p->info.key == key) {
			break;
		}
		p = p->next;
	}

	// daca exista deja cheia, actuazlizez valoarea
	if (p != NULL) {
		p->info.value = value;
		// daca nu, adaug noul element
	} else {
		info.key = key;
		info.value = value;
		H[hkey].addLast(info);
	}
}

template <class Tkey, class Tvalue>
// returneaza valoarea pentru o anumita cheie
Tvalue Hashtable<Tkey, Tvalue>::get(Tkey key) {
	Node<Elem<Tkey, Tvalue> > *p;
	int hkey = hash(key);

	// ma pozitionez pe nivelul cu cheia
	p = H[hkey].front();
	while (p != NULL) {
		if (p->info.key == key) {
			break;
		}
		p = p->next;
	}

	// daca am gasit elementul, returnez valoarea
	if (p != NULL) {
		return p->info.value;
	} else {
		Tvalue x{};
		return x;
	}
}

template <class Tkey, class Tvalue>
// verific daca exista un element cu o anumita cheie
int Hashtable<Tkey, Tvalue>::has_key(Tkey key) {
	Node<Elem<Tkey, Tvalue> > *p;
	int hkey = hash(key);

	// ma pozitionez pe nivelul cu cheia
	p = H[hkey].front();
	while (p != NULL) {
		if (p->info.key == key) {
			break;
		}
		p = p->next;
	}

	// returnez 1 sau 0
	if (p != NULL) {
		return true;
	} else {
		return false;
	}
}

template class LinkedList<std::string>;
template class LinkedList<int64_t>;
template class LinkedList<int32_t>;
template class LinkedList<int16_t>;
template class LinkedList<int8_t>;

template class Hashtable<std::string, int64_t>;
template class Hashtable<std::string, int32_t>;
template class Hashtable<std::string, int16_t>;
template class Hashtable<std::string, int8_t>;
