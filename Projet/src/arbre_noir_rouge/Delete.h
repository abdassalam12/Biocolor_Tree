
#include "arbre_noir_rouge.h"



rbnode *rb_successor(rbtree *rbt, rbnode *node) ;

void *rb_delete(rbtree *rbt, rbnode *node, int keep);

void delete_repair(rbtree *rbt, rbnode *current);