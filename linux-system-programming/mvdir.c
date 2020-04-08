/*
 * C program to move a directroy from src to dst
 */

#include <fts.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/errno.h>

#define QUIT_ON_ERR(cond) if ((cond)) { goto error; }

#define isEmptyStr(str) ((!str) || !(*str))

static int32_t fix_dst_path(const char *src, char *dst, int32_t dstsize)
{
    char *s = NULL;
    char buf[dstsize];

    if (isEmptyStr(src) || isEmptyStr(dst) || dstsize <= 0)
        return -1;

    QUIT_ON_ERR(!(s = strrchr(src, '/')));

    memset(buf, 0, dstsize);
    snprintf(buf, dstsize, "%s/%s", dst, ++s);
    strcpy(dst, buf);

    return 0;

error:
    return -1;
}

int32_t removedir(const char *path)
{
    FTS *ftsp = NULL;
    FTSENT *ent = NULL;
    int32_t retval = 0;
    char rpath[PATH_MAX] = {0};

    if (isEmptyStr(path))
        return -1;

    if (!realpath(path, rpath))
        return -1;

    char *paths[] = { rpath, NULL };

    ftsp = fts_open(paths, FTS_PHYSICAL, NULL);
    if (!ftsp)
        return -1;

    errno = 0;
    while ((ent = fts_read(ftsp))) {
        if (ent->fts_info & FTS_DP) {
            rmdir(ent->fts_path);
        } else if (ent->fts_info & FTS_F){
            unlink(ent->fts_path);
        }

        if (errno) {
            retval = -1;
            fprintf(stderr, "Failed to delete: %s\n", ent->fts_path);
            goto error;
        }
    }

error:
    if (fts_close(ftsp))
         return -1;

    return retval;
}

int32_t copy_file(const char *src, const char *dst)
{
    size_t n = 0;
    FILE *in = NULL;
    FILE *out = NULL;
    char rbuf[BUFSIZ] = {0};
    int32_t retval = -1;

    if (isEmptyStr(src) || isEmptyStr(dst))
        return -1;

    in = fopen(src, "rb");
    out= fopen(dst, "wb");
    QUIT_ON_ERR((!in || !out));

    while ((n = fread(rbuf, 1, BUFSIZ, in))) {
        QUIT_ON_ERR((fwrite(rbuf, 1, n, out) != n));
    }

    QUIT_ON_ERR(!feof(in));

    retval = 0;

error:
    if ((in && fclose(in)) || (out && fclose(out)))
        retval = -1;

    return retval;
}

int32_t mvdir(const char *src, const char *dst)
{
    FTS *ftsp = NULL;
    FTSENT *ent = NULL;
    int32_t retval = 0;
    char srcpath[PATH_MAX] = {0};
    char dstpath[PATH_MAX] = {0};

    if (isEmptyStr(src) || isEmptyStr(dst))
        return -1;

    if (!realpath(src, srcpath))
        return -1;

    char *paths[] = { srcpath, NULL };

    ftsp = fts_open(paths, FTS_PHYSICAL, NULL);
    if (!ftsp) {
        return -1;
    }

    if (!realpath(dst, dstpath)) {
        QUIT_ON_ERR((retval = -1));
    }

    while ((ent = fts_read(ftsp))) {
        char *s = NULL;
        char *cursrc = ent->fts_path;

        if (ent->fts_info & FTS_D) {
            struct stat fstat = {0};

            retval = fix_dst_path(cursrc, dstpath, sizeof(dstpath));
            QUIT_ON_ERR(retval);

            if (stat(srcpath, &fstat) || mkdir(dstpath, fstat.st_mode)) {
                if (errno != EEXIST) {
                    QUIT_ON_ERR((retval = -1));
                }
            }
        } else if (ent->fts_info & FTS_DP) {
            s = strrchr(dstpath, '/');
            QUIT_ON_ERR(!s && (retval = -1));

            *s = '\0';
        } else if (ent->fts_info & FTS_F) {
            retval = fix_dst_path(cursrc, dstpath, sizeof(dstpath));
            QUIT_ON_ERR(retval);

            if (copy_file(cursrc, dstpath)) {
                fprintf(stderr, "Unable to copy file: %s to destination %s\n",
                        cursrc, dstpath);
                goto error;
            }
            sync();

            s = strrchr(dstpath, '/');
            QUIT_ON_ERR(!s && (retval = -1));

            *s = '\0';
        } else {
            /* We shouldn't reach here */
            fprintf(stderr, "Other: %s\n", cursrc);
        }
    }

    if ((retval = removedir(src)))
        fprintf(stderr, "Deletion of %s failed\n", src);

error:
    if (fts_close(ftsp))
        retval = -1;

    printf("Move %s to %s - %s\n", srcpath, dstpath, !retval ? "success" :
            "failed");

    return retval;
}

int32_t main(int32_t argc, char **argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "[Usage: ./mvdir <src-dir> <dst-dir>]\n");
        return EXIT_FAILURE;
    }

    return mvdir(argv[1], argv[2]);
}
