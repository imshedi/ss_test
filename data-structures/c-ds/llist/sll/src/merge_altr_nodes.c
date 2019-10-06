#include "sll_hdr.h"

void merge_altr_nodes(NODE *l1, NODE *l2)
{
        NODE *tmp;

	if (!l1 || !l2) {
		printf("one of the list is empty\n");
		return;
	}

	tmp = l1;
	while (l1 && l2) {
		NODE *p1 = l1->next;
		NODE *p2 = l2->next;

		l1->next = l2;
		l2->next = p1;

		l1 = p1;
		l2 = p2;
	}

	printf("Merged llist is\n");
	display_sll(tmp);
}
