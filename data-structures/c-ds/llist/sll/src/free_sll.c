#include "sll_hdr.h"

void free_sll(NODE *head)
{
	while (head) {
		NODE *tmp = head;
		head = tmp->next;
		free(tmp);
	}
}
