#include "MergeSortHeader.h"

template <class T>
inline void merge(T array[], T temp_array[], int start, int mid, int end) {
	int i_temp = 0, i_lower = start, i_upper = mid+1;

	while((i_lower <= mid) && (i_upper <= end)) {
		if(array[i_lower] < array[i_upper]) {
			temp_array[i_temp++] = array[i_lower++];
		} else {
			temp_array[i_temp++] = array[i_upper++];
		}
	}

	if(i_lower <= mid) {
		assert(i_upper > end);
		for(; i_lower <= mid; temp_array[i_temp++] = array[i_lower++]);
	} else {
		assert(i_lower > mid);
		assert(i_upper <= end);
		for(; i_upper <= end; temp_array[i_temp++] = array[i_upper++]);
	}

	assert(i_temp == end - start + 1);

	int i_array = start;
	for(i_temp = 0; i_array <= end; array[i_array++] = temp_array[i_temp++]);

}

template <class T>
inline void ms_helper(T array[], T temp_array[], int head, int tail) {

	if(head == tail) {
		return;
	}

	assert(tail > head);

	int mid = (head + tail) / 2;
	assert((mid >= head) && mid <= tail);

	ms_helper(array, temp_array, head, mid);
	ms_helper(array, temp_array, mid+1, tail);

	merge(array, temp_array, head, mid, tail);

}

template <class T>
inline void merge_sort(T array[], int size) {

	int head = 0, tail = size - 1;

	T *temp_array = new T[size];
	ms_helper(array, temp_array, head, tail);
	delete[] temp_array;

}

int main() {
	int array_1[] = {7,3,8,2,1,5,4};
	print(array_1, 7);
	merge_sort(array_1, 7);
	print(array_1, 7);
	cout << endl;

	return 0;
}


