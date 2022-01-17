#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <stdio.h>
#include "quicksort.c"

/*int maxInArray(int *arr, int size)
{
    int max = arr[0], i;
    for (i = 1; i < size; i++)
    {
        if (arr[i] > max)
            max = arr[i];
    }

    return max;
}

int minInArray(int *arr, int size)
{
    int min = arr[0], i;
    for (i = 1; i < size; i++)
    {
        if (arr[i] < min)
            min = arr[i];
    }

    return min;
}*/

void bucketSort(int *arr, int **buckets, int N, int BUCKET, double *time)
{
    int i, j, num_threads;
    int range = N / BUCKET;
    int num_elements[BUCKET];

    if (BUCKET < 1000)
    {
        num_threads = 10;
    }
    else
    {
        num_threads = 16; //Without using specific node, this value is 20
    }

    // Initialize buckets counter, that counts how many elements are inside each bucket
    for (i = 0; i < BUCKET; i++)
        num_elements[i] = 0;

    //2. Divide the elements by the buckets
    for (i = 0; i < N; i++)
    {
        //printf("I: %d\n", i);
        // Find the bucket index for this element (arr[i])
        //printf("%d\n", arr[i]);
        double test = ((double)arr[i]) / range;
        //printf("Test %f\n", test);
        int b = (int)floor(test);
        if (b > BUCKET - 1)
            b = BUCKET - 1;
        //printf("Bucket index: %d\n", b);

        buckets[b] = (int *)realloc(buckets[b], (num_elements[b] + 1) * sizeof(int));
        buckets[b][num_elements[b]] = arr[i];
        num_elements[b]++;
    }

    // Print the buckets with their elements not ordered for testing
    /*for (i = 0; i < BUCKET; i++)
        for (j = 0; j < num_elements[i]; j++)
            printf("Bucket %d element %d: %d\n\n", i, j, buckets[i][j]);*/

    //3. Order the elements of each bucket
    *time = omp_get_wtime();
#pragma omp parallel num_threads(num_threads)
#pragma omp for schedule(static)
    for (i = 0; i < BUCKET; i++)
    {
        if (num_elements[i] > 1)
            quickSort(buckets[i], 0, num_elements[i] - 1);
    }
    *time = omp_get_wtime() - *time;

    //printf("\n\n----------------------------------------------------------\n\n");

    // Print the buckets with their elements ordered for testing
    /*for (i = 0; i < BUCKET; i++)
        for (j = 0; j < num_elements[i]; j++)
            printf("Bucket %d element %d: %d\n\n", i, j, buckets[i][j]);*/

    //4. Fill the final array in order
    int count = 0;
    for (i = 0; i < BUCKET; i++)
    {
        for (j = 0; j < num_elements[i]; j++)
            arr[count++] = buckets[i][j];
        free(buckets[i]);
    }
}

float bucketSortMain(int *arr, int size, int num_buckets)
{
    int i, BUCKET, N;
    double time = 0.0;

    BUCKET = num_buckets;
    N = size;
    // Buckets - array of buckets, each bucket has an array with the elements inside it
    int **buckets = (int **)malloc(BUCKET * sizeof(int *));

    // 1. Initialize buckets
    for (i = 0; i < BUCKET; i++)
        buckets[i] = NULL;

    // Print the initial array
    //printf("\n\nInitial array:\n\n");
    //printArray(arr, N);

    // BucketSort to order the arr elements
    bucketSort(arr, buckets, N, BUCKET, &time);

    free(buckets);

    // Print the final array
    //printf("\n\nFinal array:\n\n");
    //printArray(arr, N);

    return time;
}