//============================================================================
// Name        : Threads.cpp
// Author      : Klim
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <stdio.h>
#include <time.h>

unsigned long long int fibonacci(unsigned int n);

int main() {

	puts("Sequintal calls to fibonacci(50) and fibonacci(49)");

	time_t startTime1, endTime1, startTime2, endTime2;
	double dif1, dif2, dif3;

	time(&startTime1);
		puts("Calculating fibonacci(50)");
		unsigned long long int result1 = fibonacci(50);
	time(&endTime1);
	dif1 = difftime(endTime1, startTime1);
	printf("fibonacci ( %u ) = %llu\n", 50, result1);
	printf("Calculation time = %f minutes\n\n", dif1/60);

	time(&startTime2);
		puts("Calculating fibonacci(49)");
		unsigned long long int result2 = fibonacci(49);
	time(&endTime2);
	dif2 = difftime(endTime2, startTime2);
	printf("fibonacci ( %u ) = %llu\n", 49, result2);
	printf("Calculation time = %f minutes\n\n", dif2/60);

	dif3 = difftime(endTime2, startTime1);
	printf("Total calculation time = %f minutes\n", dif3/60);

	return 0;
}

unsigned long long int fibonacci(unsigned int n) {
	if(0 == n || 1 == n) {
		return n;
	} else {
		return fibonacci(n-1) + fibonacci(n-2);
	}
}
