#include "arbre_noir_rouge.h"

void rotate_left(rbtree *rbt, rbnode *x)
{
	rbnode *y;
    /* Etape : 1 */
	y = x->right;

	/* Etape : 2 */
	x->right = y->left;
	if (x->right != RB_NIL(rbt))
    /* change le parent de x->right de y a x  */
		x->right->parent = x;

	/* Etape : 3 */
	y->parent = x->parent;
	if (x == x->parent->left)
    /* y sera sur le left de p si x etait sur le left de p  */
		x->parent->left = y;
	else
    /* y sera sur le right de p si x etait sur le right de p  */
		x->parent->right = y;

	/* Etape : 4 */
	y->left = x;
	x->parent = y;
}

void rotate_right(rbtree *rbt, rbnode *x)
{
    rbnode *y;

    /* Etape : 1 */
    y = x->left;  // y devient le fils gauche de x (c'est le nœud qui sera déplacé vers le haut)

    /* tree x */
    x->left = y->right;  // x prend le fils droit de y comme son fils gauche
    if (x->left != RB_NIL(rbt))
        x->left->parent = x;  // Si le fils gauche de x existe, son parent devient x (mise à jour de la parenté)

    /* tree y */
    y->parent = x->parent;  // y prend le parent de x (avant la rotation)
    if (x == x->parent->left)
        x->parent->left = y;  // Si x était le fils gauche de son parent, y devient le fils gauche du parent
    else
        x->parent->right = y;  // Si x était le fils droit de son parent, y devient le fils droit du parent

    /* assemble tree x and tree y */
    y->right = x;  // y devient le parent de x, et x est attaché à son côté droit
    x->parent = y;  // Mise à jour de la parenté : x a maintenant y pour parent
}
