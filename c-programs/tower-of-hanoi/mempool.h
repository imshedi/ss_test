#ifndef __MEMPOOL_H__
#define __MEMPOOL_H__

//#define CONFIG_MEMTRACKER_DBG

#define malloc		_malloc
#define calloc		_calloc
#define realloc		_realloc
#define free(mem)	_free((void *)&mem)

typedef struct _mem_watcher {
	char *ptr;

#ifdef CONFIG_MEMTRACKER_DBG
	uint32_t size;
#endif				/* CONFIG_MEMTRACKER_DBG */

	struct _mem_watcher *next;
} mem_watcher;

void free_all_mem(void);
void _free(void **ptr);
void *_malloc(int32_t size);
void *_realloc(void *ptr, int32_t size);
void *_calloc(int32_t nmemb, int32_t size);

#endif				/* __MEMPOOL_H__ */
