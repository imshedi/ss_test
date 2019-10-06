#include "sll_hdr.h"

NODE *add_node(NODE *list, int data)
{
	NODE *tmp;

	GETMEM(tmp, NODE, sizeof(NODE));
	CHECK(!tmp);

	tmp->data = data;

	if (!list)
		return tmp;

        tmp->next = list;

        return tmp;
}
