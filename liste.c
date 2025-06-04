//
//  liste.c

//

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
* Rôle : insérer dans la liste l l’élément e, au rang r
* Antécédent : 1 <= r <= longueur(l) + 1
*/
void inserer(Liste *l, const int r, const T e) {
    assert(r>=1 && r<=longueur(*l)+1);
    // le rang r est valide
    struct noeud *n = creerNoeud(e);
    if (r==1) { // insertion en tête de liste
        n->suivant = *l;
        *l = n;
    }
    else { // cas général, r>=2
        struct noeud *q = *l;
        for (int i=2; i<r; i++){
            q = q->suivant;
        }
        // q désigne l'élément de rang n-1
        n->suivant = q->suivant;
        q->suivant = n;
    }
}













/*
* Rôle : supprime l’élément de rang r de la liste l
* Antécédent : 1 <= r <= longueur(l)
*/
void supprimer(Liste *l, const int r) {
    assert(r>=1 && r<=longueur(*l));
    // le rang r est valide
    struct noeud *p;
    if (r == 1) {
        // suppression en tête de liste
        p = *l;
        *l = (*l)->suivant;
    }
    else { // cas général, r>=2
        struct noeud *q = *l;
        for (int i=2; i<r; i++){
            q = q->suivant;
        }
        // q désigne l’élément de rang r−1
        p = q->suivant;
        q->suivant = p->suivant;
    }
    free(p);
}


/*
* Rôle : supprime le dernier élément de la liste
 */
void supprimerEnQueue(Liste *l) {
    supprimer(l, longueur(*l));
}


/*
* Rôle : supprime le dernier élément de la liste
*/
void supprimerEnQueueBis(Liste *l) {
    const int lg = longueur(*l);
    assert(lg>0);
    // se placer sur l’avant dernier noeud
    struct noeud *p;
    if (lg==1) {
        // cas particulier, suppression du 1er et seul élément
        p = *l;
        *l = NULL;
    } else {
        // cas général : se placer sur l’avant dernier noeud
        struct noeud *q = *l;
        for (int i=2; i<lg; i++){
            q = q->suivant;
        }
        // q désigne l’avant dernier noeud
        p = q->suivant; // l’élément à supprimer
        q->suivant = NULL;
    }
    free(p);
}

