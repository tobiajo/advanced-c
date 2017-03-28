#include <time.h>
#include <stdio.h>

#define N 1024

typedef void (*void_noargs)();

double measure(void_noargs func) {
	clock_t start = clock();
	func();
	return (double) (clock() - start) / CLOCKS_PER_SEC;
}

void fragment_a() {
	int X[N][N];
	for (int j = 0; j < N; j++)
		for (int i = 0; i < N; i++) X[i][j] = 1;
}

void fragment_b() {
	int X[N][N];
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) X[i][j] = 1;
}

int main(int argc, char *argv[]) {
	printf("a: %f s\n", measure(fragment_a));
	printf("b: %f s\n", measure(fragment_b));
	return 0;
}
