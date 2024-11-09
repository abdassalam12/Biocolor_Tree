
#include "arbre_noir_rouge.h"

rbnode *rb_insert(rbtree *rbt, void *data);
void insert_repair(rbtree *rbt, rbnode *current);