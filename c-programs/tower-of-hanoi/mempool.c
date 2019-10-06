#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>

#include "mempool.h"

/* Do not define these macros here or else it'll endup in recursion */
#undef malloc
#undef calloc
#undef realloc
#undef free

#define log_dbg printf

#ifdef CONFIG_MEMTRACKER_DBG
static uint32_t total_mem;
static uint32_t num_allocs;
#endif				/* CONFIG_MEMTRACKER_DBG */

static mem_watcher *memtracker;

static int32_t add_to_list(void *ptr, int32_t size)
{
	mem_watcher *node;

	if (!ptr || size <= 0) {
		return -1;
	}

	node = (mem_watcher *) malloc(sizeof(mem_watcher));
	if (!node) {
		fprintf(stderr, "malloc error while adding to mempool list\n");
		return -1;
	}
#ifdef CONFIG_MEMTRACKER_DBG
	num_allocs++;
	total_mem += size;
	node->size = size;
	log_dbg("%s: Total memory in use: %u Num of allocs: %u\n", __func__,
			total_mem, num_allocs);
#endif /* CONFIG_MEMTRACKER_DBG */

	node->ptr = ptr;
	node->next = memtracker;
	memtracker = node;

	return 0;
}

static void delete_fm_list(void *ptr)
{
	mem_watcher *curr = memtracker;

	if (!ptr || !curr) {
		return;
	}

	if (curr && (ptr == curr->ptr)) {
		memtracker = memtracker->next;
		goto end;
	}

	{
		mem_watcher *prev = curr;

		for (curr = curr->next; curr; prev = curr, curr = curr->next) {
			if (ptr == curr->ptr) {
				prev->next = curr->next;
				goto end;
			}
		}
	}

	return;

end:
#ifdef CONFIG_MEMTRACKER_DBG
	num_allocs--;
	total_mem -= curr->size;
	log_dbg("%s: Total memory in use: %u Num of allocs: %u\n", __func__,
			total_mem, num_allocs);
	log_dbg("Deleting a node with address: %p->%p\n", curr, ptr);
#endif /* CONFIG_MEMTRACKER_DBG */

	free(curr);
}

void free_all_mem(void)
{
	mem_watcher *mtmp = memtracker;

	if (!mtmp) {
#ifdef CONFIG_MEMTRACKER_DBG
		log_dbg("Empty mempool list\n");
		log_dbg("Total memory in use: %u Num of allocs: %u\n",
			total_mem, num_allocs);
#endif				/* CONFIG_MEMTRACKER_DBG */
		return;
	}

	while (mtmp) {
		memtracker = memtracker->next;

#ifdef CONFIG_MEMTRACKER_DBG
		log_dbg("Total memory in use: %u Num of allocs: %u\n",
				total_mem, num_allocs);

		log_dbg("Deleting node of address: %p->%p\n", mtmp, mtmp->ptr);
		num_allocs--;
		total_mem -= mtmp->size;
#endif				/* CONFIG_MEMTRACKER_DBG */

		free(mtmp->ptr);
		free(mtmp);
		mtmp = memtracker;
	}
}

void *_malloc(int32_t size)
{
	void *ptr;

	if (size <= 0) {
		return NULL;
	}

	ptr = malloc(size);
	if (!ptr) {
		fprintf(stderr, "malloc: %s\n", strerror(errno));
		return ptr;
	}

	add_to_list(ptr, size);

	return ptr;
}

void *_calloc(int32_t nmemb, int32_t size)
{
	void *ptr;

	if (size <= 0 || nmemb <= 0) {
		return NULL;
	}

	ptr = calloc(nmemb, size);
	if (!ptr) {
		fprintf(stderr, "calloc: %s\n", strerror(errno));
		return ptr;
	}

	add_to_list(ptr, size * nmemb);

	return ptr;
}

void *_realloc(void *ptr, int32_t size)
{
	if (size <= 0) {
		return NULL;
	}

	ptr = realloc(ptr, size);
	if (!ptr) {
		fprintf(stderr, "realloc: %s\n", strerror(errno));
		return ptr;
	}

	add_to_list(ptr, size);

	return ptr;
}

void _free(void **ptr)
{
	if (!ptr || !(*ptr)) {
		return;
	}

	free(*ptr);

	delete_fm_list(*ptr);

	*ptr = NULL;
}
