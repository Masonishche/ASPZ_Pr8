#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define ARRAY_SIZE 10000

// Comparison function for integers
int compare_int(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// Generate different types of arrays
void generate_arrays(int *sorted, int *reverse, int *random, int *duplicates, int size) {
    for (int i = 0; i < size; i++) {
        sorted[i] = i;                     // Sorted array
        reverse[i] = size - i - 1;         // Reverse sorted array
        random[i] = rand() % size;         // Random array
        duplicates[i] = size / 2;          // Array with duplicates
    }
}

// Check if array is sorted
int is_sorted(int *arr, int size) {
    for (int i = 1; i < size; i++) {
        if (arr[i] < arr[i - 1]) return 0;
    }
    return 1;
}

// Test qsort on an array
void test_qsort(int *arr, int size, const char *type) {
    int *copy = malloc(size * sizeof(int));
    memcpy(copy, arr, size * sizeof(int));
    
    clock_t start = clock();
    qsort(copy, size, sizeof(int), compare_int);
    clock_t end = clock();
    
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Sorting %s array: %f seconds\n", type, time_spent);
    printf("Is %s array sorted? %s\n", type, is_sorted(copy, size) ? "Yes" : "No");
    
    free(copy);
}

int main() {
    srand(time(NULL));
    int *sorted = malloc(ARRAY_SIZE * sizeof(int));
    int *reverse = malloc(ARRAY_SIZE * sizeof(int));
    int *random = malloc(ARRAY_SIZE * sizeof(int));
    int *duplicates = malloc(ARRAY_SIZE * sizeof(int));
    
    if (!sorted || !reverse || !random || !duplicates) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    generate_arrays(sorted, reverse, random, duplicates, ARRAY_SIZE);
    
    printf("Testing qsort performance on different inputs:\n");
    test_qsort(sorted, ARRAY_SIZE, "sorted");
    test_qsort(reverse, ARRAY_SIZE, "reverse sorted");
    test_qsort(random, ARRAY_SIZE, "random");
    test_qsort(duplicates, ARRAY_SIZE, "duplicates");
    
    // Additional correctness tests
    printf("\nRunning correctness tests:\n");
    int test1[] = {5, 2, 8, 1, 9}; // Unsorted
    int test2[] = {1, 1, 1, 1};     // All equal
    int test3[] = {1};              // Single element
    int test4[] = {};               // Empty array
    
    qsort(test1, 5, sizeof(int), compare_int);
    printf("Test 1 (unsorted): %s\n", is_sorted(test1, 5) ? "Pass" : "Fail");
    
    qsort(test2, 4, sizeof(int), compare_int);
    printf("Test 2 (all equal): %s\n", is_sorted(test2, 4) ? "Pass" : "Fail");
    
    qsort(test3, 1, sizeof(int), compare_int);
    printf("Test 3 (single element): %s\n", is_sorted(test3, 1) ? "Pass" : "Fail");
    
    qsort(test4, 0, sizeof(int), compare_int);
    printf("Test 4 (empty): %s\n", is_sorted(test4, 0) ? "Pass" : "Fail");
    
    free(sorted);
    free(reverse);
    free(random);
    free(duplicates);
    return 0;
}
