#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define ARR_SIZE 10

void merge_sort(size_t const len, double arr[len]) {
    if (len > 1) {
        /* split arr into left and right halves */
        size_t const mid = len / 2;
        size_t const rem = len % 2;
        double l_arr[mid];
        double r_arr[mid + rem];

        for (size_t i = 0; i < mid; ++i) {
            l_arr[i] = arr[i];
        }
        for (size_t i = 0; i < (mid + rem); ++i) {
            r_arr[i] = arr[mid + i];
        }

        /* merge sort each half */
        merge_sort(mid, l_arr);
        merge_sort((mid + rem), r_arr);

        /* combine the sorted halves */
        size_t l_i = 0; // index for going through l_arr
        size_t r_i = 0; // index for going through r_arr
        size_t i = 0;   // index of array merging in to
        /* merge arrays until one of the halves is done */
        while(i < len && l_i < mid && r_i < (mid + rem)) {
            if (l_arr[l_i] < r_arr[r_i])
                arr[i++] = l_arr[l_i++];
            else
                arr[i++] = r_arr[r_i++];
        }
        /* merge in the rest of whichever half is not done, if any */
        while (i < len && l_i < mid)
            arr[i++] = l_arr[l_i++];
        while (i < len && r_i < (mid + rem))
            arr[i++] = r_arr[r_i++];
    } else { // base case
        return;
    }
}

bool arr_is_sorted(size_t const len, double arr[len]) {
    if (len < 1) return false;
    if (len == 1) return true;

    for (size_t i = 0; i < len - 1; ++i) {
        if (arr[i + 1] < arr[i]) {
            return false;
        }
    }

    return true;
}

void print_arr_is_sorted(size_t const len, double arr[len]) {
    bool sorted = arr_is_sorted(len, arr);
    if (sorted) {
        printf("Array is sorted.\n");
    } else {
        printf("Array is not sorted.\n");
    }
}

void print_arr(size_t const len, double arr[len]) {
    if (len < 1) return;

    for (size_t i = 0; i < len; ++i) {
        printf("%f\n", arr[i]);
    }
}

int main(void) {
    double arr[ARR_SIZE] = {
        [0] = -27.5,
        [1] = -27.5,
        [2] = 0.0,
        [3] = 1.0,
        [4] = -5.0,
        [5] = 32.1282,
        [6] = 1.0,
        [7] = 1.001,
        [8] = 0.0,
        [9] = 1.0
    };

    printf("Array before sort:\n");
    print_arr(ARR_SIZE, arr);
    print_arr_is_sorted(ARR_SIZE, arr);

    merge_sort(ARR_SIZE, arr);

    printf("\n");
    printf("Array after sort:\n");
    print_arr(ARR_SIZE, arr);
    print_arr_is_sorted(ARR_SIZE, arr);

    return EXIT_SUCCESS;
}
