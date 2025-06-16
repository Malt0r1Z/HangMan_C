//
// liste.c
// 
// Khady DIOP & Alex MEURILLON ELSE3
//
// Ce fichier implémente les fonctions de manipulation de la liste chaînée


#include <assert.h>
#include <stdlib.h>
#include "liste.h"

/*
 * Rôle : renvoie une liste vide
*/
Liste initListe(void) {
    return NULL;
}

/*
 * Rôle : renvoie le nombre d’éléments de la liste
*/
int longueur(const Liste l) {
    struct noeud *p = l;
    int i = 0;
    while (p != NULL) {
        i++;
        p = p->suivant;
    }
    return i;
}

/*
 * Rôle : renvoie l’élément de rang r de la liste l
 * Antécédent : 1 <= r <= longueur(l)
*/
T ieme(const Liste l, const int r) {
    assert(r>=1 && r<=longueur(l));
    struct noeud *p = l;
    for (int i = 1; i<r; i++){
        p = p->suivant;
    }
    return p->elt;
}

/*
 * Rôle : crée un noeud avec l’élément e
 * et renvoie un pointeur sur ce noeud
*/
static struct noeud* creerNoeud(const T e) {
    struct noeud *n = malloc(sizeof(struct noeud));
    n->elt = e;
    n->suivant = NULL;
    return n;
}

/*
 * Rôle : Insérer dans la liste l l’élément e, au rang r
 * Antécédent : 1 <= r <= longueur(l) + 1
*/
void inserer(Liste *l, const int r, const T e) {
    assert(r>=1 && r<=longueur(*l)+1);
    // Le rang r est valide
    struct noeud *n = creerNoeud(e);
    if (r==1) { // Insertion en tête de liste
        n->suivant = *l;
        *l = n;
    }
    else { // Cas général, r>=2
        struct noeud *q = *l;
        for (int i=2; i<r; i++){
            q = q->suivant;
        }
        // q désigne l'élément de rang n-1
        n->suivant = q->suivant;
        q->suivant = n;
    }
}