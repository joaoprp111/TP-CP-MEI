#include <stdlib.h>
#include "sequential_bs.c"

int main()
{
	int N = 100;
	int BUCKET = 10;
	int *arr = (int *)malloc(N * sizeof(int));

	for (int i = 0; i < N; i++)
		arr[i] = rand() % N;

	bucketSortMain(arr, N, BUCKET);

	return 0;
}
