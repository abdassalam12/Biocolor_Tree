#include <stdio.h>
#include <stdlib.h>
#include "arbre_noir_rouge.h"
#include "Rotation.h"
#include "Insert.h"
#include "Delete.h"

static int check_order(rbtree *rbt, rbnode *n, void *min, void *max);
static int check_black_height(rbtree *rbt, rbnode *node);
static void print(rbtree *rbt, rbnode *node, void (*print_func)(void *), int depth, char *label);
static void destroy(rbtree *rbt, rbnode *node);

rbtree *rb_create(int (*compare)(const void *, const void *), void (*destroy)(void *))
{
	rbtree *rbt;

	rbt = (rbtree *) malloc(sizeof(rbtree));
	if (rbt == NULL)
		return NULL; /* out of memory */

	rbt->compare = compare;
	rbt->destroy = destroy;

	/* sentinel node nil */
	rbt->nil.left = rbt->nil.right = rbt->nil.parent = RB_NIL(rbt);
	rbt->nil.color = BLACK;
	rbt->nil.data = NULL;

	/* sentinel node root */
	rbt->root.left = rbt->root.right = rbt->root.parent = RB_NIL(rbt);
	rbt->root.color = BLACK;
	rbt->root.data = NULL;

	#ifdef RB_MIN
	rbt->min = NULL;
	#endif
	
	return rbt;
}

void rb_destroy(rbtree *rbt)
{
	destroy(rbt, RB_FIRST(rbt));
	free(rbt);
}

rbnode *rb_find(rbtree *rbt, void *data)
{
	rbnode *p;

	p = RB_FIRST(rbt);

	while (p != RB_NIL(rbt)) {
		int cmp;
		cmp = rbt->compare(data, p->data);
		if (cmp == 0)
			return p; /* found */
		p = cmp < 0 ? p->left : p->right;
	}

	return NULL; /* not found */
}



/*
 * apply func
 * return non-zero if error
 */
int rb_apply(rbtree *rbt, rbnode *node, int (*func)(void *, void *), void *cookie, enum rbtraversal order)
{
	int err;

	if (node != RB_NIL(rbt)) {
		if (order == PREORDER && (err = func(node->data, cookie)) != 0) /* preorder */
			return err;
		if ((err = rb_apply(rbt, node->left, func, cookie, order)) != 0) /* left */
			return err;
		if (order == INORDER && (err = func(node->data, cookie)) != 0) /* inorder */
			return err;
		if ((err = rb_apply(rbt, node->right, func, cookie, order)) != 0) /* right */
			return err;
		if (order == POSTORDER && (err = func(node->data, cookie)) != 0) /* postorder */
			return err;
	}

	return 0;
}



/*
 * check order of tree
 */
int rb_check_order(rbtree *rbt, void *min, void *max)
{
	return check_order(rbt, RB_FIRST(rbt), min, max);
}

/*
 * check order recursively
 */
int check_order(rbtree *rbt, rbnode *n, void *min, void *max)
{
	if (n == RB_NIL(rbt))
		return 1;

	#ifdef RB_DUP
	if (rbt->compare(n->data, min) < 0 || rbt->compare(n->data, max) > 0)
	#else
	if (rbt->compare(n->data, min) <= 0 || rbt->compare(n->data, max) >= 0)
	#endif
		return 0;

	return check_order(rbt, n->left, min, n->data) && check_order(rbt, n->right, n->data, max);
}

int rb_check_black_height(rbtree *rbt)
{
	if (RB_ROOT(rbt)->color == RED || RB_FIRST(rbt)->color == RED || RB_NIL(rbt)->color == RED)
		return 0;

	return check_black_height(rbt, RB_FIRST(rbt));
}

int check_black_height(rbtree *rbt, rbnode *n)
{
	int lbh, rbh;

	if (n == RB_NIL(rbt))
		return 1;

	if (n->color == RED && (n->left->color == RED || n->right->color == RED || n->parent->color == RED))
		return 0;

	if ((lbh = check_black_height(rbt, n->left)) == 0)
		return 0;

	if ((rbh = check_black_height(rbt, n->right)) == 0)
		return 0;

	if (lbh != rbh)
		return 0;

	return lbh + (n->color == BLACK ? 1 : 0);
}

void rb_print(rbtree *rbt, void (*print_func)(void *))
{
	printf("\n--\n");
	print(rbt, RB_FIRST(rbt), print_func, 0, "T");
	printf("\ncheck_black_height = %d\n", rb_check_black_height(rbt));
}

void print(rbtree *rbt, rbnode *n, void (*print_func)(void *), int depth, char *label)
{
	if (n != RB_NIL(rbt)) {
		print(rbt, n->right, print_func, depth + 1, "R");
		printf("%*s", 8 * depth, "");
		if (label)
			printf("%s: ", label);
		print_func(n->data);
		printf(" (%s)\n", n->color == RED ? "r" : "b");
		print(rbt, n->left, print_func, depth + 1, "L");
	}
}

void destroy(rbtree *rbt, rbnode *n)
{
	if (n != RB_NIL(rbt)) {
		destroy(rbt, n->left);
		destroy(rbt, n->right);
		rbt->destroy(n->data);
		free(n);
	}
}