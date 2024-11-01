#include <stdio.h>
#include <stdlib.h>
#include "arbre_noir_rouge.h"

// Création d'un nœud
Node* createNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->color = RED; // Nouveau nœud est rouge par défaut
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    return node;
}

// Création de l'arbre rouge-noir
RBTree* createRBTree() {
    RBTree* tree = (RBTree*)malloc(sizeof(RBTree));
    tree->TNULL = createNode(0); // Nœud nul (TNULL) pour faciliter la gestion
    tree->TNULL->color = BLACK;    // TNULL est toujours noir
    tree->root = tree->TNULL;      // L'arbre est vide au début
    return tree;
}

void printTree(RBTree* tree) {
    if (tree->root == NULL) {
        printf("L'arbre est vide.\n");
    } else {
        printf("La racine de l'arbre est : %d (Color: %s)\n", 
               tree->root->key, 
               tree->root->color == RED ? "RED" : "BLACK");
    }
}

// Fonction pour insérer un nœud
void insert(RBTree* tree, int key) {
    // Implémentez la logique d'insertion ici
}

// Fonction pour insérer un nœud
void delete(RBTree* tree, int key) {
    // Implémentez la logique d'insertion ici
}
