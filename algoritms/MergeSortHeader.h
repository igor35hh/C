#include <iostream>
#include <cassert>

using namespace std;

template <class T>
inline void swap(T array[], int pos1, int pos2) {
	T temp;
	temp = array[pos1];
	array[pos1] = array[pos2];
	array[pos2] = temp;
}

template <class T>
inline void print(T array[], int size) {
	int i;
	for(i = 0; i < size; ++i) {
		cout << array[i] << " ";
	}
	cout << endl;
}
