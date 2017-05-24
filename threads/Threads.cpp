//============================================================================
// Name        : Threads.cpp
// Author      : Klim
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <stdio.h>
#include <time.h>
#include <threads.h>

#define NUMBERS_OF_THREADS 2

int startFibonacci(void *nPtr);
unsigned long long int fibonacci(unsigned int n);

typedef struct ThreadData {
	time_t startTime;
	time_t endTime;
	unsigned int number;
} ThreadData;

int main() {

	ThreadData data[NUMBERS_OF_THREADS] =
	{
			[0] = {.number = 50},
			[1] = {.number = 49}
	};

	thrd_t threads[NUMBERS_OF_THREADS];

	puts("Unsequintal calls to fibonacci(50) and fibonacci(49)");

	for (unsigned int i = 0; i < NUMBERS_OF_THREADS; ++i) {
		printf("Starting thread to calculate fibonacci( %d )\n", data[i].number);
		if(thrd_create(&threads[i], startFibonacci, &data[i]) != thrd_success) {
			puts("Failed to create thread");
		}
	}

	for (int i = 0; i < NUMBERS_OF_THREADS; ++i) {
		thrd_join(threads[i], NULL);
	}

	time_t startTime = (data[0].startTime > data[1].startTime) ? data[0].startTime : data[1].startTime;
	time_t endTime = (data[0].endTime > data[1].endTime) ? data[0].endTime : data[1].endTime;

	printf("Total calculation time = %f minutes\n", difftime(endTime, startTime)/60);

	return 0;
}

int startFibonacci(void *ptr) {
	ThreadData *dataPTR = (THreadData *) ptr;
	dataPTR->startTime = time(NULL);
	printf("Calculating fibonacci ( %d )\n", dataPTR->number);
	printf("fibonacci ( %d ) =%lld\n", dataPTR->number, fibonacci(dataPTR->number));
	dataPTR->endTime = time(NULL);
	printf("Calculation time = %f minutes\n\n", difftime(dataPTR->endTime, dataPTR->startTime) / 60);
	return thrd_success;
}

unsigned long long int fibonacci(unsigned int n) {
	if(0 == n || 1 == n) {
		return n;
	} else {
		return fibonacci(n-1) + fibonacci(n-2);
	}
}
