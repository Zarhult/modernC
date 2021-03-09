#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
/* Program to determine pi to n decimal places with no prior knowledge of pi's value.
   This takes over a minute for 10 decimal places and probably much longer for further.
   Recommended to compile with -O2, and perhaps -march=native for extra optimization. 
   This would probably estimate pi faster with a better approach than the Leibniz formula. */

/* Returns how many leading decimal places match between two doubles. */
size_t matching_decs(double num1, double num2) {
    /* Convert doubles to strings for ease of digit access. */
    char buf1[255];
    char buf2[255];
    snprintf(buf1, sizeof(buf1), "%.253f", num1); // Since first 2 chars are "3."
    snprintf(buf2, sizeof(buf2), "%.253f", num2);

    size_t result = 0;
    size_t i = strchr(buf1, '.') - buf1 + 1; // Index of first char after decimal
    size_t j = strchr(buf2, '.') - buf2 + 1; // Etc
    while (buf1[i] == buf2[i]) {
        ++i;
        ++j;
        ++result;
    }

    return result;
}

/* f(n) = ((-1)^n) * 1/(2n+1) from n=0 to infinity */
double f(size_t const n) {
    double term = 1.0 / (2.0*n + 1.0);
    if (n % 2 != 0) term *= -1.0;

    return term;
}

/* Estimates pi up to n decimal places.
   Uses the Leibniz formula (pi/4 = sum of f(n) from n=0 to infinity) so we know the maximum
   error. For a convergent alternating series, maximum error is the absolute value of the
   first term not included. */
double pi_to_n(size_t const n) {
    if (n == 0) return -1.0; // Should estimate to at least the first decimal place

    size_t curr_n = 0;
    double pi_estimate = 0.0;
    double curr_error = f(0) * 4.0; // Pi is always within pi_estimate +/- curr_error
    size_t correct_decs = 0; // Number of decimal places in estimate that are certain
    size_t count = 0;
    do {
        ++count;
        pi_estimate += f(curr_n) * 4.0;
        ++curr_n;

        /* Digits that match between the error bounds are proven accurate.
           Only check this every 10000000 iterations for efficiency. */
        if (count % 10000000 == 0) {
            count = 0;

            curr_error = fabs(f(curr_n) * 4.0);
            correct_decs = matching_decs(pi_estimate - curr_error, pi_estimate + curr_error);
        }
    } while (correct_decs < n);

    return pi_estimate;
}

int main(void) {
    int const n_places = 9;
    /* Calculate answer and truncate it to only the correct decimal places. */
    double const tens_factor = pow(10.0, n_places);
    double const rounded_result = floor(tens_factor * pi_to_n(n_places)) / tens_factor;
    printf("Pi to %d decimal places is %.*f\n", n_places, n_places, rounded_result);

    return EXIT_SUCCESS;
}
