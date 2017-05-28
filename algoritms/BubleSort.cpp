//============================================================================
// Name        : BubleSort.cpp
// Author      : Klim
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "BubleSortHeader.h"

template <class T>
inline void bubble_sort(T array[], int size) {
	int i, j;
	for (int i = 0; i < size-1; ++i) {
		for (int j = size-1; j > i; --j) {
			if(array[j-1] > array[j]) {
				swap(array, j-1, j);
			}
		}
	}
}

int main() {

	int array_1[] = {7,3,8,2,1,5,4};
	print(array_1, 7);
	bubble_sort(array_1, 7);
	print(array_1, 7);
	cout << endl;

	return 0;
}
