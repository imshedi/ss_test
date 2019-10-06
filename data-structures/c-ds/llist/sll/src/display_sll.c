#include "sll_hdr.h"

void display_sll(NODE *head)
{
	if (!head) {
		printf("Empty sll\n");
		return;
	}

	while (head) {
		(head->next) ?  printf("%d --> ", head->data) :
                                printf("%d\n", head->data);
		head = head->next;
	}
}
