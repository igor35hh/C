#include "BetterQuckSortHeader.h"

template <class T>
inline int get_pe(T array[], int lower, int upper) {

	assert((upper-lower) >= 2);
	int mid = (lower+upper)/2;

	if((array[lower] <= array[mid])) {
		if(array[mid] <= array[upper]) {
			return mid;
		} else if(array[upper] <= array[lower]) {
			return lower;
		} else {
			return upper;
		}
	} else {
		assert(array[lower] > array[mid]);
		if(array[lower] <= array[upper]) {
			return lower;
		} else if(array[upper] <= array[mid]) {
			return mid;
		} else {
			return upper;
		}
	}

}

template <class T>
inline int partitition(T array[], int start, int end, int pe_index) {
	T pe = array[pe_index];
	swap(array, pe_index, end);
	int head = start, tail = end-1;

	while(true) {

		while((array[head] < pe)) {
			++head;
		}
		assert(array[head] >= pe);

		while((array[tail] > pe) && (tail > start)) {
			--tail;
		}
		assert(array[tail] <= pe);

		if(head >= tail) {
			break;
		}
		swap(array, head++, tail--);
	}
	swap(array, head, end);
	assert(array[head] == pe);
	return head;
}

template <class T>
inline void gs_helper(T array[], int head, int tail) {
	int diff = tail - head;
	if(diff < 1) {
		return;
	}
	if(diff == 1) {
		if(array[head] > array[tail]) {
			swap(array, head, tail);
			return;
		}
	}
	int pe_index = get_pe(array, head, tail);
	int mid = partitition(array, head, tail, pe_index);
	assert((mid>=head) && (mid<=tail));

	gs_helper(array, head, mid-1);
	gs_helper(array, mid+1, tail);
}

template <class T>
inline void quick_sort(T array[], int size) {
	int head = 0, tail = size - 1;
	gs_helper(array, head, tail);
}

int main() {

	int array_1[] = {7,3,8,2,1,5,4};
	print(array_1, 7);
	quick_sort(array_1, 7);
	print(array_1, 7);
	cout << endl;

	return 0;
}


