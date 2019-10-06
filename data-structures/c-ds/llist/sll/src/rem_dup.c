#include "sll_hdr.h"

void rem_dup(NODE *list)
{
	NODE *base;

	if (!list) {
		printf("Empty sll\n");
		return;
	}

	base = list;
	printf("Original list\n");
	display_sll(base);

	for ( ; list; list = list->next) {
		NODE *tmp;
		NODE *prev = list;

		for (tmp = list->next; tmp; tmp = tmp->next) {
			if (tmp->data == list->data) {
				prev->next = tmp->next;
				free(tmp);
				tmp = prev;
			} else {
				prev = tmp;
			}
		}
	}

	printf("List with no duplicates\n");
	display_sll(base);
}
