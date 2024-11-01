#ifndef ARBRE_NOIR_ROUGE_H
#define ARBRE_NOIR_ROUGE_H

typedef enum { RED, BLACK } Color;

// Structure pour un nœud de l'arbre rouge-noir
typedef struct Node {
    int key;                     // La clé du nœud
    Color color;                // Couleur du nœud
    struct Node* left;          // Pointeur vers le fils gauche
    struct Node* right;         // Pointeur vers le fils droit
    struct Node* parent;        // Pointeur vers le parent
} Node;

// Structure pour l'arbre rouge-noir
typedef struct {
    Node* root;                 // Racine de l'arbre
    Node* TNULL;                // Nœud nul, utilisé pour la gestion des nœuds
} RBTree;

// Prototypes de fonctions
RBTree* createRBTree();
Node* createNode(int key);
void leftRotate(RBTree* tree, Node* x);
void rightRotate(RBTree* tree, Node* y);
void insert(RBTree* tree, int key);
void deleteNode(RBTree* tree, int key);
void printTree(RBTree* tree);

#endif // ARBRE_NOIR_ROUGE_H
