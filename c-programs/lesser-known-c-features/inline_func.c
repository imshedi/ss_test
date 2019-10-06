#include <stdio.h>

inline static void fun0(int a, int b)
{
        printf("a = %d & b = %d\n", a, b);
}

inline static int fun1(int x)
{
        return x * x;
}

int main(void)
{
        fun0(0, 1);
        printf("square value = %d\n", fun1(3));

        return 0;
}
