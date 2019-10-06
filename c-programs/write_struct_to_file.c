#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FNAME	"wr_to_file.dat"

typedef struct _t0 {
        int id;
        char fname[8];
        char lname[8];
} t0;

typedef struct _t1 {
        int id;
        char fname[8];
        char lname[8];
        int val;
} t1;

typedef union _test {
        t0 t00;
        t1 t01;
} test;

FILE *fp;

int read_file(void)
{
        t1 *in;
        int ret = -1;

        fp = fopen(FNAME, "r");
        if (!fp) {
                fprintf(stderr, "\nfopen error\n");
                return ret;
        }

        in = (t1 *)calloc(1, sizeof(test));
        if (!in) {
                perror("\nmalloc error\n");
                goto read_end;
        }

        while (fread(in, sizeof(test), 1, fp) > 0)
                printf("id = %d fname = %s lname = %s val: %X\n", in->id, in->fname, in->lname, in->val);

read_end:
        if (in)
                free(in);
        fclose(fp);

        return ret;
}

int write_file(void)
{
        t0 *in;
        int ret = -1;

        fp = fopen(FNAME, "w");
        if (!fp) {
                fprintf(stderr, "\nfopen error\n");
                return ret;
        }

        in = (t0 *)malloc(sizeof(test));
        if (!in) {
                perror("\nmalloc error\n");
                goto write_end;
        }

        in->id = 1;
        strcpy(in->fname, "fname");
        strcpy(in->lname, "lname");

        fwrite(in, sizeof(test), 1, fp);

        if (!ferror(fp))
                printf("Contents to file written successfully!\n");
        else
                printf("Error writing file!\n");

write_end:
        if (in)
                free(in);

        fclose(fp);

        return ret;
}

int main(int argc, char **argv)
{
        (void)argv;

        return (argc == 1) ? write_file() : read_file();
}
