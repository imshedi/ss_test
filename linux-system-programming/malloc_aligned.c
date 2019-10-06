#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

typedef uint16_t offset_t;

#define COMPILE_AS_EXAMPLE

/*
 * Simple macro for making sure memory addresses are aligned
 * to the nearest power of two
 */
#ifndef ALIGN_UP
#define ALIGN_UP(num, align)	(((num) + ((align) - 1)) & ~((align) - 1))
#endif /* ALIGN_UP */

/* Convenience macro for memalign, the linux API */
#define memalign(align, size) aligned_malloc(align, size)

/* Number of bytes we're using for storing the aligned pointer offset */
#define PTR_OFFSET_SZ sizeof(offset_t)

/*
 * aligned_malloc takes in the requested alignment and size
 * We will call malloc with extra bytes for our header and the offset
 * required to guarantee the desired alignment.
 */
void *aligned_malloc(size_t align, size_t size)
{
	void *p;
	void *ptr;
	uint32_t hdr_size;

	if ((align == 0) || (size == 0))
		return NULL;

	/* Check for power of two since ALIGN_UP operates on powers of two */
	if ((align & (align - 1)) != 0)
		return NULL;

	/*
	 * We know we have to fit an offset value
	 * We also allocate extra bytes to ensure we can meet the alignment
	 */
	hdr_size = PTR_OFFSET_SZ + (align - 1);

	p = malloc(size + hdr_size);
	if (p == NULL)
		return NULL;

	/*
	 * Add the offset size to malloc's pointer (we will always store that)
	 * Then align the resulting value to the arget alignment
	 */
	ptr = (void *)ALIGN_UP(((uintptr_t)p + PTR_OFFSET_SZ), align);

	//Calculate the offset and store it behind our aligned pointer
	*((offset_t *)ptr - 1) = (offset_t)((uintptr_t)ptr - (uintptr_t)p);

	return ptr;
}

/*
 * aligned_free works like free(), but we work backwards from the returned
 * pointer to find the correct offset and pointer location to return to free()
 * Note that it is VERY BAD to call free() on an aligned_malloc() pointer.
 */
void aligned_free(void * ptr)
{
	assert(ptr);

	/*
	 * Walk backwards from the passed-in pointer to get the pointer offset
	 * We convert to an offset_t pointer and rely on pointer math to get the data
	 */
	offset_t offset = *((offset_t *)ptr - 1);

	/* Once we have the offset, we can get our original pointer and call free */
	void * p = (void *)((uint8_t *)ptr - offset);

	free(p);
}

#ifdef COMPILE_AS_EXAMPLE
int main(void)
{
	void *p = malloc(7);
	void *q = malloc(103);
	void *r = malloc(1000);

	void *x = aligned_malloc(4, 8);
	void *y = aligned_malloc(8, 100);
	void *z = aligned_malloc(32, 1035);

	printf("Raw malloc pointers, no alignment enforced: ");
	printf("%p, %p, %p\n", p, q, r);
	printf("Note: you may see 4-8 byte alignment on host PC\n");
	printf("aligned to 4: %p\n", x);
	printf("aligned to 8: %p\n", y);
	printf("aligned to 32: %p\n", z);

	aligned_free(x);
	aligned_free(y);
	aligned_free(z);

	free(p);
	free(q);
	free(r);

	return 0;
}
#endif /* COMPILE_AS_EXAMPLE */
