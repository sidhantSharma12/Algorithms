
#ifndef LINEAR_HASH_TABLE_H
#define LINEAR_HASH_TABLE_H

#include <iostream>

using namespace std;
#include <math.h>

enum state { EMPTY, OCCUPIED, DELETED };

template<typename T>
class LinearHashTable {
private:
	int count; //number of elements
	int power; // 2^power=arraySize
	int array_size;
	int initialCapacity;
	T *array;
	state *array_state;


public:
	LinearHashTable(int = 5);
	~LinearHashTable();
	int size() const;
	int capacity() const;
	double load_factor() const;
	bool empty() const;
	bool member(T const &) const;
	T bin(int) const;


	void insert(T const &);
	bool remove(T const &);
	int  findIndexToInsert(T const &, state *);
	int  findIndexOfObject(T const &);
	void clear();
	void doubleArray();
	void halfArray();
	void print() const;
};

template<typename T >
LinearHashTable<T >::LinearHashTable(int m) :
	array_size(1 << power) {
	count = 0;
	power = m;
	array_size = pow(2, power);//create 2^m sized array
	initialCapacity = array_size; //value of array size should not go below initialCapacity

	array = new T[array_size];
	array_state = new state[array_size];

	for (int i = 0; i<array_size; i++) {
		array_state[i] = EMPTY; //initialize it to empty
		array[i] = NULL;
	}


}

template<typename T >
LinearHashTable<T >::~LinearHashTable() {
	delete[] array;
	delete[] array_state;
}

template<typename T >
int LinearHashTable<T >::size() const {
	return count;
}

template<typename T >
int LinearHashTable<T >::capacity() const {
	return array_size;
}

template<typename T >
double LinearHashTable<T >::load_factor() const {
	return (double)count / array_size; //casting because need decimal precision
}

template<typename T >
bool LinearHashTable<T >::empty() const {
	return count == 0;
}


template<typename T >
bool LinearHashTable<T >::member(T const &obj) const {

	bool isInside = false;
	int probe = 0;
	int hashIndex = (int)obj%array_size;
	for (int i = 0; i<array_size; i++) {

		hashIndex = (hashIndex + probe) % array_size; //calculate index with probing
		if (array[hashIndex] == obj && array_state[hashIndex] == OCCUPIED) {//first iteration of for loop, probing value will be zero. Then increment
			isInside = true;
			break;
		}
		probe=1;
	}

	return isInside;
}

template<typename T >
T LinearHashTable<T >::bin(int n) const {
	if (array_state[n] == OCCUPIED) {
		return array[n];
	}
	else {
		return NULL;
	}
}

template<typename T >
void LinearHashTable<T >::insert(T const &obj) {

	if (load_factor()>0.75) {
		doubleArray();
	}

	int index = findIndexToInsert(obj, array_state);
	array[index] = obj; //assigns corrct probed index
	array_state[index] = OCCUPIED;
	count++;

}

template<typename T >
bool LinearHashTable<T >::remove(T const &obj) {//DO I SHRINK FIRST OR DELETE
	if (!member(obj)) { //checks if the object is a member of the array
		return false;
	}
	array_state[findIndexOfObject(obj)] = DELETED;

	if (load_factor() <= 0.25 && initialCapacity<array_size) {
		halfArray();
	}

	count--;
	return true;
}

template<typename T >
void LinearHashTable<T >::clear() {
	for (int i = 0; i<array_size; i++) {
		array_state[i] = EMPTY; //makes all elements empty
	}
	count=0;
}

template<typename T >
void LinearHashTable<T >::print() const {
	for (int i = 0; i<array_size; i++) {
		cout << array[i] << endl;
	}
}

template<typename T >
void LinearHashTable<T >::doubleArray() {

	int oldArraySize = array_size;
	array_size = array_size * 2;
	T * newArray = new T[array_size];
	state *newArrayState = new state[array_size];

	for (int i = 0; i<array_size; i++) {//fill  location of empty if not occupied in new array
		newArrayState[i] = EMPTY;
	}

	for (int i = 0; i<oldArraySize; i++) {//old array size
		if (array_state[i] == OCCUPIED) {
			int indexToInsert = findIndexToInsert(array[i], newArrayState);
			newArray[indexToInsert] = array[i];//finds new index to insert  
			newArrayState[indexToInsert] = OCCUPIED;
		}
	}


	delete[] array;
	delete[] array_state;

	array = newArray;
	array_state = newArrayState;

}

template<typename T >
void LinearHashTable<T>::halfArray() {//mod decreases so remainder can change
									  //half more complex than double
	int oldArraySize = array_size;
	array_size = array_size / 2;//just this is different
	T * newArray = new T[array_size];
	state *newArrayState = new state[array_size];

	for (int i = 0; i<array_size; i++) {//fill  location of empty if not occupied in new array
		newArrayState[i] = EMPTY;
	}

	for (int i = 0; i<oldArraySize; i++) {//old array size
		if (i<oldArraySize && array_state[i] == OCCUPIED) {
			int indexToInsert = findIndexToInsert(array[i], newArrayState);
			newArray[indexToInsert] = array[i];//finds new index to insert  
			newArrayState[indexToInsert] = OCCUPIED;
		}
	}


	delete[] array;
	delete[] array_state;

	array = newArray;
	array_state = newArrayState;
}

template<typename T >
int LinearHashTable<T>::findIndexToInsert(T const &obj, state * array_state) {
	int probe = 0;
	int hashIndex = (int)obj%array_size;
	for (int i = 0; i<array_size; i++) {
		hashIndex = (hashIndex + probe) % array_size;

		if (!(array_state[hashIndex] == OCCUPIED)) {//seeing if its not Occupied 
			break;
		}
		probe=1;
	}

	return hashIndex;
}

template<typename T >
int LinearHashTable<T>::findIndexOfObject(T const &obj) {
	int probe = 0;
	int hashIndex = (int)obj%array_size;
	for (int i = 0; i<array_size; i++) {

		hashIndex = (hashIndex + probe) % array_size; //calculate index with probing
		if (array[hashIndex] == obj && array_state[hashIndex] == OCCUPIED) {//first iteration of for loop, probing value will be zero. Then increment
			break;
		}
		probe=1;
	}
	return hashIndex;
}
#endif