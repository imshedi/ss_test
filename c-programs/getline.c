#include <errno.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>

/* Always add at least this many bytes when extending the buffer. */
#define MIN_CHUNK	64

/*
 * Read up to (and including) a TERMINATOR from STREAM into *LINEPTR + OFFSET
 * (and null-terminate it). *LINEPTR is a pointer returned from malloc
 * (or NULL), pointing to *N characters of space.  It is realloc'd as necessary.
 * Return the number of characters read (not including the null terminator), or
 * -1 on error or EOF.  On a -1 return, the caller should check feof(), if not
 *  then errno has been set to indicate the error.
 */

int getstr(char **lineptr, size_t *n, FILE *stream, char terminator, int offset)
{
	int ret;
	char *read_pos;		/* Where we're reading into *LINEPTR. */
	int nchars_avail;	/* Allocated but unused chars in *LINEPTR.  */

	if (!lineptr || !n || !stream) {
		errno = EINVAL;
		return -errno;
	}

	if (!*lineptr) {
		*n = MIN_CHUNK;
		*lineptr = (char *)malloc(*n);
		if (!*lineptr) {
			errno = ENOMEM;
			return -errno;
		}
	}

	nchars_avail = *n - offset;
	read_pos = *lineptr + offset;

	for (;;) {
		int save_errno;
		register int c;

		c = getc(stream);
		save_errno = errno;

		/*
		 * We always want at least one char left in the buffer, since we
		 * always (unless we get an error while reading the first char)
		 * NUL-terminate the line buffer.
		 */
		assert((*lineptr + *n) == (read_pos + nchars_avail));
		if (nchars_avail < 2) {
			if (*n > MIN_CHUNK) {
				*n *= 2;
			} else {
				*n += MIN_CHUNK;
			}

			nchars_avail = *n + *lineptr - read_pos;
			*lineptr = realloc(*lineptr, *n);
			if (!*lineptr) {
				errno = ENOMEM;
				return -errno;
			}

			read_pos = *n - nchars_avail + *lineptr;
			assert((*lineptr + *n) == (read_pos + nchars_avail));
		}

		if (ferror(stream)) {
			/*
			 * Might like to return partial line, but there is no place for us
			 * to store errno.  And we don't want to just lose errno.
			 */
			errno = save_errno;
			return -errno;
		}

		if (c == EOF) {
			/* Return partial line, if any. */
			if (read_pos == *lineptr) {
				errno = ESPIPE;
				return -errno;
			}
			break;
		}

		*read_pos++ = c;
		nchars_avail--;

		if (c == terminator)
			/* Return the line. */
			break;
	}

	/* Done - NUL terminate and return the number of chars read. */
	*read_pos = '\0';
	ret = read_pos - (*lineptr + offset);

	return ret;
}

int getline(char **lineptr, size_t *n, FILE *stream)
{
	return getstr(lineptr, n, stream, '\n', 0);
}

int main(int argc, char **argv)
{
	FILE *stream;
	size_t len = 0;
	char *line = NULL;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <file>\n", argv[0]);
		return EXIT_FAILURE;
	}

	stream = fopen(argv[1], "r");
	if (!stream ) {
		perror("fopen\n");
		return EXIT_FAILURE;
	}

	for (;;) {
		int32_t nread = getline(&line, &len, stream);
		if (nread < 0)
			break;

		printf("Retrieved line of length %d:\n", nread);
		printf("%s\n", line);
	}

	free(line);
	fclose(stream);

	return EXIT_SUCCESS;
}
