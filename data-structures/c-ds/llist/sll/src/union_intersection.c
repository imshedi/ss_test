#include "sll_hdr.h"

int check_presence(int data, NODE *l2)
{
	for ( ; l2; l2 = l2->next) {
		if (l2->data == data)
			return 1;
	}

	return 0;
}

NODE *union_sll(NODE *l1, NODE *l2)
{
	for ( ; l1; l1 = l1->next) {
		if (!check_presence(l1->data, l2))
			l2 = add_node(l2, l1->data);
		l1 = l1->next;
	}

	return l2;
}

void union_intersection(NODE *l1, NODE *l2)
{
	NODE *l3 = NULL;

	printf("List 2: \n");
	display_sll(l2);

	if (!l1 && !l2) {
		printf("lists are empty\n");
		return;
	}

	/** union */
	l3 = union_sll(l1, l3);
	l3 = union_sll(l2, l3);

	printf("Union of l1 and l2 is\n");
	display_sll(l3);
	free_sll(l3);
	l3 = NULL;

	/** intersection */
	NODE *tmp = l2;
	for ( ; l1; l1 = l1->next) {
		for ( ; l2; l2 = l2->next) {
			if ((l1->data == l2->data) &&
			    (!check_presence(l1->data, l3))) {
				l3 = add_node(l3, l1->data);
			}
		}
		l2 = tmp;
	}

	printf("Intersection of l1 and l2 is\n");
	display_sll(l3);
	free_sll(l3);
}
