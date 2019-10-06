#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int g;

void *myThreadFun(void *vargp)
{
        static int s = 0;
        int myid = (int)vargp;

        ++s, ++g;
        printf("Thread ID: %d, Static: %d, Global: %d\n", myid, s, g);

        return NULL;
}

int main(void)
{
        int i;
        pthread_t tid;

        for (i = 0; i < 3; i++)
                pthread_create(&tid, NULL, myThreadFun, (void *)&i);

        pthread_exit(NULL);

        return 0;
}
