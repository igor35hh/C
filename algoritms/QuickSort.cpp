#include "QuckSortHeader.h"

template <class T>
inline int get_pe(T array[], int lower, int upper) {
	return lower;
}

template <class T>
inline int partittion(T array[], int start, int end, int pe_index) {
	T pe = array[pe_index];
	int head = start, tail = end;

	while(head < tail) {
		while( (array[tail] > pe) ) {
			--tail;
		}
		assert(array[tail] <= pe);
		while( (array[head] < pe) ) {
			++head;
		}
		assert(array[head] >= pe);
		if(head < tail) {
			swap(array, head, tail);
		}
	}

	assert(head == tail);
	assert(array[head] == pe);

	return tail;

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
	int mid = partittion(array, head, tail, pe_index);
	assert( (mid >= head) && (mid <= tail) );

	gs_helper(array, head, mid-1);
	gs_helper(array, mid+1, tail);
}

template <class T>
inline void quick_sort(T array[], int size) {
	int head = 0, tail = size-1;
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
