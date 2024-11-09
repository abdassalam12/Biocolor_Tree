#include <stdio.h>
#include <stdlib.h>
#include "arbre_noir_rouge.h"
#include "Rotation.h"
#include "Delete.h"

rbnode *rb_successor(rbtree *rbt, rbnode *node)
{
	rbnode *p;

	p = node->right;

	if (p != RB_NIL(rbt)) {
		/* move down until we find it */
		for ( ; p->left != RB_NIL(rbt); p = p->left) ;
	} else {
		/* move up until we find it or hit the root */
		for (p = node->parent; node == p->right; node = p, p = p->parent) ;

		if (p == RB_ROOT(rbt))
			p = NULL; /* not found */
	}

	return p;
}


void *rb_delete(rbtree *rbt, rbnode *node, int keep)
{
	rbnode *target, *child;
	void *data;
	
	data = node->data;
	if (node->left == RB_NIL(rbt) || node->right == RB_NIL(rbt)) {
		target = node;

		#ifdef RB_MIN
		if (rbt->min == target)
			rbt->min = rb_successor(rbt, target); 
		#endif
	} else {
		target = rb_successor(rbt, node); 

		node->data = target->data; 

		#ifdef RB_MIN
		#endif
	}

	child = (target->left == RB_NIL(rbt)) ? target->right : target->left; /* child may be NIL */
	if (target->color == BLACK) {
		if (child->color == RED) {
            child->color = BLACK;
		} else if (target == RB_FIRST(rbt)) {

		} else {
			delete_repair(rbt, target);
		}
	} else {
	}

	if (child != RB_NIL(rbt))
		child->parent = target->parent;

	if (target == target->parent->left)
		target->parent->left = child;
	else
		target->parent->right = child;

	free(target);
	if (keep == 0) {
		rbt->destroy(data);
		data = NULL;
	}

	return data;
}

void delete_repair(rbtree *rbt, rbnode *current)
{
	rbnode *sibling;
	do {
		if (current == current->parent->left) {
			sibling = current->parent->right;

			if (sibling->color == RED) {
				/* perform an adjustment (3-children parent cluster has two representations) */
				sibling->color = BLACK;
				current->parent->color = RED;
				rotate_left(rbt, current->parent);
				sibling = current->parent->right;
			}

			/* sibling node must be BLACK now */

			if (sibling->right->color == BLACK && sibling->left->color == BLACK) {
				/* 2-children sibling cluster, fuse by recoloring */
				sibling->color = RED;
				if (current->parent->color == RED) { /* 3/4-children parent cluster */
					current->parent->color = BLACK;
					break; /* goto break */
				} else { /* 2-children parent cluster */
					current = current->parent; /* goto loop */
				}
			} else {
				/* 3/4-children sibling cluster */
				
				/* perform an adjustment (3-children sibling cluster has two representations) */
				if (sibling->right->color == BLACK) {
					sibling->left->color = BLACK;
					sibling->color = RED;
					rotate_right(rbt, sibling);
					sibling = current->parent->right;
				}

				/* transfer by rotation and recoloring */
				sibling->color = current->parent->color;
				current->parent->color = BLACK;
				sibling->right->color = BLACK;
				rotate_left(rbt, current->parent);
				break; /* goto break */
			}
		} else {
			sibling = current->parent->left;

			if (sibling->color == RED) {
				/* perform an adjustment (3-children parent cluster has two representations) */
				sibling->color = BLACK;
				current->parent->color = RED;
				rotate_right(rbt, current->parent);
				sibling = current->parent->left;
			}

			/* sibling node must be BLACK now */

			if (sibling->right->color == BLACK && sibling->left->color == BLACK) {
				/* 2-children sibling cluster, fuse by recoloring */
				sibling->color = RED;
				if (current->parent->color == RED) { /* 3/4-children parent cluster */
					current->parent->color = BLACK;
					break; /* goto break */
				} else { /* 2-children parent cluster */
					current = current->parent; /* goto loop */
				}
			} else {
				/* 3/4-children sibling cluster */

				/* perform an adjustment (3-children sibling cluster has two representations) */
				if (sibling->left->color == BLACK) {
					sibling->right->color = BLACK;
					sibling->color = RED;
					rotate_left(rbt, sibling);
					sibling = current->parent->left;
				}

				/* transfer by rotation and recoloring */
				sibling->color = current->parent->color;
				current->parent->color = BLACK;
				sibling->left->color = BLACK;
				rotate_right(rbt, current->parent);
				break; /* goto break */
			}
		}
	} while (current != RB_FIRST(rbt));
}