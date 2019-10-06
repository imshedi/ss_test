#include "sll_hdr.h"

NODE *del_nth_fm_last(NODE * head)
{
	NODE *ptr_1;
	NODE *ptr_2;
	NODE *tmp = NULL;
	int num_fm_last = 0;

	if (!head) {
		printf("EMPTY SLL\n");
		return NULL;
	}

	ptr_1 = head;
	ptr_2 = head;

	printf("Enter N:\n");
	scanf("%d", &num_fm_last);

	while ((num_fm_last--) && (ptr_1))
		ptr_1 = ptr_1->next;

	if (!ptr_1) {
		printf("Nodes are lesser than input\n");
		return head;
	}

	while (ptr_1->next) {
		tmp = ptr_2;
		ptr_2 = ptr_2->next;
		ptr_1 = ptr_1->next;
	}

	if (!tmp) {
		tmp = head->next;
		free(head);
		head = tmp;
		return head;
	}
	tmp->next = ptr_2->next;
	free(ptr_2);

	return head;
}
