#include "SelectionSortHeader.h"

template <class T>
inline int get_min_index(T array[], int left, int right) {
	int min_index = left;
	int i;
	for (int i = left; i < right; ++i) {
		if(array[i] < array[min_index]) {
			min_index = i;
		}
	}
	return min_index;
}

template <class T>
inline void selection_sort(T array[], int size) {
	int i;
	int min_index;
	for (int i = 0; i < size; ++i) {
		min_index = get_min_index(array, i, size);
		if(min_index != i) {
			swap(array, i, min_index);
		}
	}
}

int main() {

	int array_1[] = {7,3,8,2,1,5,4};
	print(array_1, 7);
	selection_sort(array_1, 7);
	print(array_1, 7);
	cout << endl;

	return 0;
}
