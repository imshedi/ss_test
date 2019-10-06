#include <stdio.h>
#include <complex.h>

int main(void)
{
    double complex result;
    double complex dc1 = 3 + 2*I;
    double complex dc2 = 4 + 5*I;

    result = dc1 + dc2;
    printf("%f + i%f\n", creal(result), cimag(result));

    return 0;
}
