#include "sll_hdr.h"

NODE *delete_node(NODE *head)
{
	NODE *cur;
	NODE **prev;
	int val = 0;

	printf("Enter the value to search and delete: ");
	scanf("%d", &val);
	if (!head) {
		printf("Empty sll\n");
		return head;
	}

	cur = head;
	prev = &head;
	while (cur) {
		if ((cur->data) == val) {
			*prev = cur->next;
			free(cur);
			return head;
		}
		cur = cur->next;
		prev = &cur;
	}

	if (!cur)
		printf("Element not found\n");

	return head;
}
