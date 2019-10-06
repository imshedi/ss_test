#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct test {
        int a;
        int b;
        char *p;
} test;

int main(void)
{
        int i;
        char **ptr;
        test x[5] = {0};

        x[1].p = malloc(32);
        if (!x[1].p) {
                perror("\n");
                return -1;
        }

        sprintf(x[1].p, "Index: %d", 1);

        for (i = 0; i < 5; i++)
                printf("Before. %p\n", x[i].p ? x[i].p : NULL);

        ptr = &x[1].p;
        strcpy(*ptr, "Index: 1 - Hello World!!!");
        printf("\nptr: %p %s\n\n", ptr, *ptr);

        for (i = 0; i < 4; i++)
                memcpy(&x[i], &x[i + 1], sizeof(test));

        memset(&x[4], 0, sizeof(test));

        for (i = 0; i < 5; i++)
                printf("After. %p\n", x[i].p);

        printf("\nptr: %p->%s\n\n", ptr, *ptr);

        free(x[0].p);

        return 0;
}
