#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define ARR_SIZE 10

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

size_t partition(size_t const len, double arr[len]) {
    /* always pivot at the end, for simplicity */
    size_t pivot = len - 1;
    size_t i = 0;
    size_t j = pivot - 1;

    while (true) {
        while ((i != (len - 1)) && (arr[i] <= arr[pivot]))
            ++i;
        while ((j != 0) && (arr[j] >= arr[pivot]))
            --j;

        double temp = arr[i];
        if (i < j) { /* if left and right have not crossed */
            arr[i] = arr[j];
            arr[j] = temp;
        } else {
            arr[i] = arr[pivot];
            arr[pivot] = temp;
            return i; /* return index the pivot was moved to */
        }
    }
}

void quick_sort(size_t const len, double arr[len]) {
    if (len < 2) return;

    size_t final_pivot_index = partition(len, arr);

    /* now pivot has been moved to its proper location */
    /* left half spans from 0 to final_pivot_index-1 */
    quick_sort(final_pivot_index, arr);
    /* right half spans from final_pivot_index+1 to len-1 */
    quick_sort(len - final_pivot_index - 1, arr + final_pivot_index + 1);
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

    quick_sort(ARR_SIZE, arr);

    printf("\n");
    printf("Array after sort:\n");
    print_arr(ARR_SIZE, arr);
    print_arr_is_sorted(ARR_SIZE, arr);

    return EXIT_SUCCESS;
}
