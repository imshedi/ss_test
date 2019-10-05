#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>

#define CENT	100	 /*! 100% marker */
#define FSIZE	512	 /*! File size in MB */
#define BUFSIZE	512	 /*! Cpoy buffer size */
#define MD5HASH	33	 /*! md5sum hash buf size */
#define FILE1	"f1.bin" /*! Source file name */
#define FILE2	"f2.bin" /*! Destination file name */

void pr_char(uint32_t count, char c)
{
        while (count--)
                putchar(c);
        fflush(stdout);
}

void get_hash(const char *fname, char *buf)
{
        FILE *fp;

        sprintf(buf, "md5sum %s", fname);
        fp = popen(buf, "r");
        if (!fp) {
                fprintf(stderr, "popen(%s) failed\n", buf);
                return;
        }

        fscanf(fp, "%s", buf);

        pclose(fp);
}

void print_progress(uint32_t i, uint32_t size)
{
        uint32_t ret;
        static uint8_t p;

        if (size < CENT && i != size)
                return;
        else if (size < CENT && i >= size)
                ret = CENT;
        else if (size >= CENT)
                ret = i / (size / CENT);

        if (((size / CENT) == 1) && ret >= CENT && i != size)
                return;

        if (ret == p || (ret >= CENT && size != i))
                return;

        if (!p)
                printf("Progress: [ ");

        p = ret;
        pr_char(p, '#');
        pr_char(CENT - p, ' ');
        ret = CENT + printf(" ] (%03d%%)", p);
        fflush(stdout);
        pr_char(ret, '\b');

        if (p >= CENT) {
                p = 0;
                printf("\n");
        }
}

int32_t main(void)
{
        FILE *fp1;
        FILE *fp2;
        char *buf;
        uint32_t i;
        uint32_t size;
        char hash1[MD5HASH];
        char hash2[MD5HASH];
        int32_t ret = EXIT_FAILURE;

        buf = malloc(sizeof(char) * BUFSIZE);
        if (!buf) {
                fprintf(stderr, "malloc error\n");
                return ret;;
        }

        sprintf(buf, "dd if=/dev/urandom of=%s count=%d bs=1M status=none", FILE1, FSIZE);
        //sprintf(buf, "seq %d > %s", FSIZE, FILE1);
        //sprintf(buf, "echo 1234567890ABCDEF > %s", FILE1);
        system(buf);

        fp1 = fopen(FILE1, "r");
        if (!fp1) {
                fprintf(stderr, "%s fopen error\n", FILE1);
                return ret;
        }

        fp2 = fopen(FILE2, "w+");
        if (!fp2) {
                fprintf(stderr, "%s fopen error\n", FILE1);
                goto f1_err;
        }

        if (fseek(fp1, 0, SEEK_END)) {
                fprintf(stderr, "%s fseek error\n", FILE1);
                goto f2_err;
        }

        size = ftell(fp1);
        rewind(fp1);

        uint32_t tmp;

        tmp = (size >= BUFSIZE) ? BUFSIZE : size;

        for (i = 0; i < size; ) {
                i += (i + BUFSIZE >= size) ? (tmp = size - i) : BUFSIZE;

                if (!tmp)
                        break;

                if (fread(buf, tmp, 1, fp1) < 0 ||
                                fwrite(buf, tmp, 1, fp2) < 0) {
                        perror("fread\n");
                        goto f2_err;
                }
                fflush(fp2);

                print_progress(i, size);
                if (size < BUFSIZE)
                        break;
        }

        get_hash(FILE1, hash1);
        get_hash(FILE2, hash2);

        if (!strcmp(hash1, hash2))
                printf("Files are identical, copy successful\n");
        else
                printf("Files are not identical, copy failed\n");

        remove(FILE1);
        remove(FILE2);

        ret = EXIT_SUCCESS;

f2_err:
        fclose(fp2);

f1_err:
        fclose(fp1);
        free(buf);

        return ret;
}
