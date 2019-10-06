#include <fts.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/errno.h>

int main(void)
{
        FTS *ftsp;
        int ret = EXIT_FAILURE;
        char *paths[] = { ".", NULL };

        ftsp = fts_open(paths, FTS_PHYSICAL, NULL);
        if (!ftsp) {
                perror("fts_open\n");
                return -1;
        }

        while (1) {
                FTSENT *ent;

                ent = fts_read(ftsp);
                if (!ent) {
                        if (!errno)
                                break;
                        perror("fts_read\n");
                        goto end;
                }

                if (ent->fts_info & FTS_D)
                        printf("Enter dir: ");
                else if (ent->fts_info & FTS_DP)
                        printf("Exit dir:  ");
                else if (ent->fts_info & FTS_F)
                        printf("File:      ");
                else
                        printf("Other:     ");

                printf("%s %s\n", ent->fts_path, ent->fts_name);

                // TRY THIS: Change this to 1, try FTS_NOCHDIR option described above
                if (0) {
                        char buf[2048] = {0};
                        char *c = getcwd(buf, 2048);

                        if (!c)
                                perror("getcwd\n");
                        else
                                printf("current working directory: %s\n", c);
                }
        }
        ret = EXIT_SUCCESS;

end:
        if (fts_close(ftsp) == -1)
                perror("fts_close\n");

        return ret;
}
