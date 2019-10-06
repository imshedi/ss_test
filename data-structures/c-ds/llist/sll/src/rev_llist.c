#include "sll_hdr.h"

#if 0
NODE *rev_llist(NODE *head)
{
        NODE *prev;
	NODE *cur = head;

	if (!cur)
		return NULL;

	while (cur) {
		NODE *next = cur->next;

		cur->next = prev;
		prev = cur;
		cur = next;
	}

	return prev;
}
#endif

NODE *rev_llist(NODE *node)
{
	NODE *rev_head = NULL;

	if (!node)
		return NULL;

        if (!node->next)
		return node;

	rev_head = rev_llist(node->next);

	node->next->next = node;
	node->next = NULL;

	return rev_head;
}
