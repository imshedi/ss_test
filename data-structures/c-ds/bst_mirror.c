#include <stdio.h>
#include <stdlib.h>

typedef struct node_t {
	int data;
	struct node_t *left;
	struct node_t *right;
} node_t;

/* Helper function that allocates a new node with the
   given data and NULL left and right pointers. */
node_t *new_node(int data)
{
	node_t *node;

	node = (node_t *)malloc(sizeof(node_t));
	if (node) {
		node->data = data;
		node->left = NULL;
		node->right = NULL;
	} else {
		perror("new_node malloc failed\n");
		exit(-1);
	}

	return node;
}

/*
 * Change a tree so that the roles of the left and
   right pointers are swapped at every node.

   So the tree...
    1
   / \
   2  3
  / \
  4 5

   is changed to...
    1
   / \
   3 2
    / \
    5 4
*/

void mirror(node_t *node)
{
	if (node) {
		/* do the subtrees */
		mirror(node->left);
		mirror(node->right);

		/* swap the pointers in this node */
		node_t *temp = node->left;
		node->left = node->right;
		node->right = temp;
	}
}

/* Helper function to print Inorder traversal.*/
void inorder(node_t *node)
{
	if (node) {
		inorder(node->left);
		printf("%d ", node->data);
		inorder(node->right);
	}
}

void delete_tree(node_t *node)
{
	if (node) {
		delete_tree(node->left);
		delete_tree(node->right);
		printf("Deleting node with value: %d\n", node->data);
		free(node);
	}
}

/* Driver program to test mirror() */
int main(void)
{
	node_t *root = new_node(1);
	root->left = new_node(2);
	root->right = new_node(3);
	root->left->left = new_node(4);
	root->left->right = new_node(5);

	/* Print inorder traversal of the input tree */
	printf("Inorder traversal of the constructed tree is \n");
	inorder(root);

	/* Convert tree to its mirror */
	mirror(root);

	/* Print inorder traversal of the mirror tree */
	printf("\nInorder traversal of the mirror tree is: \n");
	inorder(root);
	printf("\n");

	delete_tree(root);

	return 0;
}
