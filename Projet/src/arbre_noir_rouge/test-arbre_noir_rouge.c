#include <stdio.h>
#include "arbre_noir_rouge.h"



// Fonction principale pour le test
int main() {
    RBTree* tree = createRBTree();
    
    // Afficher l'état de l'arbre après sa création
    printTree(tree);
    
    return 0;
}
