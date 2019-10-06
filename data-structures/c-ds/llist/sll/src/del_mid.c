#include "sll_hdr.h"

NODE *del_mid(NODE *head)
{
	NODE *sp;
	NODE *fp;

	if (!head || !head->next) {
                if (head)
		        free(head);

		return NULL;
	}

	sp = head;
	fp = head->next->next;

	while (fp && fp->next) {
		sp = sp->next;
		fp = fp->next->next;
	}

	fp = sp->next->next;
	free(sp->next);
	sp->next = fp;

	return head;
}
