#include <ftw.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

static int32_t rm_files(const char *pathname, const struct stat *sbuf,
                int32_t type, struct FTW *ftwb)
{
        int32_t ret;

        ret = remove(pathname);
        if (ret < 0)
                fprintf(stderr, "ERROR: remove(%d->%s)\n", errno, strerror(errno));

        return ret;
}

int32_t main(int32_t argc, char **argv)
{
        int32_t ret;

        if (argc != 2) {
                fprintf(stderr,"Usage: %s <path>\n", argv[0]);
                return EXIT_FAILURE;
        }

        /*
         * Delete the directory and its contents by traversing the tree in reverse
         * order, without crossing mount boundaries and symbolic links
         */
        ret = nftw(argv[1], rm_files, 10, FTW_DEPTH | FTW_MOUNT | FTW_PHYS);
        if (ret < 0)
                fprintf(stderr, "ERROR: ntfw(%d->%s)\n", errno, strerror(errno));

        return ret;
}
