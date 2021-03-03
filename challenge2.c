#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* F(x) = sin(x) */
double F(double x) {
    return sin(x);
}

/* f(x) = numerical derivative of F at x */
double f(double x) {
    double delta = 0.01;
    double y1 = sin(x - delta);
    double y2 = sin(x + delta);

    return (y2 - y1)/(2 * delta);
}

int main(void) {
    /* check correctness for integers x = -5 ... 5 */
    for (int i = -5; i < 6; ++i) {
        printf("F(%d) = %f, f(%d) = %f, exact derivative at x is %f\n",
               i, F(i), i, f(i), cos(i));
        printf("(estimate is off by %f)\n", fabs(cos(i) - f(i)));
        printf("\n");
    }

    return EXIT_SUCCESS;
}
