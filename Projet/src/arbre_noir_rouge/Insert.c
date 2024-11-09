#include <stdio.h>
#include <stdlib.h>
#include "arbre_noir_rouge.h"
#include "Rotation.h"
#include "Insert.h"




rbnode *rb_insert(rbtree *rbt, void *data)
{
	rbnode *current, *parent;
	rbnode *new_node;

	/* do a binary search to find where it should be */

	current = RB_FIRST(rbt);
	parent = RB_ROOT(rbt);

	while (current != RB_NIL(rbt)) {
		int cmp;
		cmp = rbt->compare(data, current->data);

		#ifndef RB_DUP
		if (cmp == 0) {
			rbt->destroy(current->data);
			current->data = data;
			return current; /* updated */
		}
		#endif

		parent = current;
		current = cmp < 0 ? current->left : current->right;
	}

	/* replace the termination NIL pointer with the new node pointer */

	current = new_node = (rbnode *) malloc(sizeof(rbnode));
	if (current == NULL)
		return NULL; /* out of memory */

	current->left = current->right = RB_NIL(rbt);
	current->parent = parent;
	current->color = RED;
	current->data = data;
	
	if (parent == RB_ROOT(rbt) || rbt->compare(data, parent->data) < 0)
		parent->left = current;
	else
		parent->right = current;

	#ifdef RB_MIN
	if (rbt->min == NULL || rbt->compare(current->data, rbt->min->data) < 0)
		rbt->min = current;
	#endif

	if (current->parent->color == RED) {
		insert_repair(rbt, current);
	} else {
	}

	RB_FIRST(rbt)->color = BLACK;
	
	return new_node;
}

void insert_repair(rbtree *rbt, rbnode *current)
{
	rbnode *uncle;

	do {
		/* current node is RED and parent node is RED */

		if (current->parent == current->parent->parent->left) {
			uncle = current->parent->parent->right;
			if (uncle->color == RED) {
				/* insertion into 4-children cluster */

				/* split */
				current->parent->color = BLACK;
				uncle->color = BLACK;

				/* send grandparent node up the tree */
				current = current->parent->parent; /* goto loop or break */
				current->color = RED;
			} else {
				/* insertion into 3-children cluster */

				/* equivalent BST */
				if (current == current->parent->right) {
					current = current->parent;
					rotate_left(rbt, current);
				}

				/* 3-children cluster has two representations */
				current->parent->color = BLACK; /* thus goto break */
				current->parent->parent->color = RED;
				rotate_right(rbt, current->parent->parent);
			}
		} else {
			uncle = current->parent->parent->left;
			if (uncle->color == RED) {
				/* insertion into 4-children cluster */

				/* split */
				current->parent->color = BLACK;
				uncle->color = BLACK;

				/* send grandparent node up the tree */
				current = current->parent->parent; /* goto loop or break */
				current->color = RED;
			} else {
				/* insertion into 3-children cluster */

				/* equivalent BST */
				if (current == current->parent->left) {
					current = current->parent;
					rotate_right(rbt, current);
				}

				/* 3-children cluster has two representations */
				current->parent->color = BLACK; /* thus goto break */
				current->parent->parent->color = RED;
				rotate_left(rbt, current->parent->parent);
			}
		}
	} while (current->parent->color == RED);
}