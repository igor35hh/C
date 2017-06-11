#include <stdio.h>

int factorial(int c) {
	return (c == 0) ? 1 : c * factorial(c-1);
}

int tailfunction(int n, int acc) {
	return (n == 0) ? acc : tailfunction(n-1, acc * n);
}

int factorialtwo(int n) {
	return tailfunction(n, 1);
}

int main(void)
{
	printf("%d\n", factorial(5));

	printf("%d\n", factorialtwo(5));

	return 0;
}
