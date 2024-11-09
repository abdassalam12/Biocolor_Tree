#include <stdio.h>
#include <stdlib.h>
#include "arbre_noir_rouge.h"

// Fonction de comparaison pour les entiers
int compare_ints(const void *a, const void *b) {
    int int_a = *(int *)a;
    int int_b = *(int *)b;

    if (int_a == int_b) return 0;
    else if (int_a < int_b) return -1;
    else return 1;
}

// Fonction de destruction des données (inutile pour des int simples)
void destroy_data(void *data) {
    free(data);
}



int main() {
    // Création de l'arbre rouge-noir
    rbtree *rbt = rb_create(compare_ints, destroy_data);
    if (rbt == NULL) {
        printf("Erreur : échec de la création de l'arbre rouge-noir.\n");
        return 1;
    }

    // Tableau de données pour tester les insertions
    int values[] = {10, 20, 30, 40, 50, 25};
    size_t num_values = sizeof(values) / sizeof(values[0]);

    // Insertion des valeurs dans l'arbre
    for (size_t i = 0; i < num_values; i++) {
        int *data = malloc(sizeof(int));
        *data = values[i];
        rb_insert(rbt, data);
        printf("Insere : %d\n", *data);
    }

    // Affichage ou vérification de l'arbre ici
    // Vous pourriez ajouter des fonctions pour un parcours en ordre pour vérifier la structure

    // Nettoyage de la mémoire
    rb_destroy(rbt);

    printf("Test termine.\n");
    return 0;
}
