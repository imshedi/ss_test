#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define SIZEOFARR(a)	((int32_t)(sizeof(a) / sizeof(a[0])))

int32_t binsrch(void *elt,
                int32_t eltsize,
                void *arr,
                int32_t arrsize,
                int32_t (*fcmp)(const void *, const void *))
{
        int32_t i;
        char *array;

        if (!elt || (eltsize < 1) || !arr || (arrsize < 1) || !fcmp)
                return -1;

        for (array = arr, i = arrsize >> 1; i < arrsize; ) {
                int32_t cmpr = fcmp(&array[i * eltsize], elt);

                if (!cmpr)
                        return i;

                if (cmpr < 0) {
                        i += (arrsize - i + 1) >> 1;
                } else {
                        arrsize = i;
                        i >>= 1;
                }
        }

        return -1;
}

int32_t int_cmp(const void *v1, const void *v2)
{
        return (*(int32_t *)v1 - *(int32_t *)v2);
}

int32_t str_cmp(const void *s1, const void *s2)
{
        return strcmp(s1, s2);
}

void test_strings(void)
{
        int32_t i;
        char strs[][32] = {
                "Fallout",
                "John Wick",
                "Jason Bourne",
                "James Bond",
                "Ethan Hunt",
                "Sherlock Holmes",
                "Batman",
                "Captain America",
                "Iron Man",
                "Jarvis",
                "Thor",
        };

        printf("\nBefore sorting strings\n");
        for (i = 0; i < SIZEOFARR(strs); i++)
                printf("%s\n", (char *)&strs[i]);

        qsort(strs, SIZEOFARR(strs), sizeof(strs[0]), str_cmp);

        printf("\nAfter sorting strings\n");
        for (i = 0; i < SIZEOFARR(strs); i++)
                printf("%s\n", (char *)&strs[i]);

        i = rand() % SIZEOFARR(strs);
        printf("\n\nTrying binary search\n");
        printf("\nExpected Result: Element - %s is at index %d\n", strs[i], i);
        i = binsrch("shreenihdi", sizeof(strs[0]), *strs, SIZEOFARR(strs), str_cmp);
        printf("\nActual Result: Element - %s is at index %d\n\n", i > -1 ? strs[i] : NULL, i);
}

void test_int(void)
{
        int32_t i;
        int32_t ret;
        int32_t arr[32] = {0};

        srand(time(NULL));
        for (i = 0; i < SIZEOFARR(arr); i++)
                arr[i] = rand() % 1000;

        printf("\nArray elements are\n");
        for (i = 0; i < SIZEOFARR(arr); i++)
                printf("%d  ", arr[i]);

        printf("\n\nArray elements after sorting\n");
        qsort(arr, SIZEOFARR(arr), sizeof(int32_t), int_cmp);
        for (i = 0; i < SIZEOFARR(arr); i++)
                printf("%d  ", arr[i]);

        printf("\n\nTrying binary search\n");
        ret = rand() % SIZEOFARR(arr);
        printf("\nExpected Result: Element - %d is at index %d\n", arr[ret], ret);

        ret = binsrch(&arr[ret], sizeof(int32_t), arr, SIZEOFARR(arr), int_cmp);
        printf("\nActual Result: Element - %d is at index %d\n\n", arr[ret], ret);
}

int32_t main(void)
{
        printf("\nTrying the functionality for integer array\n");
        test_int();

        printf("\nTrying the functionality for string array\n");
        test_strings();

        return EXIT_SUCCESS;
}
