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

void quick_sort(size_t const len, double arr[len]) {
    if (len < 2) return;

    /* always pivot at the end, for simplicity */
    size_t pivot = len - 1;
    size_t left = 0;
    size_t right = pivot - 1;

    /* partition the array */
    /* do so within this function so as to avoid using pointers */
    while (true) {
        size_t i = left;
        size_t j = right;
        while (i < pivot && arr[i] <= arr[pivot])
            ++i;
        while (j >= 0 && arr[j] > arr[pivot])
            --j;

        size_t temp = arr[j];
        if (i < j) {
            arr[j] = arr[i];
            arr[i] = temp;
        } else {
            arr[j] = arr[pivot];
            arr[pivot] = temp;
            break;
        }
    }

    /* now pivot has been moved to its proper location */
    /* left half spans from left to pivot-1 */
    quick_sort(pivot, arr);
    /* right half spans from pivot+1 to len-1*/
    quick_sort((len - pivot - 1), arr + pivot + 1);
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
