#include "sll_hdr.h"

int main(void)
{
	NODE *l1 = NULL;
	NODE *l2 = NULL;
	uint32_t opt = 0;

	printf("\t\t *** sll arena *** \t\t\n");

	do {
		printf("1:Add Node 2:Display sll 3:Special Ops "
		       "4:Delete a node 5: Exit\n");
		scanf("%d", &opt);

		switch (opt) {
		case 1:
			l1 = add_node(l1, 1);
			l1 = add_node(l1, 2);
			l1 = add_node(l1, 3);
			l1 = add_node(l1, 4);
			l2 = add_node(l2, 5);
			l2 = add_node(l2, 6);
			l2 = add_node(l2, 7);
			l2 = add_node(l2, 8);
			break;

		case 2:
			display_sll(l1);
			display_sll(l2);
			break;

		case 3:
			//rem_dup(l1);
			//l1 = del_mid(l1);
			//l1 = rev_llist(l1);
			//union_intersection(l1);
			//merge_altr_nodes(l1, l2);
			//l1 = del_nth_fm_last(l1);
			break;

		case 4:
			l1 = delete_node(l1);
			break;

		case 5:
			free_sll(l1);
			free_sll(l2);
                        break;

                default:
                        break;
		}
	} while (opt != 5);

	return EXIT_SUCCESS;
}
