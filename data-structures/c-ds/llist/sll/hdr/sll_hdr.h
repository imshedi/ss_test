#ifndef __SLL_H__
#define __SLL_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct sll {
	int data;
	struct sll *next;
} NODE;

#define GETMEM(ptr, type, size) \
	do { ptr = (type *) malloc(sizeof(type) * size); } while (0)

#define FREE(ptr) do { free(ptr); ptr = NULL; } while (0)

#define CHECK(val) \
	do { \
		if (val) { \
			fprintf(stderr, "ERROR: %s:%d\n", __func__, __LINE__); \
			return NULL; \
		} \
	} while (0)

/** Functions */
extern int main(void);
extern void rem_dup(NODE *);
extern NODE *del_mid(NODE *);
extern void free_sll(NODE *);
extern NODE *rev_llist(NODE *);
extern void display_sll(NODE *);
extern NODE *delete_node(NODE *);
extern NODE *add_node(NODE *, int);
extern int check_presence(int, NODE *);
extern NODE *union_sll(NODE *, NODE *);
extern void merge_altr_nodes(NODE *, NODE *);
extern void union_intersection(NODE *, NODE *);

#endif /** __SLL_H__ */
