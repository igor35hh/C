#include <iostream>

void shell_sort(int array[], int n) {
	int temp;

	for (int gap = n; gap > 0; gap /= 2) {
		if(gap<n) {
			for(int i = gap; i < n; ++i) {
				for(int j = i-gap; j>=0 && array[j] > array[j+gap]; j -= gap) {
					temp = array[j];
					array[j] = array[j+gap];
					array[j+gap] = temp;
				}
			}
		}
	}
}

void print(const int array[], int n) {
	for(int i = 0; i<n; ++i) {
		std::cout << array[i] << ' ';
	}
	std::cout << '\n';
}

int main() {
	//int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int a[] = {0, 1, 2, 5, 4, 3, 6, 9, 8, 7, 10, 11, 12, 14, 15, 13, 16, 17, 19, 18 };
	constexpr int N = sizeof(a) / sizeof(a[0]);
	print(a, N);
	shell_sort(a, N);
	print(a, N);

}
